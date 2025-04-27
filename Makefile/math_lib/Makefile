# Math Library Project Makefile
# =============================

# Project configuration
PROJECT := mathlib
VERSION := 1.0.0

# Directory structure
SRCDIR := src
INCDIR := include
OBJDIR := obj
BINDIR := bin
TESTDIR := test

# Compiler settings
CC := gcc
CFLAGS := -Wall -Wextra -pedantic -I$(INCDIR)
LDFLAGS := -lm

# Find all source files
SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))
DEPS := $(OBJECTS:.o=.d)

# Main target and executable
TARGET := $(BINDIR)/$(PROJECT)

# Set default build type if not specified
BUILD_TYPE ?= release

# Configure flags based on build type
ifeq ($(BUILD_TYPE),debug)
    CFLAGS += -g -DDEBUG
    TARGET_DIR := debug
else ifeq ($(BUILD_TYPE),release)
    CFLAGS += -O2 -DNDEBUG
    TARGET_DIR := release
else
    $(error Unknown build type: $(BUILD_TYPE))
endif

# Set defaults for optional silent mode
V ?= 0
ifeq ($(V),1)
    # Verbose mode - show commands
    Q :=
    ECHO = @true
else
    # Quiet mode - hide commands, show simplified output
    Q := @
    ECHO = @echo
endif

# Ensure directories exist
$(shell mkdir -p $(OBJDIR) $(BINDIR))

# Default target
.PHONY: all
all: $(TARGET)

# Linking the final executable
$(TARGET): $(OBJECTS)
	$(ECHO) "LD $@"
	$(Q)$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	$(ECHO) "Build complete! Run with: $@"

# Compile C sources with automatic dependency generation
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(ECHO) "CC $<"
	$(Q)$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Create object directory if it doesn't exist
$(OBJDIR):
	$(Q)mkdir -p $@

# Include generated dependencies
-include $(DEPS)

# Clean build files
.PHONY: clean
clean:
	$(ECHO) "Cleaning build files..."
	$(Q)rm -rf $(OBJDIR)/*.o $(OBJDIR)/*.d $(TARGET)
	$(ECHO) "Clean complete!"

# Deep clean (remove all generated files)
.PHONY: distclean
distclean: clean
	$(ECHO) "Performing deep clean..."
	$(Q)rm -rf $(OBJDIR) $(BINDIR)
	$(ECHO) "Deep clean complete!"

# Run the program
.PHONY: run
run: $(TARGET)
	$(ECHO) "Running $(PROJECT)..."
	$(Q)$(TARGET)

# Debug build shortcut
.PHONY: debug
debug:
	$(MAKE) BUILD_TYPE=debug

# Release build shortcut
.PHONY: release
release:
	$(MAKE) BUILD_TYPE=release

# Build individual modules
.PHONY: basic vector matrix
basic: $(OBJDIR)/basic_math.o
	$(ECHO) "Basic math module built."

vector: $(OBJDIR)/vector_math.o
	$(ECHO) "Vector math module built."

matrix: $(OBJDIR)/matrix_math.o
	$(ECHO) "Matrix math module built."

# Target-specific flags for optimization level
$(OBJDIR)/basic_math.o: CFLAGS += -O3
$(OBJDIR)/vector_math.o: CFLAGS += -O3
$(OBJDIR)/matrix_math.o: CFLAGS += -O2

# Generate documentation with Doxygen (if installed)
.PHONY: docs
docs:
	$(ECHO) "Generating documentation..."
	$(Q)command -v doxygen >/dev/null 2>&1 && doxygen Doxyfile || echo "Doxygen not installed. Skipping documentation generation."
	$(ECHO) "Documentation generated in doc/html/"

# Install to system
.PHONY: install
install: $(TARGET)
	$(ECHO) "Installing to system..."
	$(Q)install -d $(DESTDIR)/usr/local/bin/
	$(Q)install -m 755 $(TARGET) $(DESTDIR)/usr/local/bin/
	$(ECHO) "Installation complete!"

# Uninstall from system
.PHONY: uninstall
uninstall:
	$(ECHO) "Uninstalling from system..."
	$(Q)rm -f $(DESTDIR)/usr/local/bin/$(PROJECT)
	$(ECHO) "Uninstallation complete!"

# Show help
.PHONY: help
help:
	@echo "$(PROJECT) v$(VERSION) - Available targets:"
	@echo "  all        - Build the application (default)"
	@echo "  clean      - Remove build files"
	@echo "  distclean  - Remove all generated files"
	@echo "  run        - Build and run the application"
	@echo "  debug      - Build with debug symbols"
	@echo "  release    - Build with optimizations"
	@echo "  basic      - Build only the basic math module"
	@echo "  vector     - Build only the vector math module"
	@echo "  matrix     - Build only the matrix math module"
	@echo "  docs       - Generate documentation"
	@echo "  install    - Install to system"
	@echo "  uninstall  - Remove from system"
	@echo ""
	@echo "Build options:"
	@echo "  make BUILD_TYPE=debug    - Build with debug symbols"
	@echo "  make BUILD_TYPE=release  - Build with optimizations"
	@echo "  make V=1                 - Build with verbose output"
	@echo "  make -j<N>               - Build using N parallel jobs"

# Print build information
.PHONY: info
info:
	@echo "$(PROJECT) v$(VERSION) Build Configuration:"
	@echo "  CC:        $(CC)"
	@echo "  CFLAGS:    $(CFLAGS)"
	@echo "  LDFLAGS:   $(LDFLAGS)"
	@echo "  BUILD_TYPE: $(BUILD_TYPE)"
	@echo "  SOURCES:   $(notdir $(SOURCES))"
	@echo "  OBJECTS:   $(notdir $(OBJECTS))"
	@echo "  TARGET:    $(TARGET)"