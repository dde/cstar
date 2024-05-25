## Cstar (C*) C++ Conversion by Daniel Evans, PhD

The files contained in this directory are the C++ version of Cstar, an original program by Dr. Bruce P. Lester,
implementing his language, C*, and the Parallel Computing Simulation System (PCSS) described in his book, ***The Art of
Parallel Programming***, 1stWorld Publishing, Fairfield, Iowa 52556, Library of Congress Control Number: 2006902678,
Hardcover ISBN: 1595408398, Second Printing, 2013.

Cstar was converted in order to have a source version in an industry-standard language available on many platforms,
to support the language providing fixes and enhancements for the Pace University Seidenberg School of Computer
Science and Information Systems course CS610 Introduction to Parallel Computing.

## Original Source

The original Pascal source code for PCCS is contained in the two files `Cstar-2.1-orig.txt` and `Cstar-2.2-orig.txt`.
Version 2.1 corresponds to the Mac executable, and version 2.2 corresponds to the Windows executable in the original
distribution zip file.

The original Cstar distribution, `parallel.zip`, contains the files:

        parallel/
        parallel/cstar
        parallel/cstar.exe
        parallel/ctype.h
        parallel/License.pdf
        parallel/LISTFILE.TXT
        parallel/math.h
        parallel/MatrixMultiplyParallel.c
        parallel/MatrixMultiplySequential.c
        parallel/MPI-Hello.c
        parallel/mpi.h
        parallel/RandomFloats.c
        parallel/RandomFloats.txt
        parallel/RandomIntegers.c
        parallel/RandomIntegers.txt
        parallel/RankSortParallel.c
        parallel/RankSortSequential.c
        parallel/Shortcut to Cstar.lnk
        parallel/SquareRootParallel.c
        parallel/SquareRootSequential.c
        parallel/stdlib.h
        parallel/string.h
        parallel/SumFloatInput.c
        parallel/SumFloatRandom.c

## Building

The build instructions are in the file `CMakeLists.txt`.  This is a build meta-file used by the program Cmake to
generate build configurations on many platforms and target build systems.  In particular, the IDE Clion from Jet Brains
can build Cstar using CMakeLists.txt on both current Macbook Pro computers and Windows 10 systems.

The build system supports both debug and release builds for both platforms.

All source code and auxiliary files are under GIT source code control.

## Testing

See the subdirectory `test` and the contained `README.md` file for instructions on running and enhancing the regression
tests for the system

