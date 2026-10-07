#include "types.h"
#include "riscv.h"
#include "defs.h"

static void task_delay(volatile int count)
{
    count *= 50000;
    while(count--);
}

#define DELAY 1000

void user_task0(void)
{
    printf("Task0 : Created!\n");
    while(1){
        printf("Task0 : Running...\n");
        task_delay(DELAY);
    }
}

void user_task1(void)
{
    printf("Task1 : Created!\n");
    while(1){
        printf("Task1 : Running...\n");
        task_delay(DELAY);
    }
}