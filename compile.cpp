//
// Created by Dan Evans on 11/15/24.
//
#include <string>
#include <cstring>
#define EXPORT_CS_GLOBAL
#include "cs_global.h"
#define EXPORT_CS_COMPILE
#include "cs_compile.h"
namespace Cstar
{
    extern void dumpCode();
    extern void dumpSymbols();
    extern void dumpArrays();
    extern void dumpBlocks();
    extern void dumpReals();
    extern void showConsoleList(bool);
    extern void BLOCK(/*InterpLocal *il, */SYMSET FSYS, bool ISFUN, int LEVEL, int PRT);
    extern void ERROR(int);

    int MAINFUNC;
    void compile()
    {
        INITCOMPILER();
        // strcpy(PROGNAME, "PROGRAM       ");
        MAINFUNC = -1;
        BLOCK(/*il, */DECLBEGSYS, false, 1, Tx);
        if (SY != EOFSY)
            ERROR(22);
        if (BTAB[2].VSIZE + WORKSIZE > STMAX)
            ERROR(49);
        if (MAINFUNC < 0)
            ERROR(100);
        else
        {
            if (MPIMODE)
            {
                EMIT(9);
                EMIT1(18, MAINFUNC);
                EMIT1(19, BTAB[TAB[MAINFUNC].REF].PSIZE - 1);
                EMIT(69);
            }
            EMIT1(18, MAINFUNC);
            EMIT1(19, BTAB[TAB[MAINFUNC].REF].PSIZE - 1);
        }
        EMIT(31);
        //il->ENDLOC = LC;
        LOCATION[LNUM + 1] = LC;
        //std::cout << std::endl;
    }
}
static void usage(const char *pgm)
{
    printf("Cstar (C*) compiler\n");
    printf("usage: %s [-h] [-l] [-m] [-o] [-Xabcrs] [file]\n", pgm);
    printf("  h  display this help and exit\n");
    printf("  l  display listing on the console\n");
    printf("  m  set MPI ON\n");
    printf("  o  write an object file\n");
    printf("  file  compilation file\n");
    printf("  X  execution options, combined in any order after X (no spaces)\n");
    printf("     a  display the array table\n");
    printf("     b  display the block table\n");
    printf("     c  display the generated interpreter code\n");
    printf("     r  display the real constant table\n");
    printf("     s  display the symbol table\n");
    std::exit(1);
}
static bool code_list = false;
static bool block_list = false;
static bool array_list = false;
static bool real_list = false;
static bool symbol_list = false;
static bool object_file = false;
static std::string sig = "CST*";
static std::string fto = "csto";
static void doOption(const char *opt, const char *pgm)
{
    int ix;
    switch (*opt)
    {
        case 'X':
            ix = 1;
            while (opt[ix] != '\0')
            {
                switch (opt[ix])
                {
                    case 'a':
                        // Cstar::showArrayList(true);
                        array_list = true;
                        break;
                    case 'b':
                        // Cstar::showBlockList(true);
                        block_list = true;
                        break;
                    case 'c':
                        // Cstar::showCodeList(true);
                        code_list = true;
                        break;
                    case 'r':
                        // Cstar::showRealList(true);
                        real_list = true;
                        break;
                    case 's':
                        // Cstar::showSymbolList(true);
                        symbol_list = true;
                        break;
//                    case 't':
//                        Cstar::showInstTrace(true);
//                        break;
                    default:
                        break;
                }
                ix += 1;
            }
            break;
        case 'l':
            Cstar::showConsoleList(true);
            break;
        case 'm':
            Cstar::MPIMODE = true;
            break;
        case 'o':
            object_file = true;
            break;
        default:
            usage(pgm);
            break;
    }
}
static void write_obj(FILE *obj)
{

    int code_last, inst_len;
    code_last = Cstar::LC;
    inst_len = sizeof Cstar::CODE[0];
    fwrite(sig.c_str(), 1, 4, obj);
    fwrite(Cstar::CODE, inst_len, code_last, obj);
}
std::string obj_name(const char *fn)
{
    int ln, ix;
    std::string nm = fn;
    ix = ln = (int)nm.length();
    while (--ix > 0)
    {
        if (fn[ix] == '.')
        {
          nm.replace(ix + 1, ln, fto);
          // objnm = (char *)std::malloc(ln + 1 + 5);  // 4 byte file type plus null
          break;
        }
    }
    return nm ;
}
static void cs_error(const char *p, int ern = 0, const char *p2 = "")
{
    //std::cerr << p << " " << p2 << "\n";
    fprintf(stderr, "cs%03d %s %s\n", ern, p, p2);
    std::exit(1);
}
int main(int argc, char *argv[])
{
    int ix;
    FILE *cfile, *lfile, *ofile;
    char *from_file = nullptr;
    std::string objnm;
    const char *list_file = "LISTFILE.TXT";
#ifdef MAC
    __sFILE *stdin_save = nullptr;
    Cstar::STDOUT = __stdoutp;
#else
    FILE *stdin_save = nullptr;
    Cstar::STDOUT = stdout;
#endif
    if (argc == 1)
        usage(argv[0]);
    for (ix = 1; ix < argc; ++ix)
    {
        if (argv[ix][0] == '-')
        {
            doOption(&argv[ix][1], argv[0]);
        }
        else if (from_file == nullptr)
        {
            from_file = argv[ix];
        }
        else
            usage(argv[0]);
    }
    cfile = fopen(from_file, "r");
    if (cfile == nullptr)
    {
        cs_error("cannot open input file", 1, from_file);
        return 1;
    }
    Cstar::SRC = cfile;
    lfile = fopen(list_file, "w");
    if (lfile == nullptr)
    {
        cs_error("cannot open ", 1, list_file);
        return 1;
    }
    fprintf(lfile, "%s\n", from_file);
    Cstar::LIS = lfile;
    Cstar::compile();
    fclose(lfile);
    fclose(cfile);
    // SRCOPEN = true;
    if (code_list)
        Cstar::dumpCode();
    if (block_list)
        Cstar::dumpBlocks();
    if (symbol_list)
        Cstar::dumpSymbols();
    if (array_list)
        Cstar::dumpArrays();
    if (real_list)
        Cstar::dumpReals();
    if (object_file)
    {
        objnm = obj_name(from_file);
        ofile = fopen(objnm.c_str(), "w");
        if (ofile == nullptr)
        {
            cs_error("cannot open object file ", 1, objnm.c_str());
            return 1;
        }
        write_obj(ofile);
        fclose(ofile);
    }
    return 0;
}

