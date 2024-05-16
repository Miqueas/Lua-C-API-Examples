project('Lua-C-API-Examples', 'c',
  version: '0.1.0',
  license: 'zlib',
  meson_version: '>=0.53.0',
)

cc = meson.get_compiler('c')
system = host_machine.system()

subdir('deps' / 'lua54')
subdir('src')