#include <stdio.h>
#include "constants.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

/* In this example, we load a Lua file with a table,
 * then set a metatable to it and try it
 */

int __call_metamethod(lua_State *L);

int main(int argc, char **argv) {
  lua_State *L = luaL_newstate();

  // Here I do the same as in the example 04
  int err = luaL_dofile(L, METATABLE_PATH);
  if (err) {
    fprintf(stderr, "Can't load Lua file\n");
    return 1;
  }

  lua_getglobal(L, "MyTable");

  // Our table to use as metatable
  lua_newtable(L);

  // Push the __call metamethod in the above table
  lua_pushstring(L, "__call");
  lua_pushcfunction(L, __call_metamethod);
  lua_rawset(L, 2);

  // Set the metatable. lua_setmetatable assumes that the table to
  // use as metatable is the last element in the stack, so pop it
  // and sets as metatable for the table at the given index. Now,
  // "MyTable" is in top of the stack
  lua_setmetatable(L, 1);

  // Now we can call the table "MyTable" and this will use the
  // __call metamethod of the table
  lua_pushstring(L, "name");
  lua_call(L, 1, 0);

  // lua_call() pops the table from the stack, so we need to push
  // it again
  lua_getglobal(L, "MyTable");
  lua_pushstring(L, "age");
  lua_call(L, 1, 0);

  // We keep calling "MyTable" to test the __call metamethod
  lua_getglobal(L, "MyTable");
  lua_pushstring(L, "is_alive");
  lua_call(L, 1, 0);

  lua_getglobal(L, "MyTable");
  lua_pushstring(L, "role");
  lua_call(L, 1, 0);

  lua_getglobal(L, "MyTable");
  lua_pushstring(L, "likes");
  lua_call(L, 1, 0);

  lua_close(L);

  return 0;
}

int __call_metamethod(lua_State *L) {
  const char *key = luaL_checkstring(L, 2);

  lua_rawget(L, 1);
  if (lua_isnil(L, 2)) {
    printf("key '%s' doesn't exists in table 'MyTable'\n", key);
  } else {
    int type = lua_type(L, 2);

    switch (type) {
      case LUA_TNUMBER:
        printf("%s = %f\n", key, lua_tonumber(L, 2));
        break;
      case LUA_TSTRING:
        printf("%s = %s\n", key, lua_tostring(L, 2));
        break;
      case LUA_TBOOLEAN:
        printf("%s = %s\n", key, (lua_toboolean(L, 2)) ? "true" : "false");
        break;
      default:
        printf("%s = %s(%p)\n", key, lua_typename(L, type), lua_topointer(L, 2));
        break;
    }
  }

  return 0;
}