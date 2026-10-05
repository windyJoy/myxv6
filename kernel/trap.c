#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "proc.h"
#include "defs.h"


void kernelvec();

void
trapinit(void)
{

}

void
trapinithart(void)
{
    w_stvec((uint64)kernelvec);
}

void
clockintr()
{
    w_stimecmp(r_time() + 1000000);
}

void
kerneltrap()
{
    uint64 sstatus = r_sstatus();
    uint64 scause = r_scause();

    if((sstatus & SSTATUS_SPP) == 0)
        panic("kerneltrap: not from supervisor mode");
    
    if(intr_get() != 0)
        panic("kerneltrap: interrupts enable");

    if(scause & 0x8000000000000000L){
        printf("Asynchronous trap - interrupt!\n");
        if(scause == 0x8000000000000005L){
            clockintr();
            printf("timer interrupt\n");
        }
    }
    else{
        printf("Synchronous trap - exception!\n");
        printf("scause=0x%lx sepc=0x%lx stval=0x%lx\n", scause, r_sepc(), r_stval());
        panic("kerneltrap");
    }
}
