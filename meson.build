project('Lua-C-API-Examples', 'c', version: '0.1')

lua51_dep = dependency('lua5.1', required: true)
lua52_dep = dependency('lua5.2', required: true)
lua53_dep = dependency('lua5.3', required: true)

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

lua51_bin = find_program('lua5.1', 'lua51', required: false)
lua52_bin = find_program('lua5.2', 'lua52', required: false)
tests = get_option('tests')

if lua51_bin.found()
  summary({ 'Tests': tests })
else
  tests = false
  summary({ 'Tests (Lua interpreter not found)': tests })
endif

# Example 01: hello world
hello_world_exe = executable('01_hello_world', '01_hello_world.c', dependencies: lua51_dep)

# Example 02: global function
library('gfunc', '02_gfunc.c',
  name_prefix: '',
  dependencies: lua51_dep,
  c_args: [ '-fPIC', '-shared' ]
)

gfunc_lua = configure_file(
  input: '02_gfunc.lua.in',
  output: '02_gfunc.lua',
  configuration: { 'gfunc': 'gfunc' }
)

# Example 03: basic library
library('basic_lib', '03_basic_lib.c',
  name_prefix: '',
  dependencies: lua51_dep,
  c_args: [ '-fPIC', '-shared' ]
)

basic_lib_lua = configure_file(
  input: '03_basic_lib.lua.in',
  output: '03_basic_lib.lua',
  configuration: { 'basic_lib': 'basic_lib' }
)

# Example 04 & 05: table & metatable
configure_file(
  input: 'constants.h.in',
  output: 'constants.h',
  configuration: {
    'table':      meson.project_source_root() / '04_table.lua',
    'metatable':  meson.project_source_root() / '05_metatable.lua'
  }
)

table_exe = executable('04_table', '04_table.c', dependencies: lua51_dep)
metatable_exe = executable('05_metatable', '05_metatable.c', dependencies: lua51_dep)

# Example 06: userdata
library('userdata', '06_userdata.c',
  name_prefix: '',
  dependencies: lua51_dep,
  c_args: [ '-fPIC', '-shared' ]
)

userdata_lua = configure_file(
  input: '06_userdata.lua.in',
  output: '06_userdata.lua',
  configuration: { 'userdata': 'userdata' }
)

# Example 07: stack dump
stack_dump_exe = executable('07_stack_dump', '07_stack_dump.c', dependencies: lua51_dep)

# Example 08: versions
versions_51 = executable('08_versions_51', '08_versions.c', dependencies: lua51_dep)
versions_52 = executable('08_versions_52', '08_versions.c', dependencies: lua52_dep)
versions_53 = executable('08_versions_53', '08_versions.c', dependencies: lua53_dep)

# Example 09: newlib
library('newlib', '09_newlib.c',
  name_prefix: '',
  dependencies: lua52_dep,
  c_args: [ '-fPIC', '-shared' ]
)

newlib_lua = configure_file(
  input: '09_newlib.lua.in',
  output: '09_newlib.lua',
  configuration: { 'newlib': 'newlib' }
)

if tests
  test('01 hello world', hello_world_exe)
  # This example is expected to fail
  test('02 global function', lua51_bin, args: [ gfunc_lua ], should_fail: true)
  test('03 basic library', lua51_bin, args: [ basic_lib_lua ])
  test('04 table', table_exe)
  test('05 metatable', metatable_exe)
  test('06 userdata', lua51_bin, args: [ userdata_lua ])
  test('07 stack dump', stack_dump_exe)
  test('08 versions (5.1)', versions_51)
  test('08 versions (5.2)', versions_52)
  test('08 versions (5.3)', versions_53)
  test('09 newlib (5.2+)', lua52_bin, args: [ newlib_lua ])
endif