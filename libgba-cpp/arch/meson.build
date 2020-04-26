arch_src = files([
    'cpu/interrupts.cpp',
    'display/effects.cpp',
    'display/layers.cpp',
    'display/objects.cpp',
    'display/tilemap.cpp',
    'display/video.cpp',
    'display/window.cpp',
    'sound/directsound.cpp',
    'sound/sound.cpp',
  ])

arch_public_headers = files([
  'registers.h',
  'cpu/interrupts.h',
  'display/effects.h',
  'display/layers.h',
  'display/objects.h',
  'display/tilemap.h',
  'display/video.h',
  'display/window.h',
  'sound/directsound.h',
  'sound/sound.h',
  ])

install_headers(arch_public_headers)

arch = static_library(
  'libgba_arch',
  arch_src,
  include_directories : toplevel_inc,
)

arch_dep = declare_dependency(
  link_with : arch,
  include_directories : toplevel_inc,
)
