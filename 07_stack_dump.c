#include <stdio.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#define LCODE "return 29, nil, true, \"str\", io.stdin, function()end, {}"

/* In this example we write a C function that iterates over the given
 * stack, makes a simple string representation of the items and finally
 * prints it as a more user friendly string
 */

void stack_dump(lua_State *L);

int main(int argc, char **argv) {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  int err = luaL_dostring(L, LCODE);
  if (err) {
    fprintf(stderr, "Can't load Lua string\n");
    return 1;
  }

  stack_dump(L);
  lua_close(L);

  return 0;
}

void stack_dump(lua_State *L) {
  // Gets the amount of items in the stack
  int top = lua_gettop(L);

  printf("stack: [ ");

  // Interates in the stack, gets the type of every item
  // and makes a simple string representation of it
  for (int i = 1; i <= top; i++) {
    int t = lua_type(L, i);

    switch (t) {
      case LUA_TNIL: {
        printf("nil");
        break;
      }

      case LUA_TBOOLEAN: {
        printf(lua_toboolean(L, i) ? "true" : "false");
        break;
      }

      case LUA_TLIGHTUSERDATA: {
        printf("lightuserdata@(%p)", lua_touserdata(L, i));
        break;
      }

      case LUA_TNUMBER: {
        printf("%g", lua_tonumber(L, i));
        break;
      }

      case LUA_TSTRING: {
        printf("\"%s\"", lua_tostring(L, i));
        break;
      }

      case LUA_TTABLE: {
        printf("(table)");
        break;
      }

      case LUA_TFUNCTION: {
        printf("(function)");
        break;
      }

      case LUA_TUSERDATA: {
        printf("userdata@(%p)", lua_touserdata(L, i));
        break;
      }

      case LUA_TTHREAD: {
        printf("thread@(%p)", lua_touserdata(L, i));
      }

      default: {
        printf("(%s)", lua_typename(L, t));
        break;
      }
    }

    if (i<top) printf(" ");
  }

  printf(" ]\n");
}