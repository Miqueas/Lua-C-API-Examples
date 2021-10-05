# Lua-C-API

A personal repo where I push things while I'm learning the Lua C API! Feel free to contribute :)

## Building

If you want to build this, you'll need Meson and Lua 5.1 development files and then:

```
meson . _BUILD
ninja -C _BUILD
```

And in the `_BUILD` folder you'll see the compiled files

## References

I mainly readed the [Official Reference Manual][LuaManual] but I also saw this:

 * [Veinin/lua-c-api-tutorial][lua-c-api-tutorial] &ndash; _First steps_
 * [Stack (Wikipedia)][StackWikipedia] &ndash; _The simple illustration with numbers was really helpful_
 * [Understanding the lua stack][UnderstandingStack] &ndash; _A set of articles I found about the stack_
 * [tylerneylon/lua_api_demo][api_demo_repo] &ndash; _Here I learned how to use the `lua_newuserdata` function_

And finally, thanks to the members of the [Telegram Group][TelegramGroup]!

## Why Lua 5.1?

Yes :heavy_check_mark:

[StackWikipedia]: https://en.wikipedia.org/wiki/Stack_(abstract_data_type)
[UnderstandingStack]: https://szpg1108.wordpress.com/2013/08/07/understanding-the-lua-stack-pt-1-the-basics/
[LuaManual]: https://www.lua.org/manual/5.1/manual.html#3
[api_demo_repo]: https://github.com/tylerneylon/lua_api_demo
[lua-c-api-tutorial]: https://github.com/Veinin/lua-c-api-tutorials
[TelegramGroup]: https://t.me/LuaLang