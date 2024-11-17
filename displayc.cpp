//
// Created by Dan Evans on 2/6/24.
//
#include <cstdio>
#include "cs_global.h"
#include "cs_compile.h"
#include "cs_block.h"
namespace Cstar
{
    const char *lookupSym(int, int);
    const char *arrayName(int);
    const char *opcodes[115] = {"pushstkloc", // 0
                                       "pushstklocri", "",
                                       "movdspbas", "clrchnoseq", "unhookprcr",
                                       "noop",
                                       "jmpseqon", "pushsys",
                                       "mpiinit",
                                       "jmp",
                                       "popjmpfalse",
                                       "",
                                       "getstkfrm1", "pushfm[T]",
                                       "addint", "", "",
                                       "getstkfrm2",
                                       "callblk",
                                       "swap", "pushaelstkloc",
                                       "pushpid",
                                       "cpystk[T]>[T-1]",
                                       "pushimm",
                                       "", "cnvi2r", "cin",
                                       "outstr",
                                       "outint",
                                       "setwidth/prec", "end",
                                       "returnv",
                                       "return",
                                       "rplindfmstk",
                                       "not", "negate",
                                       "outreal",
                                       "stindstk", "", "", "",
                                       "", "", "",
                                       "cmpeq",
                                       "cmpne",
                                       "cmplt",
                                       "cmple",
                                       "cmpgt",
                                       "cmpge",
                                       "or",
                                       "add",
                                       "sub", "", "",
                                       "and",
                                       "times",
                                       "intdiv",
                                       "intmod","", "", "",
                                       "outendl", "recvchvar", "recvch[var]", "send",
                                       "fork", "",
                                       "procend --fork",
                                       "procend --child",
                                       "recvch[T]", "",
                                       "pushprcr",
                                       "forall",
                                       "forgrpT-2gtT-1jmp",
                                       "incrT-2ltT-1jmp",
                                       "",
                                       "wakepar", "findprctb",
                                       "", "", "initarr", "zeroarr", "dup", "join", "testvar",
                                       "pushrconfmtbl", "",
                                       "noswitchon",
                                       "noswitchoff", "", "sendri", "",
                                       "tststrm",
                                       "tststrmind",
                                       "tststrmstkind",
                                       "", "copymsg", "",
                                       "",
                                       "lock[T]", "unlock[T]", "",
                                       "ltincr[T-1]jmp",
                                       "",
                                       "seqoff",
                                       "seqon",
                                       "incr[T]imm",
                                       "decr[T]imm",
                                       "add3", "pop", "condrel[T]", "cpymsg", ""

    };
    static const char *types[] = {"NOTYP", "REALS", "INTS", "BOOLS", "CHARS", "ARRAY", "CHANS", "RECS",
                                "PNTS", "FORWD", "LOCKS", "VOIDS"};
    static const char *states[] = {"READY", "RUNNING", "BLOCKED", "DELAYED", "TERMINATED", "SPINNING"};
    static const char *readstatus[] = {"NONE", "ATCHANNEL", "HASTICKET"};
    static const char *priority[] = {"LOW", "HIGH"};
    static const char *objects[] = {"KONSTANT", "VARIABLE", "TYPE1", "PROZEDURE",
                                    "FUNKTION", "COMPONENT", "STRUCTAG"};
    static const char *nosym = "nosym";
    static const char *prepost[] = {"pre", "post"};
    static const char *sysname[] = {"", "", "", "", "", "", "", "", "", "",
                                    "int()", "", "", "", "", "", "", "", "", "self",
                                    "clock", "seqtime", "myid", "10"};
    static const char *status[] = {"NEVERUSED", "EMPTY    ", "RESERVED ", "FULL     "};

