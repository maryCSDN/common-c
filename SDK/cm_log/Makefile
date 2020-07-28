CC				= 	gcc
MY_COMPLE_DIR	=	./comple/
MY_INCLUDE_DIR	=	./include/
MY_BIN_DIR		=	$(MY_COMPLE_DIR)bin/
MY_LIB_DIR		=	$(MY_COMPLE_DIR)lib/
MY_BIN			=   $(MY_BIN_DIR)cmlog_server
MY_LIB			=	$(MY_LIB_DIR)libcmlog.a	
MY_SRCS_DIR		=	./src/
MY_SRCS_BIN		=	$(wildcard $(MY_SRCS_DIR)*.c)	
MY_SRCS_LIB		=	$(wildcard $(MY_SRCS_DIR)include/*.c)	
MY_OBJS_BIN 	=	$(MY_SRCS_BIN:.c=.o)
MY_OBJS_LIB		=	$(MY_SRCS_LIB:.c=.o)

# -I$(INCLUDE_PATH) 引入自定义的头文件
# -g：生成调试信息
# Wall：输出全部的告警信息
CFLAGS  	   += 	-g -Wall -I$(MY_INCLUDE_DIR) -L$(MY_LIB_DIR)

compile:pre $(MY_LIB) $(MY_BIN) clean
	@echo ##cpmple cmlog success

# load: $(MY_BIN) $(MY_BIN)
# 	cp -rf $(INCLUDE_DIR) $(INC_SAVE_DIR)
# 	cp -f $(LIB)* $(LIB_SAVE_DIR)
# 	cp -f $(BIN)* $(BIN_SAVE_DIR)
pre:
	@echo ##start build cmlog

$(MY_LIB): $(MY_OBJS_LIB)
	@ar rc $@ $^
	@echo ##generate cmlog static lib

$(MY_BIN): $(MY_OBJS_BIN)
	$(CC) $(CFLAGS) -o $@ $^ -lwsock32
	@echo ##generate cmlog server bin

# .c -> .o 的编译规则
%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@ -lwsock32 

clean:
	@rm  $(MY_OBJS_LIB) $(MY_OBJS_BIN) -f
	@echo ##clean comple files

clean_all:clean
	@rm 	$(MY_LIB) $(MY_BIN) -f
	@echo ##clean lib and bin file
	
