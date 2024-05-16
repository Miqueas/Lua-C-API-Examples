# Note: this tries to be a translation of the Lua 5.4 Makefile to Meson.

lua54_cflags = [ '-std=gnu99', '-O2', '-Wall', '-Wextra', '-DLUA_COMPAT_5_3', ]
lua54_cflags += cc.get_supported_arguments('-Wno-string-plus-int', '-Wno-stringop-overflow')
lua54_ldflags = [ '-lm' ]

if system == 'freebsd' or system == 'netbsd' or system == 'openbsd'
  lua54_cflags += [
    '-DLUA_USE_LINUX',
    '-DLUA_USE_READLINE',
    '-I/usr/include/edit',
  ]

  lua54_ldflags += [ '-Wl,-E', '-ledit', ]
elif system == 'linux'
  lua54_cflags += '-DLUA_USE_LINUX'
  lua54_ldflags += [ '-Wl,-E', '-ldl', ]

  if dependency('readline', required: false).found()
    lua54_cflags += '-DLUA_USE_READLINE'
    lua54_ldflags += '-lreadline'
  endif
elif system == 'windows'
  lua54_cflags += '-DLUA_BUILD_AS_DLL'
  lua54_ldflags = [ '-s' ]
elif system == 'sunos'
  lua54_cflags += [ '-DLUA_USE_POSIX', '-DLUA_USE_DLOPEN', '-D_REENTRANT' ]
  lua54_ldflags += '-ldl'
elif system not in [ 'windows', 'emscripten', 'android', 'darwin', 'linux', 'freebsd', 'netbsd', 'openbsd', 'sunos' ]
  lua54_cflags += '-DLUA_USE_POSIX'
endif

lua54_sources = [
  # core
  'lapi.c',
  'lcode.c',
  'lctype.c',
  'ldebug.c',
  'ldo.c',
  'ldump.c',
  'lfunc.c',
  'lgc.c',
  'llex.c',
  'lmem.c',
  'lobject.c',
  'lopcodes.c',
  'lparser.c',
  'lstate.c',
  'lstring.c',
  'ltable.c',
  'ltm.c',
  'lundump.c',
  'lvm.c',
  'lzio.c',

  # lib
  'lauxlib.c',
  'lbaselib.c',
  'lcorolib.c',
  'ldblib.c',
  'liolib.c',
  'lmathlib.c',
  'loadlib.c',
  'loslib.c',
  'lstrlib.c',
  'ltablib.c',
  'lutf8lib.c',
  'linit.c',
]

lua54_version = meson.project_version().split('.')
lua54_headers = include_directories('.')

liblua54 = static_library('lua', lua54_sources
  # version: meson.project_version(),
  # soversion: version[0] + '.' + version[1],
)

lua54_exe = executable('lua', 'lua.c',
  c_args: lua54_cflags,
  link_args: lua54_ldflags,
  link_with: liblua54,
)

luac54_exe = executable('luac', 'luac.c',
  c_args: lua54_cflags,
  link_args: lua54_ldflags,
  link_with: liblua54,
)