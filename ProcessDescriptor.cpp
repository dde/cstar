//
// Created by Dan Evans on 3/5/26.
//
#include "ProcessDescriptor.h"
namespace Cstar
{
    extern int FINDFRAME(InterpLocal *il, int LENGTH);
    PROCESSDESCRIPTOR::PROCESSDESCRIPTOR(PROCPNT parent, Cstar::InterpLocal *il, int proc, int processor)
    {
        int H1, J;
        PID = proc;
        memcpy(DISPLAY, parent->DISPLAY, sizeof(DISPLAY));
        T = FINDFRAME(il, WORKSIZE) - 1;
        if (T > 0) {
            STACKSIZE = T + WORKSIZE;
            BASE = ++T;
            B = parent->B;
            // for (J = T; J < T + il->STKMAIN; J += 1) {
            //     il->S[J] = 0;
            //     il->SLOCATION[J] = processor;
            //     il->RS[J] = 0.0;
            // }
            // for (J = H1; J < H1 + BASESIZE; J += 1) {
            //     il->STARTMEM[J] = -il->STARTMEM[J];
            // }
        }
        TIME = parent->TIME;
        FORLEVEL = parent->FORLEVEL;
        FORKCOUNT = 1;
        PARENT = parent;
        PROCESSOR = processor;
        // if (il->PROCTAB[processor].STATUS == Cstar::PROCTAB::STATUS::NEVERUSED) {
        //     il->USEDPROCS++;
        // }
        // il->PROCTAB[processor].STATUS = Cstar::PROCTAB::STATUS::FULL;
        // il->PROCTAB[processor].NUMPROC++;
        /*
        J = 1;
        while (DISPLAY[J] != -1) {
            il->S[DISPLAY[J] + 5] += 1;
            J += 1;
        }
        parent->FORKCOUNT += 1;
        */
    }
}


