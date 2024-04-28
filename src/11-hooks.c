#include <stdio.h>
#include "constants.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

void lineHook(lua_State *L, lua_Debug *ar) {
  printf("Line execution!\n");
  printf("Details:\n");

  // Depending on what hook we handle, `ar` will be partially filled in some
  // fields, so we need to manually full fill it
  lua_getinfo(L, "nS", ar);

  if (ar->name != NULL) {
    printf(" -> name: %s\n", ar->name);
    printf(" -> namewhat: %s\n", ar->namewhat);
  }

  printf(" -> what: %s\n", ar->what);
  printf(" -> source: %s\n", ar->source);
  printf(" -> currentline: %d\n", ar->currentline);
}

int main(void) {
  lua_State *vm = luaL_newstate();
  lua_sethook(vm, lineHook, LUA_MASKLINE, 0);
  luaL_openlibs(vm);
  int err = luaL_dofile(vm, HOOKS_PATH);
  printf("Code: %d\n", err);
  lua_close(vm);

  return 0;
}