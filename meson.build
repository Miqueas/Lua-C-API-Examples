project('Lua-C-API', 'c', version: '0.1')

deps = [ dependency('lua5.1') ]

executable('01_hello_world', '01_hello_world.c',
  dependencies: deps
)

library('hello', '02_gfunc.c',
  name_prefix: '',
  dependencies: deps,
  c_args: [ '-fPIC', '-shared' ]
)

library('mylib', '03_basic_lib.c',
  name_prefix: '',
  dependencies: deps,
  c_args: [ '-fPIC', '-shared' ]
)

executable('04_table', '04_table.c',
  dependencies: deps
)