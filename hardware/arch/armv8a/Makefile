
CC = gcc
LD = ld 

OBJDUMP = objdump
OBJCOPY = objcopy 

DEFINES = 
#DEFINES += -DCONFIG_GIC_SINGLE_SECURITY_STATE 
#DEFINES += -DCONFIG_ARMV8_A_NS

# TARGET = --target=aarch64-unknown-none-eabi 
TARGET =
CFLAGS = ${TARGET} -Wall \
	-I./include  \
	-I../../../components/libfdt/include  \
	-I../../../components/libfdt/include/libfdt  \
	-I../../../components/libc/include  \
	-I../../../hardware/arch/armv8a/include  \
	-I../../../kernel/rhino/include  \
	-I../../../hardware/board/qemu_virt/config  \
	-Wl,--script=ldscript.arm64  \
	-nostartfiles   \
	-nodefaultlibs  \
	-nostdlib  -nostdinc \
	-mgeneral-regs-only ${DEFINES}   # 需要支持 aarch64 SIMD，然后再打开这个选项


LDFLAGS = --script=ldscript.arm64

OBJS = start.o exception.o port.o \
	entry-common.o _uart.o lostart.o \
	gtimer.o processor.o asm-offset.o gicv3.o

LIBC_PATH = ../../../components/libc/

OBJS += memchr.o memcmp.o memcpy.o memset.o  \
	strlen.o strnlen.o strtoul.o strchr.o strrchr.o \
	printf.o strcmp.o  

LIBFDT_PATH = ../../../components/libfdt/

OBJS += fdt_addresses.o fdt_empty_tree.o  \
	fdt_overlay.o fdt_ro.o fdt_rw.o fdt_strerror.o \
	fdt_sw.o fdt_wip.o fdt.o

KERNEL_PATH = ../../../kernel/rhino

K_OBJS = k_atomic.o k_buf_queue.o k_cfs.o k_dyn_mem_proc.o k_err.o  \
	k_event.o k_idle.o k_mm.o k_mm_blk.o  \
	k_mutex.o k_obj.o k_pend.o k_queue.o k_rbtree.o  \
	k_ringbuf.o k_sched.o k_sem.o k_spin_lock.o k_stats.o  \
	k_sys.o k_task_sem.o k_task.o k_tick.o k_time.o  \
	k_timer.o k_workqueue.o k_mm_debug.o

BOARD_PATH = ../../../hardware/board/qemu_virt

B_OBJS = k_config.o 

all:

board:
	${CC} ${CFLAGS} -c -o k_config.o ${BOARD_PATH}/config/k_config.c 

kernel:
	${CC} ${CFLAGS} -c -o k_atomic.o ${KERNEL_PATH}/k_atomic.c 
	${CC} ${CFLAGS} -c -o k_buf_queue.o	${KERNEL_PATH}/k_buf_queue.c  
	${CC} ${CFLAGS} -c -o k_cfs.o	${KERNEL_PATH}/k_cfs.c  
	${CC} ${CFLAGS} -c -o k_dyn_mem_proc.o	${KERNEL_PATH}/k_dyn_mem_proc.c 
	${CC} ${CFLAGS} -c -o k_err.o	${KERNEL_PATH}/k_err.c 
	${CC} ${CFLAGS} -c -o k_event.o	${KERNEL_PATH}/k_event.c  
	${CC} ${CFLAGS} -c -o k_idle.o	${KERNEL_PATH}/k_idle.c  
	${CC} ${CFLAGS} -c -o k_mm_blk.o	${KERNEL_PATH}/k_mm_blk.c  
	${CC} ${CFLAGS} -c -o k_mm_debug.o	${KERNEL_PATH}/k_mm_debug.c  
	${CC} ${CFLAGS} -c -o k_mm.o	${KERNEL_PATH}/k_mm.c  
	${CC} ${CFLAGS} -c -o k_mutex.o	${KERNEL_PATH}/k_mutex.c  
	${CC} ${CFLAGS} -c -o k_obj.o	${KERNEL_PATH}/k_obj.c 
	${CC} ${CFLAGS} -c -o k_pend.o	${KERNEL_PATH}/k_pend.c 
	${CC} ${CFLAGS} -c -o k_queue.o	${KERNEL_PATH}/k_queue.c 
	${CC} ${CFLAGS} -c -o k_rbtree.o	${KERNEL_PATH}/k_rbtree.c
	${CC} ${CFLAGS} -c -o k_ringbuf.o	${KERNEL_PATH}/k_ringbuf.c 
	${CC} ${CFLAGS} -c -o k_sched.o	${KERNEL_PATH}/k_sched.c  
	${CC} ${CFLAGS} -c -o k_sem.o	${KERNEL_PATH}/k_sem.c  
	${CC} ${CFLAGS} -c -o k_spin_lock.o	${KERNEL_PATH}/k_spin_lock.c  
	${CC} ${CFLAGS} -c -o k_stats.o	${KERNEL_PATH}/k_stats.c  
	${CC} ${CFLAGS} -c -o k_sys.o	${KERNEL_PATH}/k_sys.c  
	${CC} ${CFLAGS} -c -o k_task_sem.o	${KERNEL_PATH}/k_task_sem.c  
	${CC} ${CFLAGS} -c -o k_task.o	${KERNEL_PATH}/k_task.c  
	${CC} ${CFLAGS} -c -o k_tick.o	${KERNEL_PATH}/k_tick.c  
	${CC} ${CFLAGS} -c -o k_time.o	${KERNEL_PATH}/k_time.c  
	${CC} ${CFLAGS} -c -o k_timer.o	${KERNEL_PATH}/k_timer.c  
	${CC} ${CFLAGS} -c -o k_workqueue.o	${KERNEL_PATH}/k_workqueue.c 

