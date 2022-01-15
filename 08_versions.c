#include <stdio.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

int main(int argc, char **argv) {
  #if LUA_VERSION_NUM == 501
  printf("Lua version: 5.1\n");
  #elif LUA_VERSION_NUM == 502
  printf("Lua version: 5.2\n");
  #elif LUA_VERSION_NUM == 503
  printf("Lua version: 5.3\n");
  #elif LUA_VERSION_NUM == 504
  printf("Lua version: 5.4\n");
  #endif

  return 0;
}