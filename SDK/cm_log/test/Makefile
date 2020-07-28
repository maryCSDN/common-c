CC				= 	gcc
INCLUDE			=	../include/
LIB				=	../comple/lib/
SRCS			=	$(wildcard ./*.c)	
OBJS			=	$(SRCS:.c=.o)
EXE				= 	test
CFLAGS  	   	+= 	-g -Wall -I$(INCLUDE) 
LDFLAGS			+=	-L$(LIB)

build: clean $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -lcmlog -lwsock32
# .c -> .o 的编译规则
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm $(OBJS) $(EXE) -f