import sys
import subprocess


def usage(_pgm,  _onam, _typs):
    print(_pgm + ": a Python program for C* (Pascal) and C* (C++) version regression testing")
    print("usage: " + _pgm + " [-v vers]")
    print("  v version added to the output file names")
    print("    output in " + _onam + "-" + _typs[0] + "-version.txt and " +
          _onam + "-" + _typs[1] + "-version.txt")
    exit(1)


typs = ("cp", "ps")
vers = ("", "")
onam = 'regress'
outcp = onam + '-' + typs[0] + vers[0] + '.txt'
outps = onam + '-' + typs[1] + vers[1] + '.txt'
filelist = []
# get command line options
idx = 1
while idx < len(sys.argv):
    if sys.argv[idx].startswith('-'):
        if sys.argv[idx].startswith('-h'):
            usage(sys.argv[0], onam, typs)
        elif sys.argv[idx].startswith('-v'):
            idx += 1
            vers = (sys.argv[idx], sys.argv[idx])
        else:
            usage(sys.argv[0], onam, typs)
    else:
        filelist.append(sys.argv[idx])
    idx += 1

rgrf = "rgr-files.txt"
rgrdf = "rgr-dat-files.txt"
rgrmf = "rgr-mpi-files.txt"
rdiff = onam + '-diff.txt'
pgm1 = '../cmake-build-debug/cstar'
pgm2 = '~/Pace/courses/spring2024/cs610/parallel/cstar'
exes = (pgm1, pgm2)
print("regression phase 1")
cmd_str = 'truncate -s 0 ' + outcp + ' ' + outps
cp = subprocess.run(cmd_str, shell=True, text=True)
if cp.returncode != 0:
    print(cmd_str + ' failed with ' + str(cp.returncode))
rd = open(rgrf, 'r')
rgrf_files = rd.readlines()
rd.close()
for fil in rgrf_files:
    cmds = '\n'.join(['', 'o ' + fil[:-1], 'run', 'close', 'exit', 'EOF', ''])
    cmd_str = exes[0] + ' >>' + outcp + ' <<EOF' + cmds
    cp = subprocess.run(cmd_str, shell=True, text=True)
    if cp.returncode != 0:
        print(cmd_str + ' failed with ' + str(cp.returncode))
    cmd_str = exes[1] + ' >>' + outps + ' <<EOF' + cmds
    cp = subprocess.run(cmd_str, shell=True, text=True)
    if cp.returncode != 0:
        print(cmd_str + ' failed with ' + str(cp.returncode))
print("regression phase 2")
rd = open(rgrdf, 'r')
rgrf_files = rd.readlines()
rd.close()
for fil in rgrf_files:
    cmds = '\n'.join(['', 'o ' + fil[:-1], 'input ' + fil[:-1] + '-input.txt', 'run',
                      'close', 'input', 'exit', 'EOF', ''])
    cmd_str = exes[0] + ' >>' + outcp + ' <<EOF' + cmds
    cp = subprocess.run(cmd_str, shell=True, text=True)
    if cp.returncode != 0:
        print(cmd_str + ' failed with ' + str(cp.returncode))
    cmd_str = exes[1] + ' >>' + outps + ' <<EOF' + cmds
    cp = subprocess.run(cmd_str, shell=True, text=True)
    if cp.returncode != 0:
        print(cmd_str + ' failed with ' + str(cp.returncode))
# for fil in `cat $rgrdf`
# do
#  ${exes[0]} <<EOC >>$outcp
# o $fil
# input $fil-input.txt
# run
# close
# input
# exit
# EOC
#  ${exes[1]} <<EOP >>$outps
# o $fil
# input $fil-input.txt
# run
# close
# input
# exit
# EOP
# done
# echo "regression phase 3"
print("regression phase 3")
rd = open(rgrmf, 'r')
rgrf_files = rd.readlines()
rd.close()
for fil in rgrf_files:
    cmds = '\n'.join(['', 'mpi on', 'o ' + fil[:-1], 'run',
                      'close', 'input', 'exit', 'EOF', ''])
    cmd_str = exes[0] + ' >>' + outcp + ' <<EOF' + cmds
    cp = subprocess.run(cmd_str, shell=True, text=True)
    if cp.returncode != 0:
        print(cmd_str + ' failed with ' + str(cp.returncode))
    cmd_str = exes[1] + ' >>' + outps + ' <<EOF' + cmds
    cp = subprocess.run(cmd_str, shell=True, text=True)
    if cp.returncode != 0:
        print(cmd_str + ' failed with ' + str(cp.returncode))
print("regression complete")
cmd_str = 'diff ' + outcp + ' ' + outps + ' >' + rdiff
cp = subprocess.run(cmd_str, shell=True, text=True)
