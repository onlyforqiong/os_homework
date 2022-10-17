.DEFAULT_GOAL = run
# this is for windows operating system
NAME = os_homework_2
CXX    = g++
CFLAGS = -O2 -MMD 
LDFLAGS := -O2 $(LDFLAGS)
FILE_NAME = os_homework_2
# FILE_NAME = difftest_os_lab1
WORK_DIR  = $(shell pwd)
BUILD_DIR = build
CSRCS = $(FILE_NAME).cpp #$(shell find $(abspath .) -name "$(FILE_NAME).c" -or -name "$(FILE_NAME).cc" -or -name "$(FILE_NAME).cpp")

BINARY   = $(BUILD_DIR)/$(NAME).exe


.PHONY: app clean run

app: $(BINARY)

$(BINARY):$(CSRCS)
	@echo $(CSRCS)
	@echo $(BUILD_DIR)
	@echo  +x cc $<
	-rd /S /Q $(BUILD_DIR)
	@mkdir  $(BUILD_DIR)
	-copy  thread.txt $(BUILD_DIR)
	$(CXX) $(CFLAGS)  $< -o $(BINARY)

run : $(BINARY)
	@$<
clean : 
	rd /S /Q $(BUILD_DIR)


