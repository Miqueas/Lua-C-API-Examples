#include <stdio.h>
#include <string.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#define LIBBOOK_NAME "Book"

/*
In this example, we're pushing userdata to Lua.

Our userdata to push, a simple "Book" object type.
*/

typedef struct {
  char *title;
  char *author;
  int   pages;
  int   year;
} Book;

int book_sayhello(lua_State *L);

int book__new(lua_State *L);

int book_sayhello(lua_State *L) {
  printf("\r\nHello world from book_sayhello()!\r\n");

  return 0;
}

int luaopen_userdata(lua_State *L) {
  lua_register(L, LIBBOOK_NAME, book__new);

  return 1;
}

int book__new(lua_State *L) {
  char *title  = (char*) luaL_checkstring(L, 1);
  char *author = (char*) luaL_checkstring(L, 2);
  int   pages  = luaL_checkint(L, 3);
  int   year   = luaL_checkint(L, 4);

  /*Cleans the stack*/
  lua_settop(L, 0);

  /*lua_newuserdata() is used like malloc()*/
  Book *b = (Book *) lua_newuserdata(L, sizeof(Book));
  b->title  = title;
  b->author = author;
  b->pages  = pages;
  b->year   = year;

  /*Add table to add variables and functions*/  
  luaL_newmetatable(L, LIBBOOK_NAME);

  /*Add index*/
  lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");

  /*Add functions*/
  /*
  lua api functions commonly work with the top of the stack as arguments as well as output
  */
  lua_pushcfunction(L, book_sayhello); lua_setfield(L, -2, "sayhello");

  /*Add variables*/
  /*
  lua api functions commonly work with the top of the stack as arguments as well as output
  */
  lua_pushstring(L, b->title); lua_setfield(L, -2, "title");
  lua_pushstring(L, b->author); lua_setfield(L, -2, "author");
  lua_pushinteger(L, b->pages); lua_setfield(L, -2, "pages");
  lua_pushinteger(L, b->year); lua_setfield(L, -2, "year");

  /*Add metatable to userdata*/
  lua_setmetatable(L, 1);

  return 1;
}
