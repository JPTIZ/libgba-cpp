project('libgba-cpp',
  'cpp',
  default_options : [
    'cpp_std=c++17',
    'warning_level=3',
  ],
)

add_global_arguments(['-mthumb-interwork',
            '-fomit-frame-pointer',
            '-ffast-math'], language: 'cpp')

toplevel_inc = include_directories('.')

subdir('libgba-cpp')
