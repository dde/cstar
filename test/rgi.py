import sys
import subprocess


def usage(_pgm,  _onam, _typs):
    print(_pgm + ": a Python program for C* (Pascal) and C* (C++) interactive command comparison")
    print("usage: " + _pgm + " [-v vers] [-c n]")
    print("  c select command script n to run")
    print("  v version added to the output file names")
    print("    output in " + _onam + "-" + _typs[0] + "-version.txt and " +
          _onam + "-" + _typs[1] + "-version.txt")
    exit(1)


typs = ("cp", "ps")
vers = ("", "")
onam = 'cmdout'
outcp = onam + '-' + typs[0] + vers[0] + '.txt'
outps = onam + '-' + typs[1] + vers[1] + '.txt'
filelist = []
# get command line options
cf: int = -1
idx = 1
while idx < len(sys.argv):
    if sys.argv[idx].startswith('-'):
        if sys.argv[idx].startswith('-h'):
            usage(sys.argv[0], onam, typs)
        elif sys.argv[idx].startswith('-v'):
            idx += 1
            vers = (sys.argv[idx], sys.argv[idx])
        elif sys.argv[idx].startswith('-c'):
            idx += 1
            cf = int(sys.argv[idx])
        else:
            usage(sys.argv[0], onam, typs)
    else:
        filelist.append(sys.argv[idx])
    idx += 1
rgif = "rgi-files.txt"
rgimf = "rgi-mpi-files.txt"
rdiff = onam + '-diff.txt'
pgm1 = '../cmake-build-debug/cstar'
pgm2 = '~/Pace/courses/spring2024/cs610/parallel/cstar'
exes = (pgm1, pgm2)
lines: [str] = []
rd = open(rgif, 'r')
rgif_files = rd.readlines()
rd.close()
cp = subprocess.run("truncate -s 0 " + outcp + " " + outps, shell=True, text=True)
if cp.returncode != 0:
    print('truncate failed with ' + str(cp.returncode))
if cf > -1:
    cmdf = ["rgi-cmd" + str(cf) + ".txt\n"]
else:
    cmdf = rgif_files
for ix, fil in enumerate(cmdf):
    cmd_str = exes[0] + ' >>' + outcp + ' <' + fil[:-1]
    cp = subprocess.run(cmd_str, shell=True, text=True)
    if cp.returncode != 0:
        print(cmd_str + ' failed with ' + str(cp.returncode))
    cmd_str = exes[1] + ' >>' + outps + ' <' + fil[:-1]
    cp = subprocess.run(cmd_str, shell=True, text=True)
    if cp.returncode != 0:
        print(cmd_str + ' failed with ' + str(cp.returncode))
cmd_str = 'diff ' + outcp + ' ' + outps + ' >' + rdiff
cp = subprocess.run(cmd_str, shell=True, text=True)
