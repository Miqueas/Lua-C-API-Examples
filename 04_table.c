#include <stdio.h>
#include "constants.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

int main(int argc, char **argv) {
  lua_State *L = luaL_newstate();
  int verbose = 0;

  int err = luaL_dofile(L, TABLE_PATH);
  if (err) {
    fprintf(stderr, "Can't load lua code\n");
    return 1;
  } else {
    // The table 'Config' is the first element added to the stack, so
    // the absolute index for it'll be 1
    lua_getglobal(L, "Config");
    // Now we have 2 items, but the 'Config' table is still in the index 1,
    // 'cause is the "first in, last out"
    lua_pushstring(L, "verbose");
    lua_rawget(L, 1);

    // To prevent care about how many items is in the stack, I use the -1 index,
    // that means, the last push item in the stack (the string "verbose"). But
    // the -1 index isn't the string "verbose", 'cause when I called lua_rawget(),
    // it replaces the string with the value that the 'Config' table stores in
    // the key "verbose". See: https://www.lua.org/manual/5.1/manual.html#lua_gettable
    if (lua_toboolean(L, -1)) {
      verbose = 1;
      printf("Loaded config\n");
    }

    lua_pushstring(L, "enable_std");
    lua_rawget(L, 1);

    if (lua_toboolean(L, -1)) {
      luaL_openlibs(L);
      if (verbose) printf("Loaded standard libraries\n");
    }

    lua_pushstring(L, "name");
    lua_rawget(L, 1);
    const char *name = lua_tostring(L, -1);
    if (verbose) printf("name = %s\n", name);

    lua_pushstring(L, "access");
    lua_rawget(L, 1);
    const char *access = lua_tostring(L, -1);
    if (verbose) printf("access = %s\n", access);
  }

  lua_close(L);

  return 0;
}
