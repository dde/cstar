# Cstar (C*) C++ Conversion by Dan Evans

Table of Contents
=================

* [Introduction](#introduction)
* [Original Source](#original-source)
* [Building](#building)
  * [Build Details](#build-details)
  * [Executables](#executables) 
* [Testing](#testing)

## Introduction

The files contained in this directory are the C++ version of Cstar, an original Pascal program by Dr. Bruce P. Lester,
implementing his language, C*, and the Parallel Computing Simulation System (PCSS) described in his book, ***The Art of
Parallel Programming***, 1stWorld Publishing, Fairfield, Iowa 52556, Library of Congress Control Number: 2006902678,
Hardcover ISBN: 1595408398, Second Printing, 2013.
(C) Copyright 2006, 2013 Bruce P. Lester

Cstar was converted in order to have a source version in an industry-standard language available on many platforms,
to support the language providing fixes and enhancements for the Pace University Seidenberg School of Computer
Science and Information Systems course CS610 Introduction to Parallel Computing.

## Original Distribution

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

The C++ distributions are identical except that there is only one executable named "cstar+" (Mac) or "cstar+.exe" (Windows).  There is no "Shortcut".

## Building

The build meta-file is `CMakeLists.txt`.  This file is used by the program Cmake to
generate build configurations on many platforms and target build systems.  In particular, the IDE Clion from Jet Brains
can build Cstar using `CMakeLists.txt` on both current Macbook Pro computers and Windows 10 systems.

The build system supports both debug and release builds for both platforms.

All source code and auxiliary files are under GIT source code control.

### Build Details

(The following assumes you have installed GIT on your local system to clone and manage the source tree, and Clion to
build debug and run executables from the source)

First, clone the source tree from Github to your development system (if you plan to contribute to the project,
also fork it on Github.)

`git clone https://github.com/dde/cstar`

This will create a directory `cstar` in the current directory on your local system.  Change to the cstar directory
(`cd cstar`), then issue the command:

`git checkout main`

This will bring all the project files into the current directory

Open Clion and select Open project (not New).  Navigate to the cstar directory and click Open (open the directory `cstar`
by clicking the right pointer next to the directory name) All the project file should be displayed.

Double-click the file CMakeLists.txt.  When it opens, it will display "Project is not configured" at the left top and a
text button at the right top "Load Make project". Click the Load and it will start. (progress is displayed at the bottom).
When the Load is complete, the Title bar will display several buttons associated with building and running (hovering
will display brief help.)

* Debug - the current CMake profile
* cstar - the current run/debug configuration
* hammer icon - the Build button
* green right triangle - the Run button
* green bug - the debug button

___Windows (only)___
In the displayed CMakeLists.txt file, edit the 5th line to remove "-DMAC".

<!--Open the file `program.cpp` in a new Edit tab by doubling clicking.  Scroll to the end.  If line 545 is not
commented out, then comment it out (//)-->

**Click the Hammer icon to build. Build actions will display in a lower pane.  "Build finished" will display when complete.

To set the Run/Debug configuration, In the Title bar, click `cstar` (Run/Debug Configurations) to get the menu, then
click `Edit Configurations` to get the current configuration window. In `Working Directory`, click the folder icon to
the right, then navigate to `cstar` directory and click OK.  Then click `Apply` at the lower right, then `Close`.

Click the `Run` button. The Run pane will display at the bottom, and show the C* interactive prompt.  Open the test file
ct1.c in the test directory with the C* open command:

`open test/ct1.c`

The message "test/ct1.c Successfully Compiled" displays.

Run ct1.c with the C* `run` command.  It displays "Hello C*"

Exit with the C* `exit` command.

At this point, the C++ version of C* has executed on your system.
You can now contribute to the project.

### Executables

The Windows executables are

`.\cmake_build_debug\cstar.exe`
`.\cmake_build_release\cstar.exe`**

The Mac executables are

`./cmake-build-debug/cstar`
`./cmake-build-release/cstar`

## Testing

See the subdirectory `test` and the contained `README.md` file for instructions on running and enhancing the regression
tests for the system

