## Introduction

The files contained in this directory are used for testing the C++ version of Cstar.

### Pascal-to-C++ Regression Testing

The initial conversion of Pascal C\* was done on a Macbook Pro using the Clion IDE.  The Pascal C\* for Mac was version 2.1. See README-conversion.md for further information.

## C++ Version Regression Testing

There are three primary regression scripts, writtem in Python.  A Python module, rg\_mod.py, contains code that is common to all scripts.  The command line options for each script are the same, and can be displayed with the -h option, for example:

```
test % python3 rgr.py -h
a Python program for C\* (C++) regression comparison
usage: rgr.py \[-p vers] \[-n vers] \[-v vers] \[-g] \[-d] \[-h]
  h display this help information
  d dry run - show operation but do not execute
  g generate prior version output
  n next version (v.nn) added to the output file names (default next)
  p prior version (v.nn) added to the output file names (default 0)
  v test version (v.nn) (use instead of n and p if prior version is v.nn -1)
  x execute only, no previous version compare
    prior output in regress-cp-0.txt
    next execution to regress-cp-next.txt
```

The general steps for regresssion testing are:

1. create an enhancement to the current version; for example, assume the current version is 2.21
2. Modify the script if necessary to point to the new version
3. run the script pointing to the previous version's test out, and defaulting to "next" for the new version's output, with a command such as:
```
    % python3 rgr.py -p 2.21
        prior output in regress-cp-2.21.txt
        next execution to regress-cp-next.txt
    regression phase 1
    regression phase 2
    regression phase 3
    no differences
    regression complete
```
4. use the -x option with test input for the new version, then add the test files to the input file list for regression, and append the test output to the "next" output, renamethe "next" version to "regress-cp-2.22.txt", and verify that "python3 rgr.py -p 2.22" runs with no differences.

Repeat steps 1 through 4 for each new version.

## Scripts

The regression scripts are
- `rgr.py` - an execution regression script; a number of different .c files are compiled and executed using the current C++ Release version.

- `rgc.py` - an opcode comparison regression script; using the CODE interactive command, the interpreter numeric opcodes are listed aand captured, then compared using `diff`.  The output is essentially the same as for "rgr.py", and is written to `opcodes-cp-next.txt`.

- `rgi.py` - an interactive command script; interactive commands are run using scripted input file names contained in `rgi-files.txt`, and the output is captured in the file `cmdout-cp-next.txt` essentially the same as for the other two scripts.
is a number.


