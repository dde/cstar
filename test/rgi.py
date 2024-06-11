import sys
import os
from subprocess import Popen, PIPE, run


def usage(_pgm,  _onam, _typs):
    print(_pgm + ": a Python program for C* (Pascal) and C* (C++) interactive command comparison")
    print("usage: " + _pgm + " [-v vers] [-c n]")
    print("  c select command script n to run")
    print("  v version added to the output file names")
    print("    output in " + _onam + "-" + _typs[0] + "-version.txt and " +
          _onam + "-" + _typs[1] + "-version.txt")
    exit(1)


def run_pgm(_pgm: str, _cmds: [str], _sout: str):
    _sofd = open(_sout, "a", encoding='utf8')
    _cmd_str = '\n'.join(_cmds)
    _po = Popen(_pgm, text=True, stdin=PIPE, stdout=_sofd)
    if _po.returncode is not None:
        raise Exception('Popen ' + _pgm + ' failed with ' + str(_po.returncode))
    _po.communicate(input=_cmd_str)
    if _po.returncode != 0:
        raise Exception('communicate failed with ' + str(_po.returncode))
    _po.wait()
    if _po.returncode != 0:
        raise Exception('wait failed with ' + str(_po.returncode))
    _sofd.close()


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
which = 'release'
if os.name == 'nt':
    pgm1 = '/Users/Dan/ClionProjects/cstar/cmake-build-' + which + '/cstar.exe'
    pgm2 = '/Users/Dan/Dropbox/parallel/cstar.exe'
elif os.name == 'posix':
    pgm1 = '/Users/danevans/ClionProjects/cstar/cmake-build-' + which + '/cstar'
    pgm2 = '/Users/danevans/Library/CloudStorage/Dropbox/parallel/cstar'
else:
    print('unknown OS')
    exit(1)
exes = (pgm1, pgm2)
wd = open(outcp, 'w')
wd.close()
wd = open(outps, 'w')
wd.close()
lines: [str] = []
rd = open(rgif, 'r')
rgif_files = rd.readlines()
rd.close()
if cf > -1:
    cmdf = ["rgi-cmd" + str(cf) + ".txt\n"]
else:
    cmdf = rgif_files
for ix, fil in enumerate(cmdf):
    try:
        rd = open(fil[:-1], 'r')
        cmd_str = rd.readlines()
        rd.close()
        run_pgm(exes[0], cmd_str, outcp)
        run_pgm(exes[1], cmd_str, outps)
    except Exception as ex:
        print(str(ex))
if os.name == 'nt':
    cmd_str = 'fc /L /N ' + outcp + ' ' + outps + ' >' + rdiff
    cp = run(cmd_str, shell=True, text=True)
else:
    cmd_str = 'diff ' + outcp + ' ' + outps + ' >' + rdiff
    cp = run(cmd_str, shell=True, text=True)
print('interactive regression complete')
