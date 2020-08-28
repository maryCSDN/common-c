CC              =gcc
SRCS            =$(wildcard ./*.c)
OBJS            =$(SRCS:.c=.o)
BIN             =test


LINK            =../../../build
CFLAGS          +=-g -Wall -I$(LINK)/includes
LDFLAGS         +=-L$(LINK)/libs

compile: clean $(BIN)

$(BIN): $(OBJS) $(LINK_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -lcmlog
# .c -> .o 的编译规则
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	@rm $(OBJS) $(BIN) -f