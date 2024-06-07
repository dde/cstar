## Introduction

The files contained in this directory are used for testing the C++ version of Cstar

## Regression Testing

The initial conversion of Pascal C* was done on a Macbook Pro using the Clion IDE.  The Pascal C* for Mac is version is
2.1, and all testing of the conversion targeted this version, even though there is a later version.  This is to keep the
output files identical to allow automated diff verification.

## Scripts

There are three primary regression scripts.

- `rgr.sh` - an execution regression script; a number of different .c files are compiled and executed using both
the C++ version and the Pascal version.  The output is written to two files, `xout-cp.txt`and `xout-ps.txt`
These are `diff` compared.  For each file compiled and executed, the diff output looks like:

```
    < ct21.c Successfully Compiled
    ---
    > Program Successfully Compiled
```
The output containing the program name is from the C++ version and the other line is from the Pascal version.  There
should be no other differences.

- `rgc.sh` - an opcode comparison regression script; using the undocumented CODE interactive command, the interpreter
opcodes are listed for a compiled program, then compared using `diff`.  The output is essentially the same as for 
`rgr.sh` script, one line of difference for each test program.  There is one exception, owing to a bug in the
Pascal version which generates an opcode 38 with uninitialized operands.  The operands are unused, so this is not a
fatal problem.  The output is written to the file `opcodes-cp.txt` and `opcodes-ps.txt`.

- `rgi.sh` - an interactive command script; interactive commands are run using scripted input file names contained
in `rgi-files.txt`, and the output is
captured in the files `cmdout-cp.txt` and `cmdout-ps.txt`. `diff` is run against the output.  The output is
essentially the same as for the other two scripts.  The command scripts are files named `rgi-cmdn.txt`, where `n`
is a number.

The scripts are all controlled by files.  `rgr.sh` reads the file `rgr-files.txt` which contains the names of
all the `.c` files used in the regression testing.  There are actually three slightly different control files.  In
addition to `rgr-files.txt`, there is `rgr-dat-files.txt` containing `.c` file names that read external
data files.  The data file names are derived from the program names, such as `pgm.c-input.txt`.  The third
c ontrol file is `rgr-mpi-files.txt` which contains `.c` program file names needing the MPI execution mode.
