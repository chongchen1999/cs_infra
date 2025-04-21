# Understanding C Execution Mechanisms: Static and Dynamic Linking

This project demonstrates the fundamental execution mechanisms in C programming, focusing on libraries and linking. Here's a breakdown of the key concepts:

## 1. Static Libraries (`libstatic.a`)

Static libraries are collections of object files that are linked with the application at **compile time**:

- The library code becomes part of the executable
- No external dependencies at runtime
- Larger executable size but potentially faster execution
- Changes to the library require recompilation of the application

In our project, we create a static library (`libstatic.a`) that contains the implementation of `static_operation()` and `static_lib_info()` functions.

## 2. Shared/Dynamic Libraries (`libshared.so`)

Shared libraries are loaded into memory at **runtime**:

- The library code remains separate from the executable
- External dependency at runtime
- Smaller executable size
- Libraries can be updated without recompiling the application
- Multiple applications can share one copy of the library in memory

Our project includes a shared library (`libshared.so`) that implements `shared_operation()` and `shared_lib_info()` functions.

## 3. Symbol Visibility

The project demonstrates how to control symbol visibility:

- In the static library: The `library_version` variable is declared as `static`, making it accessible only within its source file
- In the shared library: We use proper export macros to control which symbols are exposed to applications

## 4. Library Initialization and Cleanup

The shared library demonstrates special initialization and cleanup functions:

- `__attribute__((constructor))`: Called automatically when the library is loaded
- `__attribute__((destructor))`: Called automatically when the library is unloaded

## 5. Build Process

The Makefile illustrates the different build steps:

- Static library: Compiled into object files, then archived with `ar`
- Shared library: Compiled with `-shared` and `-fPIC` flags
- Executable: Statically linked with `libstatic.a` and dynamically linked with `libshared.so`

## 6. Runtime Analysis

You can observe the dynamic linking in action:

- Use `ldd ./library_demo` to see the shared library dependencies
- The static library isn't visible in the `ldd` output because it's embedded in the executable

## Build and Run Instructions

1. Clone or extract the project
2. Run `make` to build everything
3. Run `make run` to execute the program
4. Run `make dependencies` to see library dependencies
5. Run `make explain` for a brief explanation of static vs dynamic linking
6. Run `make clean` to remove all built files

## How This Demonstrates C Execution Mechanisms

1. **Compile-Time vs Runtime Linking**: You can observe the difference between linking that happens at compile time (static) vs runtime (dynamic)
2. **Symbol Resolution**: Different ways symbols are resolved in each linking method
3. **Library Loading**: The shared library demonstrates automatic initialization when loaded
4. **Memory Management**: Different approaches to code sharing between libraries and applications
5. **Building Process**: The Makefile shows the different compilation flags needed for each library type