engine_src = files([
  'input.cpp',
  'graphics/bitmap.cpp',
  'graphics/palette.cpp',
  ])


engine_public_headers = files([
  'input.h',
  'graphics/bitmap.h',
  'graphics/graphics.h',
  'graphics/map.h',
  'graphics/maps.h',
  'graphics/palette.h',
  'graphics/tilemap.h',
  ])

install_headers(engine_public_headers)

engine = static_library(
  'libgba_engine',
  engine_src,
  include_directories : [toplevel_inc, include_directories('.')],
)

engine_dep = declare_dependency(
  link_with: engine,
  include_directories : [toplevel_inc, include_directories('.')],
)
