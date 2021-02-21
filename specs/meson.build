specs_in_files = files([
    'gba.specs.in'
  ])

specs_output = 'gba.specs'

specs_conf = configuration_data({
  'SPECS_DIR' : meson.current_source_dir(),
  'CRT0_DIR' : meson.current_build_dir(),
})

specs_gen_file = configure_file(
  input : 'gba.specs.in',
  output : specs_output,
  configuration : specs_conf,
)

specs_path = meson.current_build_dir() / specs_output

gba_crt0 = custom_target(
  'gba_crt0',
  input : 'gba_crt0.s',
  output : 'gba_crt0.o',
  command : ['arm-none-eabi-gcc', '-c', '@INPUT@', '-o', '@OUTPUT@'],
)

gba_runtime_dep = declare_dependency(
  sources : gba_crt0,
  link_args : '-specs=@0@'.format(specs_path)
)
