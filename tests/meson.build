generic_test_dirs = [
  'alphablend',
  'interrupts',
  'mode5',
  'mosaic',
  'sound',
  'windowing',
  ]

foreach test_dir : generic_test_dirs
  test_rom = executable('@0@.gba'.format(test_dir),
    files(test_dir / 'main.cpp'),
    dependencies : libgba_dep,
  )
endforeach

custom_tests = [
  'gen_tilemap',
  ]

foreach test_dir : custom_tests
  subdir(test_dir)
endforeach
