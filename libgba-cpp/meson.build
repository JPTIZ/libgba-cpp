subdir('arch')
subdir('engine')

libgba = static_library('gba',
  dependencies: [arch_dep, engine_dep, gba_runtime_dep],
)

libgba_dep = declare_dependency(
  include_directories : toplevel_inc,
  link_with : libgba)
