CC				= 	gcc
INCLUDE			=	../include/
LIB				=	../compile/lib/
SRCS			=	$(wildcard ./*.c)	
OBJS			=	$(SRCS:.c=.o)
EXE				= 	test
CFLAGS  	   	+= 	-g -Wall -I$(INCLUDE) 
LDFLAGS			+=	-L$(LIB)

compile: undo $(EXE)

$(EXE): $(OBJS)
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -lcmlog -lwsock32
# .c -> .o 的编译规则
%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@ 

undo:
	@rm $(OBJS) $(EXE)* -f