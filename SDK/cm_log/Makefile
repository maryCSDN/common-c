CC                   =gcc
MY_COMPLE_DIR        =./compile/
MY_INCLUDE_DIR       =./include/
MY_BIN_DIR           =$(MY_COMPLE_DIR)bin/
MY_LIB_DIR           =$(MY_COMPLE_DIR)lib/
MY_BIN               =$(MY_BIN_DIR)cmlog_server
MY_LIB               =$(MY_LIB_DIR)libcmlog.a
MY_SRCS_DIR          =./src/
MY_SRCS_BIN          =$(wildcard $(MY_SRCS_DIR)*.c)	
MY_SRCS_LIB          =$(wildcard $(MY_SRCS_DIR)include/*.c)	
MY_OBJS_BIN          =$(MY_SRCS_BIN:.c=.o)
MY_OBJS_LIB          =$(MY_SRCS_LIB:.c=.o)

#TEST 
MY_TEST_DIR          =./test/

# -I$(INCLUDE_PATH) 引入自定义的头文件
# -g：生成调试信息
# Wall：输出全部的告警信息
CFLAGS               +=-g -Wall -I$(MY_INCLUDE_DIR) -L$(MY_LIB_DIR)

compile:pre check_dir $(MY_LIB) $(MY_BIN) clean
	@echo "##cpmple cmlog success"

pre:
	@echo "##start build cmlog"

check_dir:
	mkdir -p $(MY_COMPLE_DIR)
	mkdir -p $(MY_INCLUDE_DIR)
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

# 提交代码前执行make build (清除编译生成项，只提交源码)
build:clean_all test_clean
	@echo "##build cmlog succes"

clean:
	rm  $(MY_OBJS_LIB) $(MY_OBJS_BIN) -f
	@echo "##clean comple files"

clean_all:clean
	rm $(MY_LIB)* $(MY_BIN)* -f
	@echo "##clean lib and bin file"

test_clean:
	@echo "##clean test compile file"
	(cd $(MY_TEST_DIR) && $(MAKE) clean) || exit 1
	@echo "##clean test compile file success"
	