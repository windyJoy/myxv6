#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "proc.h"
#include "defs.h"


void kernelvec();

int devintr();

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
kerneltrap()
{
    int which_dev = 0;
    uint64 sepc = r_sepc();
    uint64 sstatus = r_sstatus();
    uint64 scause = r_scause();

    if((sstatus & SSTATUS_SPP) == 0)
        panic("kerneltrap: not from supervisor mode");
    
    if(intr_get() != 0)
        panic("kerneltrap: interrupts enable");

    if((which_dev = devintr()) == 0){
        printf("scause=0x%lx sepc=0x%lx stval=0x%lx\n", scause, r_sepc(), r_stval());
        panic("kerneltrap");
    }

    if(which_dev == 2 && myproc() != 0)
        yield();
    
    w_sepc(sepc);
    w_sstatus(sstatus);
}

void
clockintr()
{
    w_stimecmp(r_time() + 1000000);
}

int
devintr()
{
    uint64 scause = r_scause();
    if(scause == 0x8000000000000009L){
        printf("kerneltrap: supervisor external interrupt, via PLIC\n");
        return 1;
    }
    else if(scause == 0x8000000000000005L){
        clockintr();
        return 2;
    }
    else{
        return 0;
    }
}