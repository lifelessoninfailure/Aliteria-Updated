#pragma once
#include <cstdint>
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#define r(address) (address + reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr)))
struct Lua_State;
namespace Offsets
{
    namespace Signals {
        const uintptr_t FireTouchInterest = r(0x2A50730);
        const uintptr_t FireMouseClick = r(0x2611D70);
        const uintptr_t FireRightMouseClick = r(0x26123E0);
        const uintptr_t FireMouseHoverEnter = r(0x2611F80);
        const uintptr_t FireMouseHoverLeave = r(0x2612170);

        const uintptr_t FireProximityPrompt = r(0x2653780);
    }

    namespace Instance
    {
        const uintptr_t Primitive = 0x148;
        const uintptr_t Overlap = 0x1E8;
    }
    namespace Luau
    {
        const uintptr_t Luau_Execute = r(0x46C8A40);
        const uintptr_t LuaO_NilObject = r(0x69336F0 );
        const uintptr_t LuaH_DummyNode = r(0x6933598);
    }
	const uintptr_t Print = r(0x1E6B8E0);
	const uintptr_t FakeDataModelToDataModel = 0x1D0;
	const uintptr_t FakeDataModelPointer = r(0x7be9278);
    const uintptr_t GetLuaState = r(0x1CEDE20);
    const uintptr_t OpcodeLookupTable = r(0x61C76E0);
    const uintptr_t ScriptContext = 0x440;
    const uintptr_t RequireBypass = 0xd90;
}
namespace Functions
{
    using fireclick_t = void(__fastcall*)(void* clickDetector, float distance,
        void* player);
    inline auto FireMouseClick =
        reinterpret_cast<fireclick_t>(Offsets::Signals::FireMouseClick);
    inline auto FireRightMouseClick =
        reinterpret_cast<fireclick_t>(Offsets::Signals::FireRightMouseClick);
    using firehover_t = void(__fastcall*)(void* clickDetector, void* player);
    inline auto FireMouseHover =
        reinterpret_cast<firehover_t>(Offsets::Signals::FireMouseHoverEnter);
    inline auto FireMouseHoverLeave =
        reinterpret_cast<firehover_t>(Offsets::Signals::FireMouseHoverLeave);
    inline auto FireProximityPrompt = (void(__thiscall*)(uintptr_t))Offsets::Signals::FireProximityPrompt;
    inline auto FireTouchInterest = (void(__fastcall*)(uintptr_t, uintptr_t, uintptr_t, bool, bool))Offsets::Signals::FireTouchInterest;
    // Fix 1: Use reinterpret_cast for Luau_Execute
    inline auto Luau_Execute = reinterpret_cast<void(__fastcall*)(Lua_State*)>(Offsets::Luau::Luau_Execute);

    // Fix 2: Use reinterpret_cast for Print
    inline auto Print = reinterpret_cast<int(__cdecl*)(int, const char*, ...)>(Offsets::Print);
}