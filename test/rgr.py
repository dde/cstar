import os
from subprocess import run
from rg_mod import PV, NX, run_pgm, get_args, summary, usage

title = "a Python program for C* (C++) regression comparison"
typs = ("cp", "cp")
vers = ["0", "next"]
onam = "regress"
prj = "/ClionProjects/cstar"
which = "/cmake-build-release"
rgrf = "rgr-files.txt"
rgrdf = "rgr-dat-files.txt"
rgrmf = "rgr-mpi-files.txt"
rdiff = onam + "-diff.txt"
if os.name == "nt":
    usr = "/Users/Dan"
    nxpgm = f"{usr}{prj}{which}/cstar.exe"
    pvpgm = f"{usr}/Dropbox/parallel/cstar.exe"
elif os.name == "posix":
    usr = "/Users/danevans"
    nxpgm = f"{usr}{prj}{which}/cstar"
    pvpgm = f"{usr}{prj}/parallel-m1/cstar"
    # pvpgm = "/Users/danevans/Library/CloudStorage/Dropbox/parallel/cstar"
else:
    print("unknown OS")
    exit(1)
exes = [None, nxpgm]
opt = get_args()
if opt["-f"] is None:
    rgcf = "rgr-files.txt"
else:
    rgcf = opt["-f"]
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
# outnx = onam + "-" + typs[PV] + vers[PV] + ".txt"
# outpv = onam + "-" + typs[NX] + vers[NX] + ".txt"
if opt["-d"]:
    try:
        stat_st = os.stat(outnx)
        print(f"    file {outnx} will be over written")
    except FileNotFoundError:
        pass
    if not opt["-x"]:
        try:
            stat_st = os.stat(outpv)
            if exes[PV] is not None:
                print(f"    file {outpv} will be over written by {exes[PV]}")
        except FileNotFoundError:
            if exes[PV] is None:
                print(f"    file {outpv} does not exist")
            else:
                print(f"    file {outpv} will be generated from {exes[PV]}")
    print(f"    list of test files is in {rgcf}")
    if opt["-x"]:
        print("    no comparision will be run")
    exit(0)
print("regression phase 1")
wd = open(outnx, "w")
wd.close()
if not opt["-x"]:
    wd = open(outpv, "r" if exes[PV] is None else "w")
    wd.close()
rd = open(rgrf, "r")
rgrf_files = rd.readlines()
rd.close()
for fil in rgrf_files:
    if fil[0] == "#":
        continue
    cmds = [f"o {fil[:-1]}", "run", "close", "exit", "EOF", ""]
    try:
        run_pgm(exes[NX], cmds, outnx)
        if exes[PV] is not None:
            run_pgm(exes[PV], cmds, outpv)
    except Exception as ex:
        print(str(ex))
print("regression phase 2")
rd = open(rgrdf, "r")
rgrf_files = rd.readlines()
rd.close()
for fil in rgrf_files:
    cmds = [f"o {fil[:-1]}", f"input {fil[:-1]}-input.txt", "run",
            "close", "input", "exit", "EOF", ""]
    try:
        run_pgm(exes[NX], cmds, outnx)
        if exes[PV] is not None:
            run_pgm(exes[PV], cmds, outpv)
    except Exception as ex:
        print(str(ex))
print("regression phase 3")
rd = open(rgrmf, "r")
rgrf_files = rd.readlines()
rd.close()
for fil in rgrf_files:
    cmds = ["mpi on", f"o {fil[:-1]}", "run",
            "close", "input", "exit", "EOF", ""]
    try:
        run_pgm(exes[NX], cmds, outnx)
        if exes[PV] is not None:
            run_pgm(exes[PV], cmds, outpv)
    except Exception as ex:
        print(str(ex))
if not opt["-x"]:
    if os.name == "nt":
        cmd_str = f"fc /L /N {outnx} {outpv} >{rdiff}"
    else:
        cmd_str = f"diff {outnx} {outpv} >{rdiff}"
    cp = run(cmd_str, shell=True, text=True)
    stat_st = os.stat(rdiff)
    if stat_st.st_size == 0:
        print("no differences")
    else:
        print("there are differences")
print("regression complete")
