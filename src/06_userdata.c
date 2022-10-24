#include <stdio.h>
#include <string.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#define str_arr_len(a) (sizeof(a) / sizeof(*a[0]))

typedef struct {
  char *title;
  char *author;
  int   pages;
  int   year;
} Book;

int book___index(lua_State *L);

int new_book(lua_State *L) {
  char *title  = (char*) luaL_checkstring(L, 1);
  char *author = (char*) luaL_checkstring(L, 2);
  int   pages  = luaL_checkint(L, 3);
  int   year   = luaL_checkint(L, 4);

  // Cleans the stack
  lua_settop(L, 0);

  // lua_newuserdata() is used like malloc()
  Book *b = (Book *) lua_newuserdata(L, sizeof(Book));
  b->title  = title;
  b->author = author;
  b->pages  = pages;
  b->year   = year;
  
  // stack: Book(userdata), table
  lua_newtable(L);
  // stack: Book(userdata), table, "__index"
  lua_pushstring(L, "__index");
  // stack: Book(userdata), table, "__index", cfunction
  lua_pushcfunction(L, book___index);
  // stack: Book(userdata), table
  lua_rawset(L, 2);
  // stack: Book(userdata)
  lua_setmetatable(L, 1);

  return 1;
}

int book___index(lua_State *L) {
  Book *self = (Book *) lua_touserdata(L, 1);
  const char *k = lua_tostring(L, 2);

  if (!strcmp(k, "title"))
    lua_pushstring(L, self->title);
  else if (!strcmp(k, "author"))
    lua_pushstring(L, self->author);
  else if (!strcmp(k, "pages"))
    lua_pushinteger(L, (lua_Integer) self->pages);
  else if (!strcmp(k, "year"))
    lua_pushinteger(L, (lua_Integer) self->year);
  else
    lua_pushnil(L);

  return 1;
}

int luaopen_book(lua_State *L) {
  lua_pushcfunction(L, new_book);

  return 1;
}