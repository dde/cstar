#!/bin/bash
pgms=("cp" "ps")
vers=("" "")
onam=cmdout
cf=-1
while getopts ":hc:v:" opt
do
  case $opt in
  h)
    echo "$0: a shell script for C* Pascal and C++ interactive command comparison"
    echo "usage: $0 [-v vers] [-c n]"
    echo "  c select command script n to run"
    echo "  v version added to the output file names"
    echo "    output in $onam-${pgms[0]}-version.txt and $onam-${pgms[1]}-version.txt"
    exit 1
    ;;
  c)
    cf=$OPTARG
    ;;
  v)
    vers=("-$OPTARG" "-$OPTARG")
    ;;
  ?*)
    echo "unknown option $opt"
    exit 1
  esac
done
rgif="rgi-files.txt"
pgm1=../cmake-build-debug/cstar
pgm2=~/Pace/courses/spring2024/cs610/parallel/cstar
exes=($pgm1 $pgm2)
outcp=$onam-${pgms[0]}${vers[0]}.txt
outps=$onam-${pgms[1]}${vers[1]}.txt
truncate -s 0 $outcp $outps
if [ $cf -gt -1 ]; then
  cmdf="rgi-cmd$cf.txt"
else
  cmdf=`cat $rgif`
fi
for fil in $cmdf
do
  ${exes[0]} <$fil >>$outcp
  ${exes[1]} <$fil >>$outps
done
echo "output files $outcp and $outps"
diff $outcp $outps
