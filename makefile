CC = gcc
OBJS = main.o RLEList.o AsciiArtTool.o
EXEC = AsciiArtTool
COMP_FLAG = -std=c99 -Wall -pedantic-errors

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)
	
main.o: main.c RLEList.h AsciiArtTool.h
	$(CC) -c $(COMP_FLAG) $*.c
	
AsciiArtTool.o: AsciiArtTool.c RLEList.h AsciiArtTool.h
	$(CC) -c $(COMP_FLAG) $*.c

RLEList.o: RLEList.c RLEList.h
	$(CC) -c $(COMP_FLAG) $*.c
	
clean:
	rm -f $(OBJS) $(EXEC)
