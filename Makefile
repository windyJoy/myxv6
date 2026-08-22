K = kernel

OBJS = \
	$(K)/entry.o \
	$(K)/start.o \
	$(K)/main.o \
	$(K)/printf.o \
	$(K)/uart.o \


CC = riscv64-linux-gnu-gcc
LD = riscv64-linux-gnu-ld
QEMU = qemu-system-riscv64

CFLAGS = -Wall -O -ggdb \
	-ffreestanding \
	-mcmodel=medany \
	-MD

LDFLAGS = -z max-page-size=4096

$(K)/kernel: $(OBJS) $(K)/kernel.ld
	$(LD) $(LDFLAGS) \
		-T $(K)/kernel.ld \
		-o $@ $(OBJS)

$(K)/%.o: $(K)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(K)/%.o: $(K)/%.S
	$(CC) $(CFLAGS) -c -o $@ $<

-include $(K)/*.d

qemu: $(K)/kernel
	$(QEMU) \
		-machine virt \
		-bios none \
		-kernel $(K)/kernel \
		-m 128M \
		-smp 1 \
		-nographic

qemu-gdb: $(K)/kernel
	$(QEMU) \
		-machine virt \
		-bios none \
		-kernel $(K)/kernel \
		-m 128M \
		-smp 1 \
		-nographic \
		-S \
		-gdb tcp::1234

clean:
	rm -f $(K)/*.o $(K)/*.d $(K)/kernel