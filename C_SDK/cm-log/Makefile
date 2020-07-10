CC				= 	gcc
INCLUDE_DIR 	=	./include/
BIN_SAVE_DIR	=	../cmsdk/bin/
LIB_SAVE_DIR	=	../cmsdk/lib/
INC_SAVE_DIR	=	../cmsdk/include/
SRCS_LIB		+= 	$(wildcard ./src/*.c)
SRCS_BIN	   	+=  $(wildcard ./src/*.c ./src/bin/*.c)
OBJS_LIB 		=	$(SRCS_LIB:.c=.o)
OBJS_BIN 		=	$(SRCS_BIN:.c=.o)
BIN 			= 	./cmlog
LIB				=   ./libcmlog.a

# -I$(INCLUDE_PATH) 引入自定义的头文件
# -g：生成调试信息
# Wall：输出全部的告警信息
CFLAGS  	   += 	-g -Wall -I$(INCLUDE_DIR)

build:  $(BIN) $(LIB) install

install: $(LIB) $(BIN)
	cp -f $(INCLUDE_DIR)*.h $(INC_SAVE_DIR)
	cp -f $(LIB)* $(LIB_SAVE_DIR)
	cp -f $(BIN)* $(BIN_SAVE_DIR)

$(LIB): $(OBJS_LIB)
	ar rc $@ $^

$(BIN): $(OBJS_BIN)
	$(CC) $(CFLAGS) -o $@ $^ -lwsock32 -static-libgcc

# .c -> .o 的编译规则
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ 


#_cl:
#	rm $(SRC_DIR)/*.o  $(SRC_DIR)/bin/*.o -rf

#clean:
#	rm  $(LIB_DIR) $(BIN_DIR) $(SRC_DIR)/*.o  $(SRC_DIR)/bin/*.o -rf