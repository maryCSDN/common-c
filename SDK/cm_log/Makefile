#当前模块自定义
CC                   =gcc
MY_INCLUDE_DIR       =./include/
MY_SRCS_DIR          =./src/
MY_SRCS_BIN          =$(wildcard $(MY_SRCS_DIR)*.c)	
MY_SRCS_LIB          =$(wildcard $(MY_SRCS_DIR)include/*.c)	
MY_OBJS_BIN          =$(MY_SRCS_BIN:.c=.o)
MY_OBJS_LIB          =$(MY_SRCS_LIB:.c=.o)

#generate compile file
MY_COMPLE_DIR        =./compile/
MY_BIN_DIR           =$(MY_COMPLE_DIR)bin/
MY_LIB_DIR           =$(MY_COMPLE_DIR)lib/
MY_BIN               =$(MY_BIN_DIR)cmlog
MY_LIB               =$(MY_LIB_DIR)libcmlog.a

#构建外部库定义（build）
BUILD                =../../build/cmlog/

#TEST 
MY_TEST_DIR          =./test/

# -I$(INCLUDE_PATH) 引入自定义的头文件
# -g：生成调试信息
# Wall：输出全部的告警信息
CFLAGS               +=-g -Wall -I$(MY_INCLUDE_DIR)

#compile是单编译入口，可以直接调用
compile:pre check_dir $(MY_LIB) $(MY_BIN) clean_obj
	@echo "***compile cmlog success***"

pre:
	@echo "***compile cmlog***"

check_dir:
	@mkdir -p $(MY_COMPLE_DIR);
	@mkdir -p $(MY_BIN_DIR);
	@mkdir -p $(MY_LIB_DIR);

$(MY_LIB): $(MY_OBJS_LIB)
	@ar rc $@ $^
	@echo "***generate cmlog static library***"

$(MY_BIN): $(MY_OBJS_BIN)
	@$(CC) $(CFLAGS) -o $@ $^ -lwsock32
	@echo "***generate cmlog server bin***"

# .c -> .o 的编译规则
%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@

#build 由上层Makefile调用，包含编译过程，以及拷贝头文件、静态库到指定目录
build:compile
	@mkdir -p $(BUILD)
	@cp -rf $(MY_INCLUDE_DIR) $(BUILD)
	@cp -rf $(MY_BIN_DIR) $(BUILD)
	@cp -rf $(MY_LIB_DIR) $(BUILD)


# 提交代码前执行make undo (清除编译生成项，只提交源码)
undo: clean clean_test
	@rm -rf $(MY_COMPLE_DIR)

clean_obj:
	@rm  $(MY_OBJS_LIB) $(MY_OBJS_BIN) -f

clean: clean_obj
	@rm $(MY_LIB)* $(MY_BIN)* -f

clean_test:
	@(cd $(MY_TEST_DIR) && $(MAKE) undo) || exit 1
