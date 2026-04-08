import os
from subprocess import run
from rg_mod import PV, NX, run_pgm, get_args, summary, usage

title = "a Python program for C* (C++) opcode generation comparison"
typs = ["cp", "cp"]
vers = ["0", "next"]
onam = "opcodes"
prj = "/ClionProjects/cstar"
which = "/cmake-build-release"
rgcmf = "rgc-mpi-files.txt"
rdiff = f"{onam}-diff.txt"
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
if opt["-f"] is not None:
    rgcf = opt["-f"]
else:
    rgcf = "rgc-files.txt"
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
lines: list[int] = []
rd = open(rgcf, "r")
rgcf_files = rd.readlines()
rd.close()
for fil in rgcf_files:
    try:
        rd = open(fil[:-1], "r", encoding="utf8")
        pgm_file = rd.readlines()
        lines.append(len(pgm_file))
        rd.close()
    except OSError as ex:
        print(str(ex))
    continue
# print(" ".join(map(str, lines)))
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
wd = open(outnx, "w")
wd.close()
if not opt["-x"]:
    wd = open(outpv, "r" if exes[PV] is None else "w")
    wd.close()
for ix, fil in enumerate(rgcf_files):
    cmd_str = [f"o {fil[:-1]}", f"code 1:{str(lines[ix])}", "close", "exit", "EOF", ""]
    try:
        run_pgm(exes[NX], cmd_str, outnx)
        if exes[PV] is not None:
          run_pgm(exes[PV], cmd_str, outpv)
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
print("opcode regression complete")
