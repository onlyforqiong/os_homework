.DEFAULT_GOAL = run

NAME = os_lab1
CXX    = g++
CFLAGS = -O2 -MMD 
LDFLAGS := -O2 $(LDFLAGS)

WORK_DIR  = $(shell pwd)
BUILD_DIR = $(WORK_DIR)/build
CSRCS = $(shell find $(abspath .) -name "*.c" -or -name "*.cc" -or -name "*.cpp")

BINARY   = $(BUILD_DIR)/$(NAME)


.PHONY: app clean run

app: $(BINARY)

$(BINARY):$(CSRCS)
	@echo $(CSRCS)
	@echo +x cc $<
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CFLAGS)  $< -o $(BINARY)

run : $(BINARY)
	@$<
clean : 
	rm -rf $(BUILD_DIR)


