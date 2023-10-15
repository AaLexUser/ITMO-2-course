CC=gcc
AS=nasm
ASFLAGS=-felf64
LDFLAGS=-lm -no-pie

RM = rm -rf
MKDIR = mkdir -p

TARGET=image-sepia
SOLDIR = solution
SRCDIR = $(SOLDIR)/src
INCDIR = $(SOLDIR)/include
BUILD = build
OBJDIR = $(BUILD)/obj

$(BUILD):
	$(MKDIR) $@
$(OBJDIR):
	$(MKDIR) $@

CFLAGS=-g -no-pie -O2 -I $(SOLDIR)/include

C_SOURCES = $(wildcard $(SRCDIR)/*.c)
# List of object files
C_OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(C_SOURCES))
ASM_SOURCES += $(wildcard $(SRCDIR)/*.asm)
ASM_OBJECTS=$(patsubst $(SRCDIR)/%.asm,$(OBJDIR)/%.o,$(ASM_SOURCES))

.PHONY: all clean print-objects
print-source:
	@echo $(C_SOURCES)
	@echo $(ASM_SOURCES)
print-objects:
	@echo "OBJECTS: $(OBJECTS)"
all: $(TARGET)

$(TARGET): $(C_OBJECTS) $(ASM_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.asm | $(OBJDIR)
	$(AS) $(ASFLAGS) $< -o $@

clean:
	$(RM) $(C_OBJECTS) $(ASM_OBJECTS) $(TARGET)