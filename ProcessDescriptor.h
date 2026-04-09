//
// Created by Dan Evans on 3/5/26.
//
#ifndef PROCESSDESCRIPTOR_H
#define PROCESSDESCRIPTOR_H
#include "cs_global.h"
#include "cs_compile.h"
#include "cs_interpret.h"
namespace Cstar
{
    /*
    extern int FINDFRAME(Cstar::InterpLocal *il, int LENGTH);
    class PROCESSDESCRIPTOR;
    typedef PROCESSDESCRIPTOR *PROCPNT;
    typedef PROCESSDESCRIPTOR PRD;
    */
    struct PROCESSDESCRIPTOR
    {
        int T;  // process's stack top index
        int B = 0;
        int PC = 0;  // process's program counter (index into ORDER type CODE array)
        int STACKSIZE;  // process's stack size
        int DISPLAY[LMAX + 1]; //  stack base array, starting at [2]
        PROCPNT PARENT;  // parent process, that started this process
        int NUMCHILDREN = 0;  // number of started and active child processes
        int BASE;  // like B
        int PID;   // process ID
        double MAXCHILDTIME = 0.0;
        double TIME;
        double VIRTUALTIME = 0.0;
        double MAXFORKTIME = 0.0;
        double WAKETIME = 0.0;
        int FORLEVEL = 0;
        int FORINDEX = 0;
        int PROCESSOR;  // processor number (index in PROCTAB array)
        int ALTPROC = -1;  // allocated processor (when running on processor 0)
        int FORKCOUNT = 0;
        int JOINSEM = 0;
        enum STATE {READY, RUNNING, BLOCKED, DELAYED, TERMINATED, SPINNING} STATE = READY;
        enum READSTATUS {NONE, ATCHANNEL, HASTICKET} READSTATUS = NONE;
        enum PRIORITY {LOW, HIGH} PRIORITY = LOW;
        bool SEQON = true;
        bool GROUPREP = false;
        PROCESSDESCRIPTOR(PROCPNT parent, Cstar::InterpLocal *il, int processor);
        ~PROCESSDESCRIPTOR() = default;
    };
}
#endif // PROCESSDESCRIPTOR_H
