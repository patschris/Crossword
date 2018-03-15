CC		= gcc
CFLAGS	= -g3 -Wall
EXEC 	= crossword
OBJS 	= main.o args.o crossword.o dictionary.o dictList.o solve.o slotList.o
SRCS 	= main.c args.c crossword.c dictionary.c dictList.c solve.c slotList.c
HEADS	= args.h crossword.h dictionary.h declarations.h dictList.h solve.h slotList.h

.PHONY : all
all: $(EXEC)

$(EXEC): $(OBJS) $(HEADS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

args.o: args.c
	$(CC) $(CFLAGS) -c args.c

crossword.o: crossword.c
	$(CC) $(CFLAGS) -c crossword.c
	
dictionary.o: dictionary.c
	$(CC) $(CFLAGS) -c dictionary.c

dictList.o: dictList.c
	$(CC) $(CFLAGS) -c dictList.c

solve.o: solve.c
	$(CC) $(CFLAGS) -c solve.c

slotList.o: slotList.c
	$(CC) $(CFLAGS) -c slotList.c


.PHONY: clean
clean:
	rm -f $(OBJS) $(EXEC)


.PHONY: count
count:
	wc $(SRCS) $(HEADS)