# branch-predictor-with-assembler

This project implements a simple CPU simulation with instruction execution and branch prediction using a 4-bit saturating counter predictor.

## Features

- Basic Assembler.
- Basic CPU instruction fetch, decode, and execute cycle.
- Branch prediction using a saturating 4-bit counter per instruction.
- Instruction set includes arithmetic, memory, and stack operations.

## Requirements

- GCC compiler supporting GNU extensions (recommended `gcc` with `-std=gnu17`).
- `make`

## Build Instructions

1. Clone or download the project source code.
2. Navigate to the project root directory.
3. Run `make` to build the project executable.

The provided Makefile compiles the source files in the `src/` directory and outputs an executable named `main.out` (on Linux/macOS) or `main.exe` (on Windows).

## Running the Project

After building:

```sh
./main.out
```

or on Windows:

```cmd
main.exe
```

Currently, the program executes a predefined or loaded set of assembly-style instructions in simulation, using its branch predictor to optimize instruction execution paths.

## Files

- `src/cpu.c` and `src/cpu.h`: CPU implementation including interpreter and instruction execution.
- `src/predictor.c` and `src/predictor.h`: Branch predictor implementation.
- `include/stb_ds.h`: Third-party header-only hashmap library used internally.

## Notes

- The predictor expects a threshold value between 1 and 14 for its counters.
- Ensure the compiler supports GNU extensions (e.g., `typeof`) for `stb_ds` macros.
- The Makefile uses `-std=gnu17` for compatibility.

---

This project is a foundation for experimenting with CPU simulation and branch prediction concepts. Contributions and improvements are welcome.
