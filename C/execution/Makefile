# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -I.
LDFLAGS =

# Names and paths
STATIC_LIB = build/libstatic.a
SHARED_LIB = build/libshared.so
EXECUTABLE = build/library_demo

# Source files
STATIC_SRC = static_lib/static_lib.c
SHARED_SRC = shared_lib/shared_lib.c
MAIN_SRC = main.c

# Default target
all: $(EXECUTABLE)

# Build the static library
$(STATIC_LIB): $(STATIC_SRC)
	@echo "Building static library..."
	$(CC) $(CFLAGS) -c $(STATIC_SRC) -o build/static_lib.o
	ar rcs $(STATIC_LIB) build/static_lib.o

# Build the shared library
$(SHARED_LIB): $(SHARED_SRC)
	@echo "Building shared library..."
	$(CC) $(CFLAGS) -shared -fPIC $(SHARED_SRC) -o $(SHARED_LIB)

# Build the main executable with static and dynamic linking
$(EXECUTABLE): $(MAIN_SRC) $(STATIC_LIB) $(SHARED_LIB)
	@echo "Building main executable..."
	# Link against the static library by including it directly in the command line
	# Link against the shared library dynamically
	$(CC) $(CFLAGS) $(MAIN_SRC) $(STATIC_LIB) -L. -lshared -Wl,-rpath=. -o $(EXECUTABLE)

# Run the executable
run: $(EXECUTABLE)
	@echo "Running $(EXECUTABLE)..."
	./$(EXECUTABLE)

# Show library dependencies
dependencies: $(EXECUTABLE)
	@echo "Shared library dependencies:"
	ldd $(EXECUTABLE)
	@echo "\nStatic library linkage is not visible with ldd as it's embedded in the executable"

# Clean up
clean:
	rm -f $(EXECUTABLE) $(STATIC_LIB) $(SHARED_LIB) *.o *.so *.a

# Explain the differences between static and dynamic linking
explain:
	@echo "========================================================="
	@echo "EXPLANATION OF STATIC VS DYNAMIC LINKING"
	@echo "========================================================="
	@echo "1. STATIC LINKING (libstatic.a):"
	@echo "   - Library code is copied into the executable at compile time"
	@echo "   - Results in larger executable size"
	@echo "   - No runtime dependency on the library file"
	@echo "   - Cannot be updated without recompiling the executable"
	@echo ""
	@echo "2. DYNAMIC LINKING (libshared.so):"
	@echo "   - Library code is referenced but not included in executable"
	@echo "   - Results in smaller executable size"
	@echo "   - Runtime dependency on the library file"
	@echo "   - Can be updated without recompiling the executable"
	@echo ""
	@echo "Use 'make dependencies' to see the dynamic library dependencies"
	@echo "========================================================="

.PHONY: all run dependencies clean explain