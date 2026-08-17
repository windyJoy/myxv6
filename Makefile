CC = riscv64-linux-gnu-gcc
LD = riscv64-linux-gnu-ld
QEMU = qemu-system-riscv64

CFLAGS = -march=rv64gc -ffreestanding -nostdlib -fno-builtin -mcmodel=medany
LDFLAGS = -T kernel/kernel.ld

OBJS = kernel/entry.o kernel/main.o kernel/start.o

kernel/kernel: $(OBJS) kernel/kernel.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

kernel/entry.o: kernel/entry.S
	$(CC) $(CFLAGS) -c $< -o $@

kernel/main.o: kernel/main.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel/start.o: kernel/start.c kernel/types.h kernel/param.h kernel/riscv.h
	$(CC) $(CFLAGS) -c $< -o $@

qemu: kernel/kernel
	$(QEMU) \
		-machine virt \
		-bios none \
		-kernel kernel/kernel \
		-m 128M \
		-nographic

qemu-gdb: kernel/kernel
	$(QEMU) \
    	-machine virt \
    	-bios none \
    	-kernel kernel/kernel \
    	-m 128M \
    	-nographic \
    	-S \
    	-gdb tcp::1234

clean:
	rm -f kernel/*.o kernel/kernel