#当前模块自定义
CC                   =gcc
SRC_PATH             =src
SRCS                 =$(wildcard $(SRC_PATH)/*.c)
OBJS                 =$(SRCS:.c=.o)
LIB                  =libcmlog.a

# have service control
SRV_SRC_PATH         =service
SRV_SRCS             =$(wildcard $(SRV_SRC_PATH)/*.c)
SRV_OBJS             =$(SRV_SRCS:.c=.o)
SRV_BIN              =$(SRV_SRC_PATH)/bin/cmlogsrv


# Unit test 
TEST_PATH            =test


# $@:目标文件 $^:全部展示 $<:一个一个一次展示
# -I$(INCLUDE_PATH) 引入自定义的头文件
# -g：生成调试信息
# Wall：输出全部的告警信息
CFLAGS               +=-g -Wall
# LDFLAGS

# .c -> .o 的编译规则
%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@ -static

### 上半部分为准备， 下半部分为方法

# 编译cm_log
compile:$(LIB) $(SRV_BIN) clear
	@echo "Compile cmlog successful"

$(LIB): $(OBJS)
	@echo "Generate cmlog static library"
	@ar rc $@ $^ 

$(SRV_BIN): $(SRV_OBJS)
	@echo "Generate cmlog server bin"
	@$(CC) $(CFLAGS) -o $@ $^


# 清除编译过程生成项 （提交代码前必须执行此命令）
clean: clear
	@rm -f $(SRV_BIN) $(LIB)
	@(cd $(TEST_PATH) && $(MAKE) clean) || exit 1

clear:
	@rm -f $(OBJS) $(SRV_OBJS)


