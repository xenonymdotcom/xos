PLATFORM=$(shell uname -m)
ifeq "$(PLATFORM)" "x86_64"
  #$(info "using x64 cross compiler tools.")
else ifeq "$(PLATFORM)" "armv6l"
  #$(info "Arm V6 little endian Native tools.")
else ifeq "$(PLATFORM)" "armv7l"
  #$(info "Arm V7 little endian Native tools.")
else ifeq "$(PLATFORM)" "armv5tel"
  $(error "Arm V5TE little endian Native tools (sheeva plug) not supported.")
else 
  $(error "Unsupported Platform/Architecture $(PLATFORM)")
endif

include tools.$(PLATFORM)

# updated this if you need to add other paths to the include path
INCPATH=./src

INCFLAGS=$(foreach path,$(INCPATH),$(patsubst %,-I%,$(path)))
CPUFLAG=-mcpu=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard
MACHINEFLAGS=-marm $(CPUFLAG)
COMMONFLAGS=-Wall -O2 -fdata-sections -ffunction-sections -nostdinc -ffreestanding

ASFLAGS=--warn $(CPUFLAG) 
CFLAGS=--std=c99 $(COMMONFLAGS) $(MACHINEFLAGS) $(INCFLAGS)
#CXXFLAGS=-std=c++0x $(COMMONFLAGS) $(MACHINEFLAGS) $(INCFLAGS)
CXXFLAGS=-std=c++0x -fno-rtti -fno-exceptions $(COMMONFLAGS) $(MACHINEFLAGS) $(INCFLAGS)
LDFLAGS=-nostdlib -nostartfiles -gc-sections

RPIBASE=obj/platform/board/rpi
RPIFILE=mailbox framebuffer textutils uart
RPIOBJS=$(foreach file,$(RPIFILE),$(patsubst %,$(RPIBASE)/%.o,$(file)))

CPUBASE=obj/platform/arch/arm
CPUFILE=cpu
CPUOBJS=$(foreach file,$(CPUFILE),$(patsubst %,$(CPUBASE)/%.o,$(file)))

RTLBASE=obj/platform/rtl/startup
RTLFILE=cxxstartup cxxrtl
RTLOBJS=$(foreach file,$(RTLFILE),$(patsubst %,$(RTLBASE)/%.o,$(file)))

MEMBASE=obj/platform/rtl/memory
MEMFILE=cxxrtl_malloc
MEMOBJS=$(foreach file,$(MEMFILE),$(patsubst %,$(MEMBASE)/%.o,$(file)))

MAINOBJS=obj/main.o $(RTLOBJS) $(CPUOBJS) $(RPIOBJS) $(MEMOBJS)
OBJS=start.o $(MAINOBJS)

SRCFILES=start.s $(foreach file,$(MAINOBJS),$(patsubst obj/%.o,src/%.c,$(file)))

#$(info "SRCFILES: " $(SRCFILES))
#$(info "OBJS: " $(OBJS))

all: kernel.img

clean:
	rm -f $(OBJS) kernel.elf kernel.img

.PHONY: all clean

kernel.img: kernel.elf
	$(OBJCOPY) kernel.elf -O binary kernel.img

# Turn the ELF kernel into a binary file. This could be combined with the
# step above, but it's easier to disassemble the ELF version to see why
# something's not working
kernel.elf: linkscript $(OBJS)
	$(LD) -T linkscript $(LDFLAGS) -o kernel.elf $(OBJS)

# Build the assembler bit
start.o: start.s
	$(AS) $(ASFLAGS) -o start.o start.s

obj/%.o: src/%.s
	$(AS) $(ASFLAGS) -o $@ $<

obj/%.o: src/%.c
	$(GCC) $(CFLAGS) -c -o $@ $<

obj/%.o: src/%.cpp
	$(GXX) $(CXXFLAGS) -c -o $@ $<

obj/%.o: src/%.cc
	$(GXX) $(CXXFLAGS) -c -o $@ $<

