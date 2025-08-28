# Branch Predictor with Assembler

A C-based simulator for branch prediction and assembly code execution. This project provides a simple assembler and CPU simulator to test branch prediction algorithms using custom assembly code.

## Features

- Assembler for a custom instruction set
- CPU simulation with branch prediction
- Example assembly programs (see `example/`)
- Modular codebase for easy extension

## Directory Structure

- `src/` — Source code files
- `include/` — Header files
- `obj/` — Compiled object files
- `example/` — Sample assembly programs
- `main.out` — Compiled executable

## Build Instructions


### Linux

Make sure you have `GCC` or `make` installed. Then run:

```sh
make release 
```

Or manually:

```sh
gcc -std=gnu17 -Iinclude src/*.c -o main.out
```

### Windows (MinGW/MSYS)

Open MSYS2 or MinGW terminal. Make sure GCC is installed (`pacman -S mingw-w64-x86_64-gcc` for MSYS2).

```sh
make release
```

Or manually:

```sh
gcc -std=gnu17 -Iinclude src/*.c -o main.exe
```

### Windows (Command Prompt with GCC)

If you have GCC in your PATH (e.g., via MinGW), run:

```cmd
gcc -std=gnu17 -Iinclude src/*.c -o main.exe
```

Or use the VS Code build task (C/C++: gcc build active file).

## Usage

Run the simulator with an example assembly file:

```sh
./main.out example/fibb.s
```

## Example Programs

- `fibb.s` — Fibonacci sequence
- `ifelse.s` — If-else logic
- `loop.s` — Loop example
- `primes.s` — Prime number calculation

## Contributing

Feel free to open issues or submit pull requests.

## License

See `LICENSE` for details.

