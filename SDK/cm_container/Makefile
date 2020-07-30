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
MY_LIB               = $(MY_LIB_DIR)libcmcontainer.a

#构建外部库定义（build）
BUILD                = ../../build/cmcontainer/

#resources
RES_INCLUDE          = ../cm_log/include/
#RES_LIB              = ../cm_log/compile/lib/

#TEST 
MY_TEST_DIR          =./test/

# -I$(INCLUDE_PATH) 引入自定义的头文件
# -g：生成调试信息
# Wall：输出全部的告警信息
CFLAGS               +=-g -Wall -I$(MY_INCLUDE_DIR) -I$(RES_INCLUDE)
#LDFLAGS              +=-L$(RES_LIB)

compile:pre check_dir $(MY_LIB) $(MY_BIN) clean_obj
	@echo "***cpmple cmcontainer success***"

pre:
	@echo "***compile cmcontainer***"

check_dir:
	@mkdir -p $(MY_COMPLE_DIR);
	@mkdir -p $(MY_INCLUDE_DIR);
	@mkdir -p $(MY_BIN_DIR)
	@mkdir -p $(MY_LIB_DIR)

$(MY_LIB): $(MY_OBJS_LIB)
	@ar rc $@ $^
	@echo "***generate cmcontainer static library***"

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
	@rm  $(MY_OBJS_LIB) -f

clean: clean_obj
	@rm $(MY_LIB)* -f

clean_test:
	@(cd $(MY_TEST_DIR) && $(MAKE) undo) || exit 1