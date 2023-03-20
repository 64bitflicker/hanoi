NAME = hanoi
INC_DIR += ./include
BUILD_DIR ?= ./build
OBJ_DIR ?= $(BUILD_DIR)/obj
BINARY ?= $(BUILD_DIR)/$(NAME)

# Compilation flags
CC = gcc
LD = gcc
INCLUDES  = $(addprefix -I, $(INC_DIR))
CFLAGS   += -O2 -MMD -Wall -Werror -ggdb $(INCLUDES)

# Files to be compiled
SRCS = $(shell find src/ -name "*.c")
OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

# Compilation patterns
$(OBJ_DIR)/%.o: src/%.c
	@echo + [CC] $<
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<

# Depencies
-include $(OBJS:.o=.d)

.DEFAULT_GOAL = exe
.PHONY: exe run gdb clean
exe:$(BINARY)

# Command to execute NEMU
ARGS = 3
RUN_EXEC := $(BINARY) $(ARGS)

$(BINARY): $(OBJS)
	@echo + [LD] $@
	@$(LD) -O2 -o $@ $^

run: $(BINARY)
	@$(RUN_EXEC)

gdb: $(BINARY)
	gdb --args $(BINARY) $(ARGS)

clean: 
	rm -rf $(BUILD_DIR)