libc:
	${CC} ${CFLAGS} -c -o memchr.o ${LIBC_PATH}string/memchr.c
	${CC} ${CFLAGS} -c -o memcpy.o ${LIBC_PATH}string/memcpy.c
	${CC} ${CFLAGS} -c -o memcmp.o ${LIBC_PATH}string/memcmp.c
	${CC} ${CFLAGS} -c -o memset.o ${LIBC_PATH}string/memset.c
	${CC} ${CFLAGS} -c -o strlen.o ${LIBC_PATH}string/strlen.c
	${CC} ${CFLAGS} -c -o strchr.o ${LIBC_PATH}string/strchr.c
	${CC} ${CFLAGS} -c -o strrchr.o ${LIBC_PATH}string/strrchr.c
	${CC} ${CFLAGS} -c -o strnlen.o ${LIBC_PATH}string/strnlen.c
	${CC} ${CFLAGS} -c -o strcmp.o ${LIBC_PATH}string/strcmp.c

	${CC} ${CFLAGS} -c -o strtoul.o ${LIBC_PATH}stdlib/strtoul.c

	${CC} ${CFLAGS} -c -o printf.o ${LIBC_PATH}libkernel/printf.c

libfdt:
	${CC} ${CFLAGS} -c -o fdt_addresses.o ${LIBFDT_PATH}fdt_addresses.c
	${CC} ${CFLAGS} -c -o fdt_empty_tree.o ${LIBFDT_PATH}fdt_empty_tree.c
	${CC} ${CFLAGS} -c -o fdt_overlay.o ${LIBFDT_PATH}fdt_overlay.c
	${CC} ${CFLAGS} -c -o fdt_ro.o ${LIBFDT_PATH}fdt_ro.c 
	${CC} ${CFLAGS} -c -o fdt_rw.o ${LIBFDT_PATH}fdt_rw.c 
	${CC} ${CFLAGS} -c -o fdt_strerror.o ${LIBFDT_PATH}fdt_strerror.c
	${CC} ${CFLAGS} -c -o fdt_sw.o ${LIBFDT_PATH}fdt_sw.c 
	${CC} ${CFLAGS} -c -o fdt_wip.o ${LIBFDT_PATH}fdt_wip.c 
	${CC} ${CFLAGS} -c -o fdt.o ${LIBFDT_PATH}fdt.c 

elf: libfdt libc kernel board
	${CC} ${CFLAGS} -c -o start.o start.S
	${CC} ${CFLAGS} -c -o exception.o exception.S 
	${CC} ${CFLAGS} -c -o port.o port.S 
	${CC} ${CFLAGS} -c -o entry-common.o entry-common.c 
	${CC} ${CFLAGS} -c -o _uart.o _uart.c 
	${CC} ${CFLAGS} -c -o lostart.o lostart.c
	${CC} ${CFLAGS} -c -o gtimer.o gtimer.c 
	${CC} ${CFLAGS} -c -o processor.o processor.c 
	${CC} ${CFLAGS} -c -o asm-offset.o asm-offset.c 
	${CC} ${CFLAGS} -c -o gicv3.o gicv3/gic.c 

#	${LD} ${LDFLAGS} -o aos.elf ${OBJS}
	${CC} ${CFLAGS} -o aos.elf ${OBJS} ${K_OBJS} ${B_OBJS}

all: elf
	${OBJCOPY} -O binary aos.elf aos.bin
	${OBJDUMP} -S aos.elf > aos.dis
	hexdump aos.bin > dump
	nm -n -S aos.elf > symbol.txt 

# virualization == EL2
# secure == EL3

QEMU_M_VIRTUAL =on
QEMU_M_SECURE =off

QEMU_MACHINE = virt,virtualization=${QEMU_M_VIRTUAL},secure=${QEMU_M_SECURE},gic-version=3
QEMU_MEMORY = 3G
QEMU_CPU = cortex-a72
QEMU_SMP = 1
QEMU_FLAGS =

get_dtb:
	qemu-system-aarch64 -M ${QEMU_MACHINE},dumpdtb=virt.dtb  \
		-m ${QEMU_MEMORY} \
		-cpu ${QEMU_CPU}  \
		-smp ${QEMU_SMP}  ${QEMU_FLAGS} \
		-nographic
	dtc -I dtb -O dts virt.dtb > virt.dts 

run_qemu: all
	@echo " "
	@echo " "
	@echo "start running on qemu ..."
	qemu-system-aarch64 -M ${QEMU_MACHINE} -m ${QEMU_MEMORY} \
		-cpu ${QEMU_CPU}  \
		-smp ${QEMU_SMP}  \
		-bios aos.bin ${QEMU_FLAGS} \
		-nographic

clean:
	@rm -f *.o *.elf *.dis *.bin  *.dtb *.dts dump symbol.txt 



