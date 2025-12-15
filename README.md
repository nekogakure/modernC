# modernC
modernC is a library written in C that extends **readability, safety, and expressiveness**.

While it takes inspiration from the design philosophies of modern languages such as Rust, its highest priority is **not breaking C’s existing syntax, build systems, or toolchains**.  
Everything is completed **entirely on top of standard C**, requiring no special compiler or runtime.  
(Well… it does use some GCC extensions.)

## Overview
- Fundamental type definitions (integers, floating-point, bool, size types)
- Error handling centered around Result / Option
- Dynamic data structures (such as Vec)
- String representations (borrowed / owned)
- Attribute support
- And more

## Intended Use
For people who are interested in trying C++ or Rust but are not quite ready to take that step yet, and for enthusiasts.

## Requirements
- C23
- GCC or Clang

## License
See the [LICENSE](./LICENSE) file for details.

modernC is fully supported by [Arciris org](https://github.com/arciris-org).
