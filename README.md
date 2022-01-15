## Common Layer Interface Library

This library is written in C++ for The Common Layer Interface (CLI) a universal format for the input of geometry data to model fabrication systems based on layer manufacturing technologies (LMT).
- The library provides templated data structures for deserializing ascii or binary CLI files.
- There are two main data structures: Header & Geometry. Header holds all of the parsed header data while the Geometry holds layers, which internally are composed of other data structures.

## Compilation
You will need visual studio for Microsoft windows. You can get the free community latest version from Microsoft website.
The code is all written from scratch and relies only on C++ standard library. So it is possible to compile the code for other platforms but not tested.

## Usage
- The main program is set to run using arguments. To display help:

```bash
 .\CLILayerAreaCalculator.exe  -help
```
Note: The only option supported right now is parsing of a single file in the main. To run the program with a single file, type:
```bash
 .\CLILayerAreaCalculator.exe  -path path/to/cli/file
```
