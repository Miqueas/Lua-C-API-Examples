project('Lua-C-API', 'c', version: '0.1')

deps = [ dependency('lua5.1', required: true) ]

# Names for binaries/libraries, in the order as shown
# in the repo (01, 02, 03, ...)
names = [
  '01_hello_world',
  'hello',
  'mylib',
  '04_table',
  '05_metatable',
  'book',
  '07_stack_dump'
]

lua = find_program('lua5.1', 'lua51', required: false)
tests = get_option('tests')

if lua.found()
  summary({ 'Tests': tests })
else
  tests = false
  summary({ 'Tests (Lua interpreter not found)': tests })
endif

configure_file(
  input: 'constants.h.in',
  output: 'constants.h',
  configuration: {
    'table':      meson.project_source_root() / '04_table.lua',
    'metatable':  meson.project_source_root() / '05_metatable.lua'
  }
)

gfunc_lua = configure_file(
  input: '02_gfunc.lua.in',
  output: '02_gfunc.lua',
  configuration: { 'gfunc': names[1] }
)

basic_lib_lua = configure_file(
  input: '03_basic_lib.lua.in',
  output: '03_basic_lib.lua',
  configuration: { 'basic_lib': names[2] }
)

userdata_lua = configure_file(
  input: '06_userdata.lua.in',
  output: '06_userdata.lua',
  configuration: { 'book': names[5] }
)

hello_world_exe = executable(names[0], '01_hello_world.c', dependencies: deps)

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

table_exe = executable(names[3], '04_table.c', dependencies: deps)
metatable_exe = executable(names[4], '05_metatable.c', dependencies: deps)

library(names[5], '06_userdata.c',
  name_prefix: '',
  dependencies: deps,
  c_args: [ '-fPIC', '-shared' ]
)

stack_dump_exe = executable(names[6], '07_stack_dump.c', dependencies: deps)

if tests
  test('01 hello world', hello_world_exe)
  # This example is expected to fail
  test('02 global function', lua, args: [ gfunc_lua ], should_fail: true)
  test('03 basic library', lua, args: [ basic_lib_lua ])
  test('04 table', table_exe)
  test('05 metatable', metatable_exe)
  test('06 userdata', lua, args: [ userdata_lua ])
  test('07 stack dump', stack_dump_exe)
endif