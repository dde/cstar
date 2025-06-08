import sys
import os
from subprocess import Popen, PIPE, run


def usage(_pgm,  _onam, _typs):
    print(_pgm + ": a Python program for C* (C++) version regression testing")
    print("usage: " + _pgm + " [-h] [-v vers]")
    print("  h display this help information")
    print("  v version added to the output file names")
    print("    output in " + _onam + "-" + _typs[0] + "-version.txt and " +
          _onam + "-" + _typs[1] + "-version.txt")
    exit(1)


def args():
    global vers, filelist
    # get command line options
    idx = 1
    while idx < len(sys.argv):
        if sys.argv[idx].startswith('-'):
            if sys.argv[idx].startswith('-h'):
                usage(sys.argv[0], onam, typs)
            elif sys.argv[idx].startswith('-v'):
                idx += 1
                vers = sys.argv[idx]
            else:
                usage(sys.argv[0], onam, typs)
        else:
            filelist.append(sys.argv[idx])
        idx += 1

def latest(onm: str, typ: str, v: int) -> int:
    frst = True
    while True:
        ovnm = onm + '-' + typ + '-v' + str(v) + '.txt'
        try:
            stat_st = os.stat(ovnm)
            frst = False
        except FileNotFoundError:
            if frst:
                raise FileNotFoundError("version " + str(v) + " missing")
            return v
        v += 1

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

vers = 0
filelist = []
onam = 'regress'
typs = ("nx", "cp")
args()
vl: int = latest(onam, typs[1], vers)
print('next version is', vl)
# sys.exit(1)
vers = (str(vl),) * 2
outnx = onam + '-' + typs[0] + vers[0] + '.txt'
outcp = onam + '-' + typs[1] + vers[1] + '.txt'

rgrf = "rgr-files.txt"
rgrdf = "rgr-dat-files.txt"
rgrmf = "rgr-mpi-files.txt"
rdiff = onam + '-diff.txt'
which = 'release'
if os.name == 'nt':
    nxpgm = '/Users/Dan/ClionProjects/cstar/cmake-build-' + which + '/cstar.exe'
    cppgm = '/Users/Dan/Dropbox/parallel/cstar.exe'
elif os.name == 'posix':
    nxpgm = '/Users/danevans/ClionProjects/cstar/cmake-build-' + which + '/cstar'
    cppgm = '/Users/danevans/ClionProjects/cstar/parallel-m1/cstar'
    # cppgm = '/Users/danevans/Library/CloudStorage/Dropbox/parallel/cstar'
else:
    print('unknown OS')
    exit(1)
exes = (nxpgm, cppgm)
print("regression phase 1")
wd = open(outnx, 'w')
wd.close()
wd = open(outcp, 'w')
wd.close()
rd = open(rgrf, 'r')
rgrf_files = rd.readlines()
rd.close()
for fil in rgrf_files:
    cmds = ['o ' + fil[:-1], 'run', 'close', 'exit', 'EOF', '']
    try:
        run_pgm(exes[0], cmds, outnx)
        run_pgm(exes[1], cmds, outcp)
    except Exception as ex:
        print(str(ex))
print("regression phase 2")
rd = open(rgrdf, 'r')
rgrf_files = rd.readlines()
rd.close()
for fil in rgrf_files:
    cmds = ['o ' + fil[:-1], 'input ' + fil[:-1] + '-input.txt', 'run',
            'close', 'input', 'exit', 'EOF', '']
    try:
        run_pgm(exes[0], cmds, outnx)
        run_pgm(exes[1], cmds, outcp)
    except Exception as ex:
        print(str(ex))
print("regression phase 3")
rd = open(rgrmf, 'r')
rgrf_files = rd.readlines()
rd.close()
for fil in rgrf_files:
    cmds = ['mpi on', 'o ' + fil[:-1], 'run',
            'close', 'input', 'exit', 'EOF', '']
    try:
        run_pgm(exes[0], cmds, outnx)
        run_pgm(exes[1], cmds, outcp)
    except Exception as ex:
        print(str(ex))
if os.name == 'nt':
    cmd_str = 'fc /L /N ' + outnx + ' ' + outcp + ' >' + rdiff
    cp = run(cmd_str, shell=True, text=True)
elif os.name == 'posix':
    cmd_str = 'diff ' + outnx + ' ' + outcp + ' >' + rdiff
    cp = run(cmd_str, shell=True, text=True)
print("regression complete")
