import sys
import os
from subprocess import Popen, PIPE, run


def usage(_pgm,  _onam, _typs):
    # print(_pgm + ": a Python program for C* (Pascal) and C* (C++) code generation comparison")
    print(_pgm + ": a Python program for C* (C++) release code generation comparison")
    print("usage: " + _pgm + " [-v vers]")
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


typs = ("cp", "pv")
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
which = 'release'
if os.name == 'nt':
    pgm1 = '/Users/Dan/ClionProjects/cstar/cmake-build-' + which + '/cstar.exe'
    pgm2 = '/Users/Dan/Dropbox/parallel/cstar.exe'
elif os.name == 'posix':
    pgm1 = '/Users/danevans/ClionProjects/cstar/cmake-build-' + which + '/cstar'
    pgm2 = '/Users/danevans/ClionProjects/cstar/parallel/cstar+'
    # pgm2 = '/Users/danevans/Library/CloudStorage/Dropbox/parallel/cstar'
else:
    print('unknown OS')
    exit(1)
exes = (pgm1, pgm2)
lines: [int] = []
rd = open(rgcf, 'r')
rgcf_files = rd.readlines()
rd.close()
for ix, fil in enumerate(rgcf_files):
    try:
        rd = open(fil[:-1], 'r', encoding='utf8')
        pgm_file = rd.readlines()
        lines.append(len(pgm_file))
        rd.close()
    except OSError as ex:
        print(str(ex))
        continue
# print(' '.join(map(str, lines)))
wd = open(outcp, 'w')
wd.close()
wd = open(outps, 'w')
wd.close()
for ix, fil in enumerate(rgcf_files):
    cmd_str = ['o ' + fil[:-1], 'code 1:' + str(lines[ix]), 'close', 'exit', 'EOF', '']
    try:
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
print('opcode regression complete')
