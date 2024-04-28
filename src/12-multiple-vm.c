#include <stdio.h>
#include <pthread.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "constants.h"

/* Using multiple Lua VM's in the same program */

void *luaThread1(void *_) {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  int error = luaL_dofile(L, THREADED_PATH);

  if (error) {
    fprintf(stderr, "Thread 3: Error. Code: %d\n", error);
    lua_close(L);
    return NULL;
  }

  lua_getglobal(L, "thread1");
  lua_call(L, 0, 0);
  lua_getglobal(L, "print");
  lua_pushstring(L, "\n\n");
  lua_call(L, 1, 0);
  lua_close(L);

  return NULL;
}

void *luaThread2(void *_) {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  int error = luaL_dofile(L, THREADED_PATH);

  if (error) {
    fprintf(stderr, "Thread 3: Error. Code: %d\n", error);
    lua_close(L);
    return NULL;
  }

  lua_getglobal(L, "thread2");
  lua_call(L, 0, 0);
  lua_getglobal(L, "print");
  lua_pushstring(L, "\n\n");
  lua_call(L, 1, 0);
  lua_close(L);

  return NULL;
}

void *luaThread3(void *_) {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  int error = luaL_dofile(L, THREADED_PATH);

  if (error) {
    fprintf(stderr, "Thread 3: Error. Code: %d\n", error);
    lua_close(L);
    return NULL;
  }

  lua_getglobal(L, "thread3");
  lua_pushinteger(L, (lua_Integer) 29);
  lua_pushinteger(L, (lua_Integer) 69);
  lua_call(L, 2, 1);
  lua_Integer result = luaL_checkinteger(L, 1);
  lua_getglobal(L, "print");
  lua_pushstring(L, "Thread 3 result: ");
  lua_pushinteger(L, result);
  lua_pushstring(L, "\n\n");
  lua_call(L, 3, 0);
  lua_close(L);

  return NULL;
}

int main(void) {
  pthread_t thread1;
  pthread_t thread2;
  pthread_t thread3;

  pthread_create(&thread1, NULL, luaThread1, NULL);
  pthread_join(thread1, NULL);
  pthread_create(&thread2, NULL, luaThread2, NULL);
  pthread_join(thread2, NULL);
  pthread_create(&thread3, NULL, luaThread3, NULL);
  pthread_join(thread3, NULL);

  return 0;
}