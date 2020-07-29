CC              = gcc
INCLUDE         =../include/
LIB             =../compile/lib/
SRCS            =$(wildcard ./*.c)	
OBJS            =$(SRCS:.c=.o)
EXE             =test

RES_INCLUDE     =../../cm_log/include/
RES_LIB         =../../cm_log/compile/lib/

CFLAGS          +=-g -Wall -I$(INCLUDE) -I$(RES_INCLUDE)
LDFLAGS         +=-L$(LIB) -L$(RES_LIB)

compile: undo $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -lcmlog -lwsock32 -lcmlist

# .c -> .o 的编译规则
%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@ 

undo:
	@rm $(OBJS) $(EXE)* -f