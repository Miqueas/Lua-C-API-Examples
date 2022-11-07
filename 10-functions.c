#include <stdio.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

/* In this example I'll explain how C functions works with Lua
 * (a bit late I guess)
 */

int add(lua_State *L);

int luaopen_addfn(lua_State *L) {
  lua_pushcfunction(L, add);

  return 1;
}

// When a C function is called from Lua, the argumments are
// passed in the `lua_State *L`
int add(lua_State *L) {
  // First argument, stack index 1
  lua_Number x = luaL_checknumber(L, 1);
  // Second argument, stack index 2
  lua_Number y = luaL_checknumber(L, 2);

  // Then, to return the value, we just push in the stack
  lua_pushnumber(L, x + y);

  // And finally, we indicate that this function returns
  // `n` values, in this case, we just return one value
  return 1;
}