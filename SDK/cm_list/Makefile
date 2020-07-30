#define
CC                   = gcc
MY_INCLUDE_DIR       = ./include/
MY_SRCS_DIR          = ./src/
MY_SRCS_LIB          = $(wildcard $(MY_SRCS_DIR)include/*.c)	
MY_OBJS_LIB          = $(MY_SRCS_LIB:.c=.o)

#generate compile file
MY_COMPLE_DIR        = ./compile/
MY_BIN_DIR           = $(MY_COMPLE_DIR)bin/
MY_LIB_DIR           = $(MY_COMPLE_DIR)lib/
MY_LIB               = $(MY_LIB_DIR)libcmlist.a

#构建外部库定义（build）
COMPILE              =../../compiles/cmlist/
INCLUDE              =$(COMPILE)include/
LIB                  =$(COMPILE)lib/
BIN                  =$(COMPILE)bin/

#resources

#TEST 
MY_TEST_DIR          =./test/

# -I$(INCLUDE_PATH) 引入自定义的头文件
# -g：生成调试信息
# Wall：输出全部的告警信息
CFLAGS               +=-g -Wall -I$(MY_INCLUDE_DIR) 
#LDFLAGS              +=-L$(LIB)

compile:pre check_dir $(MY_LIB) $(MY_BIN) clean
	@echo "##cpmple cmlog success"

pre:
	@echo "##start build cmlog"

check_dir:
mkdir -p $(MY_COMPLE_DIR);
mkdir -p $(MY_INCLUDE_DIR);
mkdir -p $(MY_BIN_DIR)
mkdir -p $(MY_LIB_DIR)

$(MY_LIB): $(MY_OBJS_LIB)
	ar rc $@ $^
	@echo "##generate cmlog static lib"

$(MY_BIN): $(MY_OBJS_BIN)
	$(CC) $(CFLAGS) -o $@ $^ -lwsock32
	@echo "##generate cmlog server bin"

# .c -> .o 的编译规则
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ -lwsock32 

#build 由上层Makefile调用，包含编译过程，以及拷贝头文件、静态库到指定目录
build:compile
	mkdir -p $(BUILD)
	mkdir -p $(INCLUDE)
	mkdir -p $(LIB)
	mkdir -p $(BIN)
	cp -rf $(MY_INCLUDE_DIR) $(INCLUDE)
	cp -rf $(MY_BIN_DIR) $(BIN)
	cp -rf $(MY_LIB_DIR) $(LIB)


# 提交代码前执行make undo (清除编译生成项，只提交源码)
undo: clean clean_test
	rm -rf $(MY_COMPLE_DIR)
	@echo "##clean cmlog compile file"

clean:
	@rm  $(MY_OBJS_LIB) $(MY_OBJS_BIN) \
		$(MY_LIB)* $(MY_BIN)* -f

clean_test:
	@(cd $(MY_TEST_DIR) && $(MAKE) undo) || exit 1