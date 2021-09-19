# Lua-C-API

A personal repo where I want to push things while I'm learning the Lua C API

## Building

If you want to build this, you'll need Meson and Lua 5.1 development files and then:

```
meson . _BUILD
ninja -C _BUILD
```

And in the `_BUILD` folder you'll see the compiled files

## About the Lua stack

There's some good reads that can help to understand the Lua stack:

 * [Stack (Wikipedia)][StackWikipedia] &ndash; _This was really helpful for me (mostly the simple illustration with 6 elements)_
 * [Understanding the lua stack][UnderstandingStack] &ndash; _A set of articles I found about the stack_
 * [The Stack][LuaManual] &ndash; _The official Lua manual explain how indexing the stack works, and tells about absolute and relative indexes_

[StackWikipedia]: https://en.wikipedia.org/wiki/Stack_(abstract_data_type)
[UnderstandingStack]: https://szpg1108.wordpress.com/2013/08/07/understanding-the-lua-stack-pt-1-the-basics/
[LuaManual]: https://www.lua.org/manual/5.1/manual.html#3.1