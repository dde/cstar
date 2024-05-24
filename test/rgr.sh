#!/bin/bash
declare -a typs vers exes
typs=("cp" "ps")
vers=("" "")
onam=regress
outcp=$onam-${typs[0]}${vers[0]}.txt
outps=$onam-${typs[1]}${vers[1]}.txt
while getopts ":hv:" opt
do
  case $opt in
  h)
    echo "$0: a shell script for C* Pascal and C++ regression testing"
    echo "usage: $0 [-v vers]"
    echo "  v version added to the output file names"
    echo "    output in $onam-${typs[0]}-version.txt and $onam-${typs[1]}-version.txt"
    exit 1
    ;;
  v)
    vers=("-$OPTARG" "-$OPTARG")
    ;;
  ?*)
    echo "unknown option $opt"
    exit 1
  esac
done
rgrf="rgr-files.txt"
rgrdf="rgr-dat-files.txt"
rgrmf="rgr-mpi-files.txt"
pgm1=../cmake-build-debug/cstar
pgm2=~/Pace/courses/spring2024/cs610/parallel/cstar
exes=($pgm1 $pgm2)
echo "regression phase 1"
truncate -s 0 $outcp $outps
for fil in `cat $rgrf`
do
  ${exes[0]} <<EOC >>$outcp
o $fil
run
close
exit
EOC
  ${exes[1]} <<EOP >>$outps
o $fil
run
close
exit
EOP
done
echo "regression phase 2"
for fil in `cat $rgrdf`
do
  ${exes[0]} <<EOC >>$outcp
o $fil
input $fil-input.txt
run
close
input
exit
EOC
  ${exes[1]} <<EOP >>$outps
o $fil
input $fil-input.txt
run
close
input
exit
EOP
done
echo "regression phase 3"
for fil in `cat $rgrmf`
do
  ${exes[0]} <<EOC >>$outcp
mpi on
o $fil
run
close
exit
EOC
  ${exes[1]} <<EOP >>$outps
mpi on
o $fil
run
close
exit
EOP
done
echo "regression complete"
diff $outcp $outps
