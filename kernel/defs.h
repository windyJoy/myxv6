struct context;
struct proc;
struct spinlock;

//uart.c
void            uartinit(void);
void            uartputc_sync(int);

//printf.c
int             printf(char*, ...) __attribute__ ((format (printf, 1, 2)));
void            panic(char*) __attribute__((noreturn));
void            printfinit(void);

// string.c
int             memcmp(const void*, const void*, uint);
void*           memmove(void*, const void*, uint);
void*           memset(void*, int, uint);
char*           safestrcpy(char*, const char*, int);
int             strlen(const char*);
int             strncmp(const char*, const char*, uint);
char*           strncpy(char*, const char*, int);

// kalloc.c
void*           kalloc(void);
void            kfree(void*);
void            kinit(void);

// proc.c
int             cpuid(void);
struct cpu*     mycpu(void);
struct proc*    myproc(void);
void            sched(void);
void            yield(void);
void            procinit(void);
void            scheduler(void) __attribute__((noreturn));
void            userinit(void);

// swtch.S
void            swtch(struct context*, struct context*);

// user.c
void            user_task0(void);
void            user_task1(void);

// trap.c
void            trapinit(void);
void            trapinithart(void);

// spinlock.c
void            initlock(struct spinlock* lk, char* name);
void            push_off(void);
void            pop_off(void);
int             holding(struct spinlock*lk);
void            acquire(struct spinlock *lk);
void            release(struct spinlock *lk);