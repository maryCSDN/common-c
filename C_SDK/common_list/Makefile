SRC_PATH 		= 	./src
TEST_PATH		=	./test
SRCS	 		+= 	$(wildcard $(SRC_PATH)/*.c)
SRCS	 		+= 	$(wildcard $(TEST_PATH)/*.c)
OBJS 			=	$(SRCS:.c=.o)
BIN				=	test	#目标文件
# -I$(INCLUDE_PATH) 引入自定义的头文件
# -g：生成调试信息
# Wall：输出全部的告警信息
CFLAGS  		+= -g -Wall -I$(SRC_PATH)

build: clean $(BIN) _cl

$(BIN) : $(OBJS)
	gcc $(CFLAGS) -o $@ $^

# .c -> .o 的编译规则
%.o:%.c
	gcc $(CFLAGS) -c $< -o $@

_cl:
	rm $(SRC_PATH)/*.o $(TEST_PATH)/*.o -rf

clean:
	rm $(SRC_PATH)/*.o $(TEST_PATH)/*.o \
	test.exe -rf