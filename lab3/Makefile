.DEFAULT_GOAL = run

NAME = os_lab3
CXX    = g++
CFLAGS = -O2 -MMD 
LDFLAGS := -O2 $(LDFLAGS)
FILE_NAME = os_lab3
# FILE_NAME = difftest_os_lab1
WORK_DIR  = $(shell pwd)
BUILD_DIR = $(WORK_DIR)/build
CSRCS = $(shell find $(abspath .) -name "$(FILE_NAME).c" -or -name "$(FILE_NAME).cc" -or -name "$(FILE_NAME).cpp")

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


