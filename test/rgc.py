import sys
import subprocess


def usage(_pgm,  _onam, _typs):
    print(_pgm + ": a Python program for C* (Pascal) and C* (C++) code generation comparison")
    print("usage: " + _pgm + " [-v vers]")
    print("  v version added to the output file names")
    print("    output in " + _onam + "-" + _typs[0] + "-version.txt and " +
          _onam + "-" + _typs[1] + "-version.txt")
    exit(1)


typs = ("cp", "ps")
vers = ("", "")
onam = 'opcodes'
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
rgcf = "rgc-files.txt"
rgcmf = "rgc-mpi-files.txt"
rdiff = onam + '-diff.txt'
pgm1 = '../cmake-build-debug/cstar'
pgm2 = '~/Pace/courses/spring2024/cs610/parallel/cstar'
exes = (pgm1, pgm2)
lines: [str] = []
rd = open(rgcf, 'r')
rgcf_files = rd.readlines()
rd.close()
for ix, fil in enumerate(rgcf_files):
    cp = subprocess.run('wc -l <' + fil[:-1], shell=True, text=True, capture_output=True)
    if cp.returncode == 0:
        lines.append(int(cp.stdout))
    else:
        print('wc returned ' + str(cp.returncode))
# print(' '.join(map(str, lines)))
cp = subprocess.run("truncate -s 0 " + outcp + " " + outps, shell=True, text=True)
if cp.returncode != 0:
    print('truncate failed with ' + str(cp.returncode))
for ix, fil in enumerate(rgcf_files):
    cmds = '\n'.join(['', 'o ' + fil[:-1], 'code 1:' + str(lines[ix]), 'close', 'exit', 'EOF', ''])
    cmd_str = exes[0] + ' >>' + outcp + ' <<EOF' + cmds
    cp = subprocess.run(cmd_str, shell=True, text=True)
    if cp.returncode != 0:
        print(cmd_str + ' failed with ' + str(cp.returncode))
    cmd_str = exes[1] + ' >>' + outps + ' <<EOF' + cmds
    cp = subprocess.run(cmd_str, shell=True, text=True)
    if cp.returncode != 0:
        print(cmd_str + ' failed with ' + str(cp.returncode))
cmd_str = 'diff ' + outcp + ' ' + outps + ' >' + rdiff
cp = subprocess.run(cmd_str, shell=True, text=True)
