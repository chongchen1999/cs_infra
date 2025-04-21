## The process to generate .out
.c -> .i: preprocessing
.i -> .s: compilation
.s -> .o: assembly
.o -> .out: linking

## CLI
- gcc -E hello.c -o hello.i
- gcc -S hello.i -o hello.s
- as hello.s -o hello.o
- ld hello.o -o hello.out

## Makefile
```makefile
all: hello.out
hello.out: hello.o
    ld hello.o -o hello.out
hello.o: hello.s
    as hello.s -o hello.o
hello.s: hello.i
    gcc -S hello.i -o hello.s
hello.i: hello.c
    gcc -E hello.c -o hello.i
clean:
    rm *.i *.s *.o *.out
```

## Makefile (simplified)
```makefile
CC=gcc
AS=as
LD=ld
CFLAGS=-E
SFLAGS=-S
AFLAGS=
LFLAGS=

all: hello.out
%.out: %.o
    $(LD) $< -o $@
%.o: %.s
    $(AS) $< -o $@
%.s: %.i
    $(CC) $(SFLAGS) $< -o $@
```

