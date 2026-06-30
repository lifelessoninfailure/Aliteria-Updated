#pragma once
#include <lua.h>
#include <lualib.h>
#include "../../Misc/Misc.h"
#include "../../Helper/Helper.hpp"
#include "Scheduler/Scheduler.h"
namespace Environment
{
	namespace Libraries
	{
		namespace Misc
		{
			inline int getexecutorname( lua_State* L )
			{
				lua_pushstring( L , "Aliteria" );
				return 1;
			}
			inline int identifyexecutor( lua_State* L )
			{
				lua_pushstring( L , "Aliteria" );
				lua_pushstring( L , "Base" );
				return 2;
			}
			inline int getgenv( lua_State* L )
			{
				lua_pushvalue( L , LUA_GLOBALSINDEX );
				return 1;
			}
			inline int getreg( lua_State* L )
			{
				lua_pushvalue( L , LUA_REGISTRYINDEX );
				return 1;
			}
			inline int gettenv( lua_State* L )
			{
				luaL_checktype( L , 1 , LUA_TTHREAD );
				lua_getfenv( L , 1 );
				return 1;
			}
	
		

			inline void Register( lua_State* L )
			{
       
				Helper::RegisterFunction( L , "getexecutorname" , getexecutorname );
				Helper::RegisterFunction( L , "identifyexecutor" , identifyexecutor );
				Helper::RegisterFunction( L , "getgenv" , getgenv );
				Helper::RegisterFunction( L , "getreg" , getreg );
				Helper::RegisterFunction( L , "gettenv" , gettenv );
				
				
			}
		}
	}
}
