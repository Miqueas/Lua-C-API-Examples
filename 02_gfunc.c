#include <stdio.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

int hello(lua_State *L) {
  const char *name;

  // Type checking. In the Lua C API (5.1), numbers are always convertibles
  // to strings, so is needed to check if the function is given the correct
  // argument types
  if (lua_isnumber(L, 1)) {
    return luaL_typerror(L, 1, "string");
  } else if (!lua_isstring(L, 1)) {
    name = "guest";
  } else { name = lua_tostring(L, 1); }

  printf("Hello, %s!\n", name);

  // The function return 0 values
  return 0;
}

// Since we're making a C module for Lua, the way that Lua loads it is
// calling a function called "luaopen_<modname>". Be careful about this
// 'cause your module can't be loaded if there's an naming error!
int luaopen_hello(lua_State *L) {
  // Push the above C function as a global function
  lua_register(L, "hello", hello);

  return 0;
}