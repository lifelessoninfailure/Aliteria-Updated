#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <fstream>
#include <filesystem>
#include <Dependencies/Luau/VM/include/lua.h>
#include <Dependencies/Luau/VM/src/lapi.h>
#include "../Misc/Misc.h"
#include "../Aliteria_Main/Shared/Instances.h"
#include "../Aliteria_Main/Compiler.h"
#include "../IdentityManager/IdentityManager.h"

namespace AutoExecute
{
    inline std::string ReadFile( const std::string& Path )
    {
        std::ifstream File( Path , std::ios::binary );
        if ( !File.is_open( ) ) return "";
        return std::string( ( std::istreambuf_iterator< char >( File ) ) , std::istreambuf_iterator< char >( ) );
    }

    inline std::string GetLocalAppData( )
    {
        char* Buf = nullptr;
        size_t Size = 0;
        if ( _dupenv_s( &Buf , &Size , "LOCALAPPDATA" ) == 0 && Buf != nullptr )
        {
            std::string Result( Buf );
            free( Buf );
            return Result;
        }
        return "";
    }

    inline void Run( lua_State* L )
    {
        std::string Path = GetLocalAppData( ) + "\\Aliteria\\filesystem.lua";
        if ( !std::filesystem::exists( Path ) )
        {
            ::Misc::Print( "[AutoExecute] filesystem.lua not found" );
            return;
        }
        std::string Script = ReadFile( Path );
        if ( Script.empty( ) )
        {
            ::Misc::Print( "[AutoExecute] filesystem.lua is empty" );
            return;
        }

        int Top = lua_gettop( L );
        std::string Bytecode = Anetia_Compiler::BytecodeCompile( Script );
        if ( luau_load( L , "filesystem.lua" , Bytecode.c_str( ) , Bytecode.size( ) , 0 ) != LUA_OK )
        {
            const char* Err = lua_tostring( L , -1 );
            ::Misc::Error( Err ? Err : "[AutoExecute] Load error" );
            lua_pop( L , 1 );
            return;
        }
        Closure* cl = clvalue( luaA_toobject( L , -1 ) );
        IdentityManager::SetProtoCaps( cl->l.p , &Misc::MaxCaps );
        if ( lua_pcall( L , 0 , 0 , 0 ) != LUA_OK )
        {
            const char* Err = lua_tostring( L , -1 );
            ::Misc::Error( Err ? Err : "[AutoExecute] Runtime error" );
            lua_pop( L , 1 );
            return;
        }
        lua_settop( L , Top );
        ::Misc::Print( "[AutoExecute] FileSystem loaded" );
    }
}
