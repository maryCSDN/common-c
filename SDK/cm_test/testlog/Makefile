CC				= 	gcc
INCLUDE			=	../../cm-sdk/include/
LIB				=	../../cm-sdk/lib/
SRCS			=   $(wildcard ./src/*.c)
OBJS			=	$(SRCS:.c=.o)
EXE				= 	test
CFLAGS  	   	+= 	-g -Wall -I$(INCLUDE) 
LDFLAGS			+=	-L$(LIB)

build: clean $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -lcmlog
# .c -> .o 的编译规则
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm ./src/*.o $(EXE) -f