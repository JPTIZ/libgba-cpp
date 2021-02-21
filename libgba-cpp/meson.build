subdir('arch')
subdir('engine')

libgba = static_library('gba',
  dependencies: [arch_dep, engine_dep, gba_runtime_dep],
)

libgba_dep = declare_dependency(link_with : libgba)
