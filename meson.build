project('libgba-cpp',
  'cpp',
  version : '0.1.0',
  default_options : [
    'backend=ninja',
    'cpp_std=c++17',
    'warning_level=3',
  ],
)

toplevel_inc = include_directories('.')

subdir('specs')
subdir('libgba-cpp')

if get_option('build-tests')
  subdir('tests')
endif
