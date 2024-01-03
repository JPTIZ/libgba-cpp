project('gba-pong',
  'cpp',
  default_options: [
    'cpp_std=c++20',
  ])

libgba = dependency('libgba', fallback : ['libgba', 'libgba_dep'])

pong = executable('pong.gba',
  'main.cpp',
  dependencies : libgba)
