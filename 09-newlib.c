#include <stdio.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

/* In this example we use the axuliar function `luaL_newlib`,
 * which is available since Lua 5.2 and simplifies the way
 * of creating modules/libraries
 */

int swap(lua_State *L) {
  lua_Number n1 = luaL_checknumber(L, 1);
  lua_Number n2 = luaL_checknumber(L, 2);
  lua_pushnumber(L, n2);
  lua_pushnumber(L, n1);
  return 2;
}

const luaL_Reg funcs[] = {
  { "swap", swap },
  { NULL, NULL }
};

int luaopen_newlib(lua_State *L) {
  // This function is basically a helper/wrapper that just
  // creates a new table, fill it with our C functions and
  // push it on to the stack
  luaL_newlib(L, funcs);

  return 1;
}