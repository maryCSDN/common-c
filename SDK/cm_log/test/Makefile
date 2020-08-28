CC              =gcc
SRCS            =$(wildcard ./*.c)
OBJS            =$(SRCS:.c=.o)
BIN             =test
LINK_LOG        =../src
LINK_SRCS       =$(wildcard $(LINK_LOG)/*.c)
LINK_OBJS       =$(LINK_SRCS:.c=.o)

CFLAGS          +=-g -Wall #-I$(LINK_LOG)/include
#LDFLAGS         +=-L$(LINK_LOG)

compile: clean $(BIN)

$(BIN): $(OBJS) $(LINK_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -lwsock32
# .c -> .o 的编译规则
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	@rm $(OBJS) $(BIN) -f