    static struct CurExec
    {
        int functionSymtabIndex;
        int blockTableIndex;
        int functionVarFirst;
        int functionVarLast;
    } curExec = {0, 0, 0, 0};
    void dumpInst(int ix)
    {
        int F, X, Y;
        const char *op;
        char ibuf[80];

        F = CODE[ix].F;
        X = CODE[ix].X;
        Y = CODE[ix].Y;
        op = (opcodes[F] == nullptr) ? "..." :  opcodes[F];
        switch (F)
        {
            case 0:
            case 1:
                snprintf(ibuf, sizeof ibuf, "%4d: %3d %d,%d %s %s\n", ix,
                         F, X, Y, op, lookupSym(X, Y));
                break;
            case 8:
                snprintf(ibuf, sizeof ibuf, "%4d: %3d %d,%d %s %s\n", ix,
                         F, X, Y, op, sysname[Y]);
                break;
            case 7:
            case 10:
                snprintf(ibuf, sizeof ibuf, "%4d: %3d %d,%d %s %d\n", ix,
                         F, X, Y, op, Y);
                break;
            case 18:
                snprintf(ibuf, sizeof ibuf, "%4d: %3d %d,%d %s %s\n", ix,
                         F, X, Y, op, TAB[Y].NAME);
                curExec.functionSymtabIndex = Y;
                curExec.blockTableIndex = TAB[Y].REF;
                curExec.functionVarFirst = BTAB[curExec.blockTableIndex].LAST;
                curExec.functionVarLast = BTAB[curExec.blockTableIndex].LASTPAR;
                break;
            case 19:
                snprintf(ibuf, sizeof ibuf, "%4d: %3d %d,%d %s %s\n", ix,
                         F, X, Y, op, TAB[X].NAME);
                break;
            case 23:
            case 110:
                snprintf(ibuf, sizeof ibuf, "%4d: %3d %d,%d %s len=%d\n", ix,
                         F, X, Y, op, X);
                break;

            case 21:
                snprintf(ibuf, sizeof ibuf, "%4d: %3d %d,%d %s %s\n", ix,
                         F, X, Y, op, arrayName(Y));
                break;
            case 24:
            case 75:
            case 76:
            case 112:
                snprintf(ibuf, sizeof ibuf, "%4d: %3d %d,%d %s %d\n", ix,
                         F, X, Y, op, Y);
                break;
            case 64:
                snprintf(ibuf, sizeof ibuf, "%4d: %3d %d,%d %s %s\n", ix,
                         F, X, Y, op, lookupSym(X, Y));
                break;
            case 104:
                snprintf(ibuf, sizeof ibuf, "%4d: %3d %d,%d %s %d%s\n", ix,
                         F, X, Y, op, X, (Y == 1) ? ",grprep" :"");
                break;
            case 108:
            case 109:
                snprintf(ibuf, sizeof ibuf, "%4d: %3d %d,%d %s %s %d\n", ix,
                         F, X, Y, op, prepost[Y], X);
                break;
            default:
                snprintf(ibuf, sizeof ibuf, "%4d: %3d %d,%d %s\n", ix, F, X, Y, op);
                break;
        }
        fprintf(STDOUT, "%s", ibuf);
    }
    void dumpLInst(int ix, int *line)
    {
        while (LOCATION[*line] <= ix)
        {
            fprintf(STDOUT, "Line %4d\n", *line);
            ++*line;
        }
        dumpInst(ix);
    }

