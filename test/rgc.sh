#!/bin/bash
declare -a -i lines
args=($0 $*)
pgms=("cp" "ps")
vers=("" "")
onam=opcodes
while getopts ":hv:" opt
do
  case $opt in
  h)
    echo "$0: a shell script for C* Pascal and C++ code generation comparison"
    echo "usage: $0 [-v vers]"
    echo "  v version added to the output file names"
    echo "    output in $onam-${pgms[0]}-version.txt and $onam-${pgms[1]}-version.txt"
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
rgcf="rgc-files.txt"
rgcmf="rgc-mpi-files.txt"
pgm1=../cmake-build-debug/cstar
pgm2=~/Pace/courses/spring2024/cs610/parallel/cstar
exes=($pgm1 $pgm2)
ix=0
for fil in `cat $rgcf`
do
  lines[$ix]=`wc -l <$fil`
  ix=$(($ix + 1))
done
outcp=$onam-${pgms[0]}${vers[0]}.txt
outps=$onam-${pgms[1]}${vers[1]}.txt
truncate -s 0 $outcp $outps
ix=0
for fil in `cat $rgcf`
do
  ${exes[0]} <<EOC >>$outcp
o $fil
code 1:${lines[$ix]}
close
exit
EOC
  ${exes[1]} <<EOP >>$outps
o $fil
code 1:${lines[$ix]}
close
exit
EOP
  ix=$(($ix + 1))
done
ix=0
for fil in `cat $rgcmf`
do
  ${exes[0]} <<EOC >>$outcp
mpi on
o $fil
code 1:${lines[$ix]}
close
exit
EOC
  ${exes[1]} <<EOP >>$outps
mpi on
o $fil
code 1:${lines[$ix]}
close
exit
EOP
  ix=$(($ix + 1))
done
echo "output files $outcp and $outps"
diff $outcp $outps
