PLATFORM=$(shell uname -m)
ifeq "$(PLATFORM)" "x86_64"
  $(info "using x64 cross compiler tools.")
else ifeq "$(PLATFORM)" "armv6l"
  $(info "Arm V6 little endian Native tools.")
else ifeq "$(PLATFORM)" "armv5tel"
  $(error "Arm V5TE little endian Native tools (sheeva plug) not supported.")
else 
  $(error "Unsupported Platform/Architecture $(PLATFORM)")
endif

include tools.$(PLATFORM)

ASFLAGS=--warn -mcpu=arm1176jzf-s
CFLAGS=-Wall --std=c99 -O2 -fdata-sections -ffunction-sections -nostdinc -ffreestanding -marm -mcpu=arm1176jzf-s -I./src
CXXFLAGS=-Wall -std=c++0x -O2 -fdata-sections -ffunction-sections -nostdinc -ffreestanding -marm -mcpu=arm1176jzf-s -I./src
MAINOBJS=obj/platform/board/rpi/mailbox.o obj/platform/board/rpi/framebuffer.o obj/platform/board/rpi/textutils.o obj/main.o
OBJS=start.o obj/platform/arch/arm/cpu.o $(MAINOBJS)
SRCFILES=start.s src/platform/arch/arm/cpu.s $(foreach file,$(MAINOBJS),$(patsubst obj/%.o,src/%.c,$(file)))

$(info "SRCFILES: " $(SRCFILES))
$(info "OBJS: " $(OBJS))

all: kernel.img

clean:
	rm -f *.o kernel.elf kernel.img

.PHONY: all clean

# Turn the ELF kernel into a binary file. This could be combined with the
# step above, but it's easier to disassemble the ELF version to see why
# something's not working
kernel.img: kernel.elf
	$(OBJCOPY) kernel.elf -O binary kernel.img

kernel.elf: linkscript $(OBJS)
	$(LD) -T linkscript -nostdlib -nostartfiles -gc-sections -o kernel.elf $(OBJS)

# Build the assembler bit
start.o: start.s
	$(AS) $(ASOPT) -o start.o start.s

obj/%.o: src/%.s
	$(AS) $(ASFLAGS) -o $@ $<

obj/%.o: src/%.c
	$(GCC) $(CFLAGS) -c -o $@ $<

obj/%.o: src/%.cpp
	$(GXX) $(CXXFLAGS) -c -o $@ $<

obj/%.o: src/%.cc
	$(GXX) $(CXXFLAGS) -c -o $@ $<

