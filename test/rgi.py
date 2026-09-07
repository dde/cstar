import os
from subprocess import run
from rg_mod import PV, NX, run_pgm, get_args, summary, usage

title= "a Python program for C* (C++) version interactive command comparison"
typs = ["cp", "cp"]
vers = ["0", "next"]
onam = 'cmdout'
# prj = "/ClionProjects/cstar"
# which = "/cmake-build-release"
rgif = "rgi-files.txt"
rgimf = "rgi-mpi-files.txt"
rdiff = f"{onam}-diff.txt"

usr = os.path.expanduser("~")

script_dir = os.path.dirname(os.path.abspath(__file__))
repo_root = os.path.dirname(script_dir)

build_dir = "cmake-build-release"
if not os.path.exists(os.path.join(repo_root, build_dir)):
    if os.path.exists(os.path.join(repo_root, "cmake-build-debug")):
        build_dir = "cmake-build-debug"

if os.name == "nt":
    nxpgm = os.path.join(repo_root, build_dir, "cstar.exe")
    pvpgm = f"{usr}/Dropbox/parallel/cstar.exe"
    # usr = "/Users/Dan"
    # nxpgm = f"{usr}{prj}{which}/cstar.exe"
    # pvpgm = f"{usr}/Dropbox/parallel/cstar.exe"
elif os.name == "posix":
    nxpgm = os.path.join(repo_root, build_dir, "cstar")
    pvpgm = f"{usr}/ClionProjects/cstar/parallel-m1/cstar"
    # usr = "/Users/danevans"
    # nxpgm = f"{usr}{prj}{which}/cstar"
    # pvpgm = f"{usr}{prj}/parallel-m1/cstar"
    # pvpgm = "/Users/danevans/Library/CloudStorage/Dropbox/parallel/cstar"
else:
    print("unknown OS")
    exit(1)

exes = [None, nxpgm]
cf: int = -1
opt = get_args()
if opt["-g"]:
    exes[PV] = pvpgm
if opt["-p"] is not None:
    vers[PV] = opt["-p"]
if opt["-n"] is not None:
    vers[NX] = opt["-n"]
if opt["-v"] is not None:
    vers = opt["-v"]
if opt["-h"]:
    usage(title, onam, typs, vers, exes)
summary(onam, typs, vers, exes)

outpv = f"{onam}-{typs[PV]}-{vers[PV]}.txt"
outnx = f"{onam}-{typs[NX]}-{vers[NX]}.txt"

if opt["-d"]:
    try:
        stat_st = os.stat(outnx)
        print(f"    file {outnx} will be over written")
    except FileNotFoundError:
        pass
    if opt["-x"]:
        try:
            stat_st = os.stat(outpv)
            if exes[PV] is not None:
                print(f"    file {outpv} will be over written by {exes[PV]}")
        except FileNotFoundError:
            if exes[PV] is None:
                print(f"    file {outpv} does not exist")
            else:
                print(f"    file {outpv} will be generated from {exes[PV]}")
    print(f"    list of test files is in {rgif}")
    if opt["-x"]:
        print("    no comparison will be run")
    exit(0)

wd = open(outnx, 'w')
wd.close()
wd = open(outpv, "r" if exes[PV] is None else "w")
wd.close()
lines: list[str] = []
rd = open(rgif, 'r')
rgif_files = rd.readlines()
rd.close()

if cf > -1:
    cmdf = [f"rgi-cmd{str(cf)}.txt\n"]
else:
    cmdf = rgif_files
for ix, fil in enumerate(cmdf):
    if fil[0] == "#":
        continue
    try:
        rd = open(fil[:-1], 'r')
        cmd_str = rd.readlines()
        rd.close()
        run_pgm(exes[NX], cmd_str, outnx)
        if exes[PV] is not None:
            run_pgm(exes[PV], cmd_str, outpv)
    except Exception as ex:
        print(str(ex))

if not opt["-x"]:
    if os.name == "nt":
        cmd_str = f"fc /L /N {outnx} {outpv} >{rdiff}"
        cp = run(cmd_str, shell=True, text=True)
        # Windows fc returns 0 for a match, >0 for differences
        if cp.returncode == 0:
            print("no differences")
        else:
            print("there are differences")
    else:
        cmd_str = f"diff {outnx} {outpv} >{rdiff}"
        cp = run(cmd_str, shell=True, text=True)
        # Mac/Linux diff outputs 0 bytes for a match
        stat_st = os.stat(rdiff)
        if stat_st.st_size == 0:
            print("no differences")
        else:
            print("there are differences")

print('interactive regression complete')
