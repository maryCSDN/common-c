CC				= 	gcc
INCLUDE_DIR 	=	./include/
BIN_SAVE_DIR	=	../cm-sdk/bin/
LIB_SAVE_DIR	=	../cm-sdk/lib/
INC_SAVE_DIR	=	../cm-sdk/include/
SRCS_LIB		+= 	$(wildcard ./src/*.c)
SRCS_BIN	   	+=  $(wildcard ./src/*.c ./src/bin/*.c)
OBJS_LIB 		=	$(SRCS_LIB:.c=.o)
OBJS_BIN 		=	$(SRCS_BIN:.c=.o)
LIB				=   ./libcmlist.a

# -I$(INCLUDE_PATH) 引入自定义的头文件
# -g：生成调试信息
# Wall：输出全部的告警信息
CFLAGS  	   += 	-g -Wall -I$(INCLUDE_DIR) -I$(INC_SAVE_DIR) -L$(LIB)

build:  $(LIB) install

install: $(LIB)
	cp -f $(INCLUDE_DIR)*.h $(INC_SAVE_DIR)
	cp -f $(LIB)* $(LIB_SAVE_DIR)

$(LIB): $(OBJS_LIB)
	ar rc $@ $^ 

# .c -> .o 的编译规则
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@  -lcmlog -lwsock32 -static-libgcc

clean:
	rm  $(LIB) ./src/*.o   -f