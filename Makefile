CC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m4 -mthumb -nostdlib -ffreestanding -O0 -g -Wall -Wextra -Werror
SOURCES = startup.c main.c
TARGET = firmware.elf

all: $(TARGET)

$(TARGET): $(SOURCES) linker.ld Makefile
	$(CC) $(CFLAGS) -T linker.ld $(SOURCES) -o $(TARGET)

flash: $(TARGET)
	openocd -f board/stm32f4discovery.cfg -c "program $(TARGET) verify reset exit"

clean:
	rm -f $(TARGET)