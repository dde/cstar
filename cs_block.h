//
// Created by Dan Evans on 1/17/24.
//

#ifndef CSTAR_CS_BLOCK_H
#define CSTAR_CS_BLOCK_H
namespace Cstar
{
    typedef struct BlockLocal
    {
        SYMSET FSYS;
        bool ISFUN;
        int LEVEL;
        int PRT;
        /* parameters above */
        int DX;
        int RDX;
        INDEX RLAST;
        int PRB;
        int PCNT;
        int X, V;
        int FLEVEL;
        int NUMWITH, MAXNUMWITH;
        bool CREATEFLAG;
        bool ISDECLARATION;
        bool UNDEFMSGFLAG;
        InterpLocal *blkil;
    } BlockLocal;
}
#endif //CSTAR_CS_BLOCK_H
