//
// Created by Dan Evans on 3/23/26.
//
#include "cs_global.h"
#include "cs_compile.h"
#include "cs_interpret.h"

namespace Cstar
{
    ACTIVEPROCESS::ACTIVEPROCESS(PROCESSDESCRIPTOR *proc)
    {
        PDES = proc;
        NEXT = nullptr;
    }
    void InterpLocal::enqActiveProc(ACTIVEPROCESS *active)
    {
        active->NEXT = ACPTAIL->NEXT;
        ACPTAIL->NEXT = active;
        ACPTAIL = active;
    }
    /*
    void InterpLocal::stackInit(STYPE *stk)
    {
        return;
    }
    template<typename T, typename... Arg_t>
    void InterpLocal::stackInit(STYPE *stk, T value, Arg_t... args)
    {
        *stk = (STYPE)value;
        stackInit(stk + 1, args...);
    }
    */
}
