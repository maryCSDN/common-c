#当前模块自定义
SRC_PATH             =src
SRCS                 =$(wildcard $(SRC_PATH)/*.c)
OBJS                 =$(SRCS:.c=.o)
# 在SDK build库目录下生成的cmcontainer的库文件
LIB                  =$(_CMLIBS)/libcmcontainer.a


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
	@$(_CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

### 上半部分为准备， 下半部分为方法

# 构建cm_log
build:pre compile 
	@echo "build cmcontainer successful"

# 前拷贝动作， 避免因拷贝时序导致的编译问题
pre:
	@cp -f $(SRC_PATH)/include/* $(_CMINCLUDES) 

# 编译cm_log
compile:$(LIB) clear
	@echo "Compile cmcontainer successful"

$(LIB): $(OBJS)
	@echo "Generate cmcontainer static library"
	@ar rc $@ $^ 


# 清除编译过程生成项 （提交代码前必须执行此命令）
clean: clear
	@(cd $(TEST_PATH) && $(MAKE) clean) || exit 1

clear:
	@rm -f $(OBJS) $(SRV_OBJS)


