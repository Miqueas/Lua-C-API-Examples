lua51_dep = dependency('lua5.1')
lua52_dep = dependency('lua5.2')
lua53_dep = dependency('lua5.3')
lua54_dep = dependency('lua5.4')
lua51_bin = find_program('lua5.1', 'lua51')
lua52_bin = find_program('lua5.2', 'lua52')
tests = get_option('tests')

if lua51_bin.found()
  summary({ 'Tests': tests })
else
  tests = false
  summary({ 'Tests (Lua interpreter not found)': tests })
endif

# ==== Constants header used by some examples (04, 05 & 11) ==== #
configure_file(
  input: 'constants.h.in',
  output: 'constants.h',
  configuration: {
    'table':     meson.project_source_root() / 'src' / '04-table.lua',
    'metatable': meson.project_source_root() / 'src' / '05-metatable.lua',
    'hooks':     meson.project_source_root() / 'src' / '11-hooks.lua'
  }
)
# ==== Example 01: hello world ==== #
hello_world_exe = executable('01-hello-world', '01-hello-world.c', dependencies: lua51_dep)

# ==== Example 02: global function ==== #
library('gfunc', '02-gfunc.c',
  name_prefix: '',
  dependencies: lua51_dep,
  c_args: [ '-fPIC', '-shared' ]
)

gfunc_lua = configure_file(
  input: '02-gfunc.lua.in',
  output: '02-gfunc.lua',
  configuration: { 'gfunc': 'gfunc' }
)

# ==== Example 03: basic library ==== #
library('basiclib', '03-basic-lib.c',
  name_prefix: '',
  dependencies: lua51_dep,
  c_args: [ '-fPIC', '-shared' ]
)

basic_lib_lua = configure_file(
  input: '03-basic-lib.lua.in',
  output: '03-basic-lib.lua',
  configuration: { 'basiclib': 'basiclib' }
)

# ==== Example 04: table ==== #
table_exe = executable('04-table', '04-table.c', dependencies: lua51_dep)

# ==== Example 05: metatable ==== #
metatable_exe = executable('05-metatable', '05-metatable.c', dependencies: lua51_dep)

# ==== Example 06: userdata ==== #
library('userdata', '06-userdata.c',
  name_prefix: '',
  dependencies: lua51_dep,
  c_args: [ '-fPIC', '-shared' ]
)

userdata_lua = configure_file(
  input: '06-userdata.lua.in',
  output: '06-userdata.lua',
  configuration: { 'userdata': 'userdata' }
)

# ==== Example 07: stack dump ==== #
stack_dump_exe = executable('07-stack-dump', '07-stack-dump.c', dependencies: lua51_dep)

# ==== Example 08: versions ==== #
versions_51_exe = executable('08-versions-51', '08-versions.c', dependencies: lua51_dep)
versions_52_exe = executable('08-versions-52', '08-versions.c', dependencies: lua52_dep)
versions_53_exe = executable('08-versions-53', '08-versions.c', dependencies: lua53_dep)
versions_54_exe = executable('08-versions-54', '08-versions.c', dependencies: lua54_dep)

# ==== Example 09: newlib ==== #
library('newlib', '09-newlib.c',
  name_prefix: '',
  dependencies: lua52_dep,
  c_args: [ '-fPIC', '-shared' ]
)

newlib_lua = configure_file(
  input: '09-newlib.lua.in',
  output: '09-newlib.lua',
  configuration: { 'newlib': 'newlib' }
)

# ==== Example 10: functions ==== #
library('addfn', '10-functions.c',
  name_prefix: '',
  dependencies: lua51_dep,
  c_args: [ '-fPIC', '-shared' ]
)

addfn_lua = configure_file(
  input: '10-functions.lua.in',
  output: '10-functions.lua',
  configuration: { 'addfn': 'addfn' }
)

# ==== Example 11: hooks ==== #
hooks_exe = executable('11-hooks', '11-hooks.c', dependencies: lua51_dep)

if tests
  test('01 hello world', hello_world_exe)
  # This example is expected to fail
  test('02 global function', lua51_bin, args: [ gfunc_lua ], should_fail: true)
  # Setting the 'LUA_CPATH' env prevents the test to fail. This is 'cuz Lua will not find the .so file otherwise if you
  # run `meson test` from other directory
  test('03 basic library', lua51_bin, args: [ basic_lib_lua ], env: { 'LUA_CPATH': meson.build_root() / 'src' / '?.so' })
  test('04 table', table_exe)
  test('05 metatable', metatable_exe)
  test('06 userdata', lua51_bin, args: [ userdata_lua ], env: { 'LUA_CPATH': meson.build_root() / 'src' / '?.so' })
  test('07 stack dump', stack_dump_exe)
  test('08 versions (5.1)', versions_51_exe)
  test('08 versions (5.2)', versions_52_exe)
  test('08 versions (5.3)', versions_53_exe)
  test('08 versions (5.4)', versions_54_exe)
  test('09 newlib (5.2+)', lua52_bin, args: [ newlib_lua ], env: { 'LUA_CPATH': meson.build_root() / 'src' / '?.so' })
  test('10 functions', lua51_bin, args: [ addfn_lua ], env: { 'LUA_CPATH': meson.build_root() / 'src' / '?.so' })
  test('11 hooks', hooks_exe)
endif
