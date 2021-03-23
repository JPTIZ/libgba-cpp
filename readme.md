LibGBA - CPP
============

What is it?
-----------

It's a C++ library for GBA homebrew development. Focused on better API and
abstraction, so programmers can focus more on game logic and call functions for
effects instead of thinking in a too low-level way.

Requirements
------------

A lot of statements are being written with C++11/14/17 features, so, the
requirements are:

- **Toolchain**: DevKitPro (to compile for GBA ARMv4 ISA and ARM7TDMI
  processor).
- **Compiler**: GCC 7.1 or above;
- **Build-system**: Meson

Examples
--------

- [AlphaBlending (BG Layers)](tests/alphablend)
- [Generated Tilemaps](tests/gen_tilemap)
- [Interrupts](tests/interrupts)
- [Mode5](tests/mode5)
- [Mosaic](tests/mosaic)
- [Sound](tests/sound)
- [Tilemap](tests/tilemap)
- [Windowing](tests/windowing)

Building
--------

To build this project, after installing the [Requirements](#Requirements) and
cloning this repository, enter the cloned repository's directory and run:

```console
$ meson build --cross-file cross_file.ini
```

If you want to build examples as well, add `-Dbuild-tests=true` to the command:

```console
$ meson build -Dbuild-tests=true
```

Running examples
----------------

After building the examples (see [Building](#Building)), you'll need a GBA
emulator. My personal recommendations are:
- [MGBA](https://mgba.io/): an open-source fully-featured GBA emulator with a
  lot of cool debugging tools. Can also link with GDB for a professional
  in-depth debugging.
- [Visual Boy Advance-M](https://vba-m.com/): continuation of the almighty
  legendary VisualBoyAdvance.

Examples are compiled into the `build/tests` directory. So to run, say,
`alphablend` example, you should open `build/tests/alphablend.gba` with your
emulator.

Documentation
-------------

- [API Documentation](https://jptiz.github.io/libgba-cpp/index.html)

To-Do's
-------

[Check issues](https://github.com/JPTIZ/libgba-cpp/issues).

Bibliography
------------

There are two main contributions for the knowledge necessary to make this
library: one is the greatly well explained tutorials [TONC by J
Vijn](http://www.coranac.com/tonc/text/toc.htm) (which I really want to thank
him for making it), and the other is the great [GBA Techical Manual by Martin
Korth](http://problemkaputt.de/gbatek.htm).
