#include <stdio.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

/* In this example we create an small library
 * and return it as a table
 */

int main(void) {
  lua_State *L1 = luaL_newstate();
  lua_State *L2 = luaL_newstate();

  luaL_openlibs(L1);
  luaL_openlibs(L2);

  lua_getglobal(L1, "print");
  lua_getglobal(L2, "print");
  lua_pushstring(L1, "Hello from Lua State 1");
  lua_pushstring(L2, "Hello from Lua State 2");

  lua_call(L1, 1, 0);
  lua_call(L2, 1, 0);

  lua_close(L1);
  lua_close(L2);
}