ASM=nasm
CC=gcc
LD=ld
RM=rm
ASMFLAGS=-f elf64
.PHONY: clean all run
all: main
run: clean all
clean:
	$(RM) *.o
main: main.o dict.o lib.o
	$(LD) -o $@ $^
%.o: %.asm
	$(ASM) $(ASMFLAGS) -o $@ $<
dict.o: dict.asm lib.inc
	$(ASM) $(ASMFLAGS) -o $@ $<
main.o: main.asm colon.inc lib.inc dict.inc words.inc
	$(ASM) $(ASMFLAGS) -o $@ $<
