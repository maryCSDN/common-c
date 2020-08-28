#当前模块自定义
SRC_PATH             =src
SRCS                 =$(wildcard $(SRC_PATH)/*.c)
OBJS                 =$(SRCS:.c=.o)
# 在SDK build库目录下生成的cmlog的库文件
LIB                  =$(_CMLIBS)/libcmlog.a

# have service control
SRV_SRC_PATH         =service
SRV_SRCS             =$(wildcard $(SRV_SRC_PATH)/*.c)
SRV_OBJS             =$(SRV_SRCS:.c=.o)
# 在SDK build库目录下生成cmlog server的可执行文件
BIN                  =$(_CMBINS)/cmlogsrv


# Unit test 
TEST_PATH            =test


# $@:目标文件 $^:全部展示 $<:一个一个一次展示
# -I$(INCLUDE_PATH) 引入自定义的头文件
# -g：生成调试信息
# Wall：输出全部的告警信息
CFLAGS               +=-g -Wall -I$(_CMINCLUDES)
LDFLAGS              +=-L$(_CMLIBS)

# .c -> .o 的编译规则
%.o:%.c
	@$(_CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@ -static

### 上半部分为准备， 下半部分为方法

# 构建cm_log
build:pre compile 
	@echo "build cmlog successful"

# 前拷贝动作， 避免因拷贝时序导致的编译问题
pre:
	@cp -f $(SRC_PATH)/include/* $(_CMINCLUDES) 

# 编译cm_log
compile:$(LIB) $(BIN) clear
	@echo "Compile cmlog successful"

$(LIB): $(OBJS)
	@echo "Generate cmlog static library"
	@ar rc $@ $^ 

ifeq ($(OS), Windows_NT)
$(BIN): $(SRV_OBJS)
	@echo "Generate cmlog server bin, [Windows System]"
	@$(_CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -lcmlog -lwsock32
else
$(BIN): $(SRV_OBJS)
	@echo "Generate cmlog server bin, [like unix]"
	@$(_CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -lcmlog
endif


# 清除编译过程生成项 （提交代码前必须执行此命令）
clean: clear
	@(cd $(TEST_PATH) && $(MAKE) clean) || exit 1

clear:
	@rm -f $(OBJS) $(SRV_OBJS)