    void dumpCode()
    {
        int ix;
        int line = 1;
        for (ix = 0; ix < LC; ++ix)
        {
           dumpLInst(ix, &line);
        }
    }
    void dumpSymbols()
    {
        int ix;
//        const char *np;
//        ALFA name;
        fprintf(STDOUT, "Symbol Table\n");
        fprintf(STDOUT, "Indx Name           Link     Object  Type Ref Nm Lev   Addr   Size Fref FLev PP\n");
        for (ix = 0; ix <= Tx; ++ix)
        {
            // strcpy(name, TAB[ix].NAME);
            fprintf(STDOUT, "%4d %.14s %4d %10s %5s %3d %2d %3d %6d %6ld %4d %4d %2d\n", ix,
                    TAB[ix].NAME,
                    TAB[ix].LINK,
                    objects[TAB[ix].OBJ],
                    types[TAB[ix].TYP],
                    TAB[ix].REF,
                    TAB[ix].NORMAL,
                    TAB[ix].LEV,
                    TAB[ix].ADR,
                    TAB[ix].SIZE,
                    TAB[ix].FREF,
                    TAB[ix].FORLEV,
                    TAB[ix].PNTPARAM);
        }
    }
    void dumpArrays()
    {
        int ix;
        fprintf(STDOUT, "Array Table\n");
        fprintf(STDOUT, "Indx IxTyp ElTyp ERef Low High ElSz Siz\n");
        for (ix = 0; ix <= A; ++ix)
        {
            fprintf(STDOUT, "%4d %5s %5s %4d %3d %4d %4d %3d\n", ix,
                    types[ATAB[ix].INXTYP],
                    types[ATAB[ix].ELTYP],
                    ATAB[ix].ELREF,
                    ATAB[ix].LOW,
                    ATAB[ix].HIGH,
                    ATAB[ix].ELSIZE,
                    ATAB[ix].SIZE);
        }
    }
    void dumpBlocks()
    {
        int ix, lst, ct;
        fprintf(STDOUT, "Block Table\n");
        fprintf(STDOUT, "  Display\n");
        ix = 1;
        while (ix <= LMAX && DISPLAY[ix] > 0)
        {
            fprintf(STDOUT, "  D%d %d\n", ix, DISPLAY[ix]);
            ix += 1;
        }
        fprintf(STDOUT, "Indx  Last LstPr PSize VSize PrCnt\n");
        for (ix = 0; ix <= B; ++ix)
        {
            fprintf(STDOUT, "%4d %5d %5d %5d %5d %5d\n", ix,
                    BTAB[ix].LAST,
                    BTAB[ix].LASTPAR,
                    BTAB[ix].PSIZE,
                    BTAB[ix].VSIZE,
                    BTAB[ix].PARCNT);
        }
        for (ix = B; ix >= 1; --ix)
        {
            lst = BTAB[ix].LAST;
            fprintf(STDOUT, "block %d declares\n", ix);
            ct = 0;
            while (lst != 0)
            {
                fprintf(STDOUT, " %s", TAB[lst].NAME);
                if (++ct % 8 == 0)
                {
                    fprintf(STDOUT, "\n");
                }
                lst = TAB[lst].LINK;
            }
            if (ct % 8 != 0)
                fprintf(STDOUT, "\n");
        }
    }
    void dumpReals()
    {
        int ix;
        fprintf(STDOUT, "Real Constants\n");
        fprintf(STDOUT, "Indx     RConst  IConval    RConval\n");
        for (ix = 0; ix <= CPNT; ++ix)
        {
            fprintf(STDOUT, "%4d %12.6f %6d %12.6f\n", ix, CONTABLE[ix], INITABLE[ix].IVAL, INITABLE[ix].RVAL);
        }
    }
    const char *lookupSym(int lev, int adr)
    {
        int ix, blev;
//        for (ix = Tx; ix >= 0; --ix)
//        {
//            if (TAB[ix].ADR == adr && TAB[ix].LEV == lev)
//                return TAB[ix].NAME;
//        }
//        for (ix = curExec.functionVarFirst; ix >= curExec.functionVarLast; --ix)
//        {
//            if (TAB[ix].ADR == adr && TAB[ix].LEV == lev)
//                return TAB[ix].NAME;
//        }
        ix = BTAB[lev].LAST;
        while (ix != 0)
        {
            if (TAB[ix].ADR == adr)
                return TAB[ix].NAME;
            ix = TAB[ix].LINK;
        }
        return nosym;
    }
    const char *arrayName(int ref)
    {
        int ix;
        for (ix = Tx; ix >= 0; --ix)
        {
            if (TAB[ix].TYP == ARRAYS && TAB[ix].REF == ref)
                return TAB[ix].NAME;
        }
        return nosym;
    }
}
