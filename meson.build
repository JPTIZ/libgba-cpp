project('libgba-cpp',
  'cpp',
  default_options : [
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
