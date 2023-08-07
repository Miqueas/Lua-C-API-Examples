#include <stdio.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

// In this example we push a global C function in Lua

int hello(lua_State *L) {
  const char *name;

  // Type checking. Numbers are always convertibles to strings (at least
  // for 5.1), so is recommended to check if the function is getting the
  // correct argument types
  if (lua_isnumber(L, 1)) {
    return luaL_typerror(L, 1, "string");
  } else if (!lua_isstring(L, 1)) {
    name = "guest";
  } else { name = lua_tostring(L, 1); }

  printf("Hello, %s!\n", name);

  // The function return 0 values
  return 0;
}

// Since we're making a C module/library, we don't write a `main` function.
// Instead, we need to write a function called "luaopen_<modname>" that will
// be opened by Lua. Be careful about this, 'cause your module can't be loaded
// if there's a naming error!
int luaopen_gfunc(lua_State *L) {
  // Push the C function `hello` as a global function
  lua_register(L, "hello", hello);

  return 0;
}