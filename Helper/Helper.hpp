#pragma once
#include <lua.h>
namespace Helper
{
	inline void RegisterFunction( lua_State* L , const char* Name , lua_CFunction Function )
	{
		lua_pushcfunction( L , Function , Name );
		lua_setglobal( L , Name );
	}
}
