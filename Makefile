CC=arm-none-eabi-gcc
CFLAGS=-mcpu=cortex-m3 -mthumb -Wall -Wextra -O0

all: firmware.bin

firmware.elf: main.o startup.o
	$(CC) -T link.ld -nostdlib $^ -o $@

firmware.bin: firmware.elf
	arm-none-eabi-objcopy -O binary $< $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.elf *.bin
