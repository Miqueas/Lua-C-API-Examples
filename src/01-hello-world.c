#include <stdio.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

/*
 * Classic "hello world" example. This essentially creates a Lua runtime and
 * then calls: print("Hello, world!")
 */

int main(void) {
  // Creates a new lua runtime
  lua_State *L = luaL_newstate();
  // Enable lua standard libraries
  luaL_openlibs(L);
  // Push on top of the stack the `print` function
  lua_getglobal(L, "print");
  // Push the string that will be passed to the `print` function,
  // now this is the top of the stack
  lua_pushstring(L, "Hello, world from the C API!");
  // And finally, we call the function. Please, check the reference manual
  // for details of how this works
  lua_call(L, 1, 0);
  // After that, we close the runtime (note that this destroys any value
  // in the stack too)
  lua_close(L);

  return 0;
}
