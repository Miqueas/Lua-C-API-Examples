#include <stdio.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

/* In this example we create an small library
 * and return it as a table
 */

int sqr(lua_State *L);
int fib(lua_State *L);
int cube(lua_State *L);

int luaopen_basic_lib(lua_State *L) {
  // Table to be returned
  lua_createtable(L, 0, 3);

  // Table key
  lua_pushstring(L, "sqr");
  // Table value
  lua_pushcfunction(L, sqr);
  // Push the key and the value into the table and then
  // remove these things from the stack
  lua_rawset(L, -3);

  lua_pushstring(L, "cube");
  lua_pushcfunction(L, cube);
  lua_rawset(L, -3);

  lua_pushstring(L, "fib");
  lua_pushcfunction(L, fib);
  lua_rawset(L, -3);

  return 1;
}

int sqr(lua_State *L) {
  lua_Number n   = luaL_checknumber(L, 1);
  lua_Number res = n * n;
  lua_pushnumber(L, res);
  return 1;
}

int cube(lua_State *L) {
  lua_Number n   = luaL_checknumber(L, 1);
  lua_Number res = n * n * n;
  lua_pushnumber(L, res);
  return 1;
}

int fib(lua_State *L) {
  lua_Number n = luaL_checknumber(L, 1);
  lua_Number x = 0, y = 1, z;

  if (n != 0 || n != 1) {
    for (int i = 2; i <= n; i++) {
      z = x + y;
      x = y;
      y = z;
    }

    lua_pushnumber(L, y);
  } else { lua_pushnumber(L, n); }

  return 1;
}