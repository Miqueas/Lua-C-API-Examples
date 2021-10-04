#include <stdio.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

/*
 * Classic "hello world" example. This essentially creates a Lua runtime and
 * then calls: print("Hello, world!")
 */
int main(int argc, char **argv) {
  // Creates a new lua runtime
  lua_State *L = luaL_newstate();
  // Enable lua standard libraries
  luaL_openlibs(L);
  // On top of the stack
  lua_getglobal(L, "print");
  // Pass the below string as argument for the print() function
  lua_pushstring(L, "Hello, world from the C API!");
  // Aaand then... Calls the function!
  lua_call(L, 1, 0);
  // Destroy all the sh*t... And closes the lua runtime :)
  lua_close(L);

  return 0;
}
