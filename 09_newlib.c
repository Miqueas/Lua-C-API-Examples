#include <stdio.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

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
  luaL_newlib(L, funcs);

  return 1;
}