#include <stdio.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

int hello(lua_State *L) {
  const char *name;

  // Type checking. In the C API, numbers are always convertibles to strings, so
  // is needed to check if the function is given the correct argument types
  if (
    (lua_isstring(L, 1) && lua_isnumber(L, 1)) ||
    (!lua_isstring(L, 1) && !lua_isnil(L, 1))
  ) {
    return luaL_typerror(L, 1, "string");
  } else if (!lua_isstring(L, 1) && lua_isnil(L, 1)) {
    name = "guest";
  } else { name = lua_tostring(L, 1); }

  printf("Hello, %s!\n", name);

  // The function return 0 values
  return 0;
}

int luaopen_hello(lua_State *L) {
  // Push the above C function as a global function
  lua_register(L, "hello", hello);
  return 0;
}
