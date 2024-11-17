//
// Created by Dan Evans on 11/15/24.
//
#include "cs_global.h"
#include "cs_compile.h"
#include "cs_errors.h"
namespace Cstar
{
    static void ENTER(const char *X0, OBJECTS X1, TYPES X2, int X3)
    {
        Tx++;
        if (Tx == TMAX)
        {
            FATAL(1);
        } else
        {
            strcpy(TAB[Tx].NAME, X0);
            TAB[Tx].LINK = Tx - 1;
            TAB[Tx].OBJ = X1;
            TAB[Tx].TYP = X2;
            TAB[Tx].REF = 0;
            TAB[Tx].NORMAL = true;
            TAB[Tx].LEV = 0;
            TAB[Tx].ADR = X3;
            TAB[Tx].FORLEV = 0;
            TAB[Tx].PNTPARAM = false;
        }
    }

    static void LIBFINIT(int index, const char *name, int idnum)
    {
        strcpy(LIBFUNC[index].NAME, name);
        LIBFUNC[index].IDNUM = idnum;
    }

    void INITCOMPILER()
    {
        KSY[0] = DEFINESY;
        KSY[1] = DEFINESY;
        KSY[2] = INCLUDESY;
        KSY[3] = BREAKSY;
        KSY[4] = CASESY;
        KSY[5] = CINSY;
        KSY[6] = CONSTSY;
        KSY[7] = CONTSY;
        KSY[8] = COUTSY;
        KSY[9] = DEFAULTSY;
        KSY[10] = DOSY;
        KSY[11] = ELSESY;
        KSY[12] = ENDLSY;
        KSY[13] = ENUMSY;
        KSY[14] = FORSY;
        KSY[15] = FORALLSY;
        KSY[16] = FORKSY;
        KSY[17] = FUNCTIONSY;
        KSY[18] = GROUPINGSY;
        KSY[19] = IFSY;
        KSY[20] = JOINSY;
        KSY[21] = LONGSY;
        KSY[22] = MOVESY;
        KSY[23] = NEWSY;
        KSY[24] = RETURNSY;
        KSY[25] = SHORTSY;
        KSY[26] = CHANSY;
        KSY[27] = STRUCTSY;
        KSY[28] = SWITCHSY;
        KSY[29] = THENSY;
        KSY[30] = TOSY;
        KSY[31] = TYPESY;
        KSY[32] = UNIONSY;
        KSY[33] = UNSIGNEDSY;
        KSY[34] = VALUESY;
        KSY[35] = WHILESY;
        SPS['('] = LPARENT;
        SPS[')'] = RPARENT;
        SPS[','] = COMMA;
        SPS['['] = LBRACK;
        SPS[']'] = RBRACK;
        SPS[';'] = SEMICOLON;
        SPS['~'] = BITCOMPSY;
        SPS['{'] = LSETBRACK;
        SPS['^'] = BITXORSY;
        SPS['@'] = ATSY;
        SPS['}'] = RSETBRACK;
        SPS[28] = EOFSY;
        SPS[':'] = COLON;
        // CONSTBEGSYS = {PLUS, MINUS, INTCON, CHARCON, REALCON, IDENT};
        CONSTBEGSYS[PLUS] = true;
        CONSTBEGSYS[MINUS] = true;
        CONSTBEGSYS[INTCON] = true;
        CONSTBEGSYS[CHARCON] = true;
        CONSTBEGSYS[REALCON] = true;
        CONSTBEGSYS[IDENT] = true;
        // TYPEBEGSYS  = {IDENT, STRUCTSY, CONSTSY, SHORTSY, LONGSY, UNSIGNEDSY};
        TYPEBEGSYS[IDENT] = true;
        TYPEBEGSYS[STRUCTSY] = true;
        TYPEBEGSYS[CONSTSY] = true;
        TYPEBEGSYS[SHORTSY] = true;
        TYPEBEGSYS[LONGSY] = true;
        TYPEBEGSYS[UNSIGNEDSY] = true;
        // DECLBEGSYS  = {IDENT, STRUCTSY, CONSTSY, SHORTSY, LONGSY, UNSIGNEDSY, TYPESY, DEFINESY, INCLUDESY}; //+ TYPEBEGSYS;
        DECLBEGSYS = TYPEBEGSYS;
        DECLBEGSYS[TYPESY] = true;
        DECLBEGSYS[DEFINESY] = true;
        DECLBEGSYS[INCLUDESY] = true;
        // BLOCKBEGSYS = {IDENT, STRUCTSY, CONSTSY, SHORTSY, LONGSY, UNSIGNEDSY, TYPESY, DEFINESY}; // + TYPEBEGSYS;
        BLOCKBEGSYS = DECLBEGSYS;
        BLOCKBEGSYS[INCLUDESY] = false;
        //FACBEGSYS = {INTCON, CHARCON, REALCON, IDENT, LPARENT, NOTSY, DECREMENT, INCREMENT, PLUS, MINUS, TIMES, STRNG};
        FACBEGSYS[INTCON] = true;
        FACBEGSYS[CHARCON] = true;
        FACBEGSYS[REALCON] = true;
        FACBEGSYS[IDENT] = true;
        FACBEGSYS[LPARENT] = true;
        FACBEGSYS[NOTSY] = true;
        FACBEGSYS[DECREMENT] = true;
        FACBEGSYS[INCREMENT] = true;
        FACBEGSYS[PLUS] = true;
        FACBEGSYS[MINUS] = true;
        FACBEGSYS[TIMES] = true;
        FACBEGSYS[STRNG] = true;
//        STATBEGSYS = {IFSY, WHILESY, DOSY, FORSY, FORALLSY, SEMICOLON, FORKSY, JOINSY, SWITCHSY, LSETBRACK, RETURNSY,
//                      BREAKSY, CONTSY, MOVESY, CINSY, COUTSY};
        STATBEGSYS[IFSY] = true;
        STATBEGSYS[WHILESY] = true;
        STATBEGSYS[DOSY] = true;
        STATBEGSYS[FORSY] = true;
        STATBEGSYS[FORALLSY] = true;
        STATBEGSYS[SEMICOLON] = true;
        STATBEGSYS[FORKSY] = true;
        STATBEGSYS[JOINSY] = true;
        STATBEGSYS[SWITCHSY] = true;
        STATBEGSYS[LSETBRACK] = true;
        STATBEGSYS[RETURNSY] = true;
        STATBEGSYS[BREAKSY] = true;
        STATBEGSYS[CONTSY] = true;
        STATBEGSYS[MOVESY] = true;
        STATBEGSYS[CINSY] = true;
        STATBEGSYS[COUTSY] = true;
        // ASSIGNBEGSYS = {IDENT, LPARENT, DECREMENT, INCREMENT, TIMES};
        ASSIGNBEGSYS[IDENT] = true;
        ASSIGNBEGSYS[LPARENT] = true;
        ASSIGNBEGSYS[DECREMENT] = true;
        ASSIGNBEGSYS[INCREMENT] = true;
        ASSIGNBEGSYS[TIMES] = true;
        // COMPASGNSYS = {PLUSEQ, MINUSEQ, TIMESEQ, RDIVEQ, IMODEQ};
        COMPASGNSYS[PLUSEQ] = true;
        COMPASGNSYS[MINUSEQ] = true;
        COMPASGNSYS[TIMESEQ] = true;
        COMPASGNSYS[RDIVEQ] = true;
        COMPASGNSYS[IMODEQ] = true;
        // SELECTSYS = {LBRACK, PERIOD, RARROW};
        SELECTSYS[LBRACK] = true;
        SELECTSYS[PERIOD] = true;
        SELECTSYS[RARROW] = true;
        // EXECSYS = {IFSY, WHILESY, DOSY, FORSY, FORALLSY, SEMICOLON, FORKSY, JOINSY, SWITCHSY, LSETBRACK, RETURNSY,
        //            BREAKSY, CONTSY, MOVESY, CINSY, COUTSY, ELSESY, TOSY, DOSY, CASESY, DEFAULTSY};
        EXECSYS[IFSY] = true;
        EXECSYS[WHILESY] = true;
        EXECSYS[DOSY] = true;
        EXECSYS[FORSY] = true;
        EXECSYS[FORALLSY] = true;
        EXECSYS[SEMICOLON] = true;
        EXECSYS[FORKSY] = true;
        EXECSYS[JOINSY] = true;
        EXECSYS[SWITCHSY] = true;
        EXECSYS[LSETBRACK] = true;
        EXECSYS[RETURNSY] = true;
        EXECSYS[BREAKSY] = true;
        EXECSYS[CONTSY] = true;
        EXECSYS[MOVESY] = true;
        EXECSYS[CINSY] = true;
        EXECSYS[COUTSY] = true;
        EXECSYS[ELSESY] = true;
        EXECSYS[TOSY] = true;
        EXECSYS[CASESY] = true;
        EXECSYS[DEFAULTSY] = true;
        // NONMPISYS = {CHANSY, FORKSY, JOINSY, FORALLSY};
        NONMPISYS[CHANSY] = true;
        NONMPISYS[FORKSY] = true;
        NONMPISYS[JOINSY] = true;
        NONMPISYS[FORALLSY] = true;
        // STANTYPS = {NOTYP, REALS, INTS, BOOLS, CHARS};
        STANTYPS[NOTYP] = true;
        STANTYPS[REALS] = true;
        STANTYPS[INTS] = true;
        STANTYPS[BOOLS] = true;
        STANTYPS[CHARS] = true;
        LC = 0;
        LL = 0;
        LL2 = 0;
        CC = 0;
        CC2 = 0;
        CH = ' ';
        CPNT = 1;
        LNUM = 0;
        ERRPOS = 0;
        ERRS = 0;
        INSYMBOL();
        EXECNT = 0;
        EOFCOUNT = 0;
        Tx = -1;
        A = 0;
        B = 1;    // index to BTAB
        SX = 0;
        C2 = 0;
        C = 0;
        ERRORCOUNT = 0;
        OKBREAK = false;
        BREAKPNT = 0;
        ITPNT = 1;
        DISPLAY[0] = 1;
        strcpy(DUMMYNAME, "************00");
        INCLUDEFLAG = false;
        FATALERROR = false;
        PROTOINDEX = -1;
        ENTER("              ", VARIABLE, NOTYP, 0);
        ENTER("FALSE         ", KONSTANT, BOOLS, 0);
        ENTER("TRUE          ", KONSTANT, BOOLS, 1);
        ENTER("NULL          ", KONSTANT, PNTS, 0);
        ENTER("CHAR          ", TYPE1, CHARS, 1);
        ENTER("BOOLEAN       ", TYPE1, BOOLS, 1);
        ENTER("INT           ", TYPE1, INTS, 1);
        ENTER("FLOAT         ", TYPE1, REALS, 1);
        ENTER("DOUBLE        ", TYPE1, REALS, 1);
        ENTER("VOID          ", TYPE1, VOIDS, 1);
        ENTER("SPINLOCK      ", TYPE1, LOCKS, 1);
        ENTER("SELF          ", FUNKTION, INTS, 19);
        ENTER("CLOCK         ", FUNKTION, REALS, 20);
        ENTER("SEQTIME       ", FUNKTION, REALS, 21);
        ENTER("MYID          ", FUNKTION, INTS, 22);
        ENTER("SIZEOF        ", FUNKTION, INTS, 24);
        ENTER("SEND          ", PROZEDURE, NOTYP, 3);
        ENTER("RECV          ", PROZEDURE, NOTYP, 4);
        ENTER("NEW           ", PROZEDURE, NOTYP, 5);
        ENTER("DELETE        ", PROZEDURE, NOTYP, 6);
        ENTER("LOCK          ", PROZEDURE, NOTYP, 7);
        ENTER("UNLOCK        ", PROZEDURE, NOTYP, 8);
        ENTER("DURATION      ", PROZEDURE, NOTYP, 9);
        ENTER("SEQOFF        ", PROZEDURE, NOTYP, 10);
        ENTER("SEQON         ", PROZEDURE, NOTYP, 11);
        ENTER("              ", PROZEDURE, NOTYP, 0);
        BTAB[1].LAST = Tx;
        BTAB[1].LASTPAR = 1;
        BTAB[1].PSIZE = 0;
        BTAB[1].VSIZE = 0;
        LIBFINIT(1, "ABS           ", 1);
        LIBFINIT(2, "FABS          ", 2);
        LIBFINIT(3, "CEIL          ", 9);
        LIBFINIT(4, "FLOOR         ", 10);
        LIBFINIT(5, "SIN           ", 11);
        LIBFINIT(6, "COS           ", 12);
        LIBFINIT(7, "EXP           ", 13);
        LIBFINIT(8, "LOG           ", 14);
        LIBFINIT(9, "SQRT          ", 15);
        LIBFINIT(10, "ATAN          ", 16);
        LIBFINIT(11, "MPI_INIT      ", 50);
        LIBFINIT(12, "MPI_FINALIZE  ", 51);
        LIBFINIT(13, "MPI_COMM_RANK ", 52);
        LIBFINIT(14, "MPI_COMM_SIZE ", 53);
        LIBFINIT(15, "MPI_SEND      ", 54);
        LIBFINIT(16, "MPI_RECV      ", 55);
        LIBFINIT(17, "MPI_GET_COUNT ", 56);
        LIBFINIT(18, "MPI_BARRIER   ", 57);
        LIBFINIT(19, "MPI_BCAST     ", 58);
        LIBFINIT(20, "MPI_GATHER    ", 59);
        LIBFINIT(21, "MPI_SCATTER   ", 60);
        LIBFINIT(22, "MPI_REDUCE    ", 61);
        LIBFINIT(23, "MPI_ALLREDUCE ", 62);
        LIBFINIT(24, "MPI_IPROBE    ", 63);
        LIBFINIT(25, "MPI_CART_CREAT", 64);
        LIBFINIT(26, "MPI_CARTDIM_GE", 65);
        LIBFINIT(27, "MPI_CART_GET  ", 66);
        LIBFINIT(28, "MPI_CART_RANK ", 67);
        LIBFINIT(29, "MPI_CART_COORD", 68);
        LIBFINIT(30, "MPI_CART_SHIFT", 69);
        LIBFINIT(31, "MPI_COMM_FREE ", 70);
        LIBFINIT(32, "MPI_WTIME     ", 71);
        LIBFINIT(33, "MALLOC        ", 17);
        LIBFINIT(34, "CALLOC        ", 18);
        LIBFINIT(35, "REALLOC       ", 19);
        LIBFINIT(36, "FREE          ", 20);
        LIBFINIT(37, "STRCAT        ", 21);
        LIBFINIT(38, "STRCHR        ", 22);
        LIBFINIT(39, "STRCMP        ", 23);
        LIBFINIT(40, "STRCPY        ", 24);
        LIBFINIT(41, "STRLEN        ", 25);
        LIBFINIT(42, "STRSTR        ", 26);
        LIBFINIT(43, "ISALNUM       ", 27);
        LIBFINIT(44, "ISALPHA       ", 28);
        LIBFINIT(45, "ISCNTRL       ", 29);
        LIBFINIT(46, "ISDIGIT       ", 30);
        LIBFINIT(47, "ISGRAPH       ", 31);
        LIBFINIT(48, "ISLOWER       ", 32);
        LIBFINIT(49, "ISPRINT       ", 33);
        LIBFINIT(50, "ISPUNCT       ", 34);
        LIBFINIT(51, "ISSPACE       ", 35);
        LIBFINIT(52, "ISUPPER       ", 36);
        LIBFINIT(53, "ISXDIGIT      ", 37);
        LIBFINIT(54, "TOLOWER       ", 38);
        LIBFINIT(55, "TOUPPER       ", 39);
        LIBFINIT(56, "ABORT         ", 40);
        LIBFINIT(57, "EXIT          ", 41);
        LIBFINIT(58, "DIV           ", 42);
        LIBFINIT(59, "RAND          ", 43);
    }
}