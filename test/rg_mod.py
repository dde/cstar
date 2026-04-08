import sys
from subprocess import Popen, PIPE

PV = 0
NX = 1

def summary(_onam, _typs, _vers, _exes):
    _msg = "    prior output in " if _exes[PV] is None else "    prior execution to "
    print(f"{_msg}{_onam}-{_typs[PV]}-{_vers[PV]}.txt")
    print(f"    next execution to {_onam}-{_typs[NX]}-{_vers[NX]}.txt")

def usage(_ttl,  _onam, _typs, _vers, _exes):
    print(_ttl)
    print(f"usage: {sys.argv[0]} [-p vers] [-n vers] [-v vers] [-g] [-d] [-h]")
    print("  h display this help information")
    print("  d dry run - show operation but do not execute")
    print("  g generate prior version output")
    print("  n next version (v.nn) added to the output file names (default next)")
    print("  p prior version (v.nn) added to the output file names (default 0)")
    print("  v test version (v.nn) (use instead of n and p if prior version is v.nn -1)")
    print("  x execute only, no previous version compare")
    summary(_onam, _typs, _vers, _exes)
    exit(1)

def prior_release(rel):
    fmt = "{:.2f}"
    nrm = 100.0 * float(fmt.format(float(rel)))
    return fmt.format((nrm - 1) / 100.0)


def run_pgm(_pgm: str, _cmds: list[str], _sout: str):
    _sofd = open(_sout, "a", encoding="utf8")
    _cmd_str = "\n".join(_cmds)
    _po = Popen(_pgm, text=True, stdin=PIPE, stdout=_sofd)
    if _po.returncode is not None:
        raise Exception("Popen " + _pgm + " failed with " + str(_po.returncode))
    _po.communicate(input=_cmd_str)
    if _po.returncode != 0:
        raise Exception("communicate failed with " + str(_po.returncode))
    _po.wait()
    if _po.returncode != 0:
        raise Exception("wait failed with " + str(_po.returncode))
    _sofd.close()


def get_args():
    # get command line options
    _rtn = {"-h": False, "-d": False, "-g": False, "-x": False,
            "-p": None, "-n": None, "-v": None, "-f": None}
    _ix = 1
    while _ix < len(sys.argv):
        if sys.argv[_ix].startswith("-"):
            if sys.argv[_ix].startswith("-h"):
                _rtn["-h"] = True
            elif sys.argv[_ix].startswith("-d"):
                _rtn["-d"] = True
            elif sys.argv[_ix].startswith("-g"):
                _rtn["-g"] = True
            elif sys.argv[_ix].startswith("-x"):
                _rtn["-x"] = True
            elif sys.argv[_ix].startswith("-n"):
                _ix += 1
                _rtn["-n"] = str(sys.argv[_ix])
            elif sys.argv[_ix].startswith("-p"):
                _ix += 1
                _rtn["-p"] = sys.argv[_ix]
            elif sys.argv[_ix].startswith("-v"):
                _ix += 1
                _rtn["-p"] = [prior_release(sys.argv[_ix]), sys.argv[_ix]]
            elif sys.argv[_ix].startswith("-f"):
                _ix += 1
                _rtn["-f"] = sys.argv[_ix]
            else:
                _rtn["-h"] = True
        _ix += 1
    return _rtn
