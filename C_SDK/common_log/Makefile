CC				= 	gcc
SRC_DIR			=   ./src				
INCLUDE_DIR 	=	./include
BIN_DIR			=   ./bin
LIB_DIR			= 	./lib
BIN 			= 	$(BIN_DIR)/cmlog
LIB				=   $(LIB_DIR)/libcmlog.a
LIB_FILE		= 	$(wildcard $(SRC_DIR)/*.c)
BIN_FILE	   +=   $(LIB_FILE)
BIN_FILE	   +=	$(wildcard $(SRC_DIR)/bin/*.c)
LIB_OBJS_FILE 	=	$(LIB_FILE:.c=.o)
BIN_OBJS_FILE 	=	$(BIN_FILE:.c=.o)

# -I$(INCLUDE_PATH) 引入自定义的头文件
# -g：生成调试信息
# Wall：输出全部的告警信息
CFLAGS  	   += 	-g -Wall -I$(INCLUDE_DIR)

build:	$(LIB) $(BIN)

$(LIB): $(LIB_OBJS_FILE)
	mkdir $(LIB_DIR)
	ar rc $@ $^

$(BIN): $(BIN_OBJS_FILE)
	mkdir $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ -lwsock32 -static-libgcc


# .c -> .o 的编译规则
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

#_cl:
#	rm $(SRC_DIR)/*.o  $(SRC_DIR)/bin/*.o -rf

#clean:
#	rm  $(LIB_DIR) $(BIN_DIR) $(SRC_DIR)/*.o  $(SRC_DIR)/bin/*.o -rf