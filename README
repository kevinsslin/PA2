# Maximum Planar Subset Program

This program finds the maximum planar subset of chords in a circle.

## Compilation Instructions

1. To compile the optimized version:
   ```bash
   make
   ```

2. To compile the debug version with additional debug information:
   ```bash
   make debug
   ```

The executables will be generated in the `bin/` directory:
- Optimized version: `bin/mps`
- Debug version: `bin/mps_dbg`

## Running Instructions

Run the program with input and output files as arguments:
```bash
./bin/mps <input_file> <output_file>
```

For debug version with additional information:
```bash
./bin/mps_dbg <input_file> <output_file>
```

Example:
```bash
./bin/mps inputs/12.in outputs/12.out
```

## Input Format

The input file should contain:
- First line: number of points (must be even)
- Following lines: pairs of numbers representing chord endpoints
- Input ends with 0

Example input (inputs/12.in):
```
12
0 4
1 9
2 6
3 10
5 7
8 11
0
```

## Output Format

The output file will contain:
- First line: maximum number of non-crossing chords possible
- Following lines: pairs of numbers representing the selected chords

Example output (outputs/12.out):
```
3
0 4
5 7
8 11
```

## Cleaning

To clean the compiled files:
```bash
make clean
```

## Debug Mode

The debug version (`mps_dbg`) includes additional output showing:
- Input processing information
- DP table calculation process
- Solution tracing steps

This information is printed to standard output (console) while the actual results are still written to the output file.
