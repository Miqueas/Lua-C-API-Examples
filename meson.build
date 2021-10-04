project('Lua-C-API', 'c', version: '0.1')

deps = [ dependency('lua5.1') ]

# Names for binaries/libraries, in the order as shown
# in the repo (01, 02, 03, ...)
names = [
  '01_hello_world',
  'hello',
  'mylib',
  '04_table',
  '05_metatable'
]

constants_cfg = {
  'table':     join_paths(meson.source_root(), '04_table.lua'),
  'metatable': join_paths(meson.source_root(), '05_metatable.lua')
}

configure_file(
  input: 'constants.h.in',
  output: 'constants.h',
  configuration: constants_cfg
)

configure_file(
  input: '02_gfunc.lua.in',
  output: '02_gfunc.lua',
  configuration: { 'gfunc': names[1] }
)

configure_file(
  input: '03_basic_lib.lua.in',
  output: '03_basic_lib.lua',
  configuration: { 'basic_lib': names[2] }
)

executable(names[0], '01_hello_world.c', dependencies: deps)

library(names[1], '02_gfunc.c',
  name_prefix: '',
  dependencies: deps,
  c_args: [ '-fPIC', '-shared' ]
)

library(names[2], '03_basic_lib.c',
  name_prefix: '',
  dependencies: deps,
  c_args: [ '-fPIC', '-shared' ]
)

executable(names[3], '04_table.c', dependencies: deps)
executable(names[4], '05_metatable.c', dependencies: deps)