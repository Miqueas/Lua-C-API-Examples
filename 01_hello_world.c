#include <stdio.h>
#include <stdlib.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

/*
 * Classic "hello world" example. This essentially creates a Lua runtime and
 * then calls: print("Hello, world!")
 */
int main(int argc, char **argv) {
  // Creates a new lua runtime
  lua_State *lvm = luaL_newstate();
  // Enable lua standard libraries
  luaL_openlibs(lvm);
  // On top of the stack
  lua_getglobal(lvm, "print");
  // Pass the below string as argument for the print() function
  lua_pushstring(lvm, "Hello, world from the C API!");
  // Aaand then... Calls the function!
  lua_call(lvm, 1, 0);
  // Destroy all the sh*t... And closes the lua runtime :)
  lua_close(lvm);

  return 0;
}