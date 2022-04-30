CC = gcc
OBJS = tool/main.o RLEList.o tool/AsciiArtTool.o
EXEC = AsciiArtTool
DEBUG_FLAG = -g
RLELIST_H = /home/mtm/public/2122b/ex1/RLEList.h
COMP_FLAG = -std=c99 -I/home/mtm/public/2122b/ex1 -Itool -Wall -pedantic-errors -Werror

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(COMP_FLAG) $(DEBUG_FLAG) -o $(EXEC)
	
tool/main.o: tool/main.c $(RLELIST_H) tool/AsciiArtTool.h
	$(CC) -c $(COMP_FLAG) $*.c -o tool/main.o
	
tool/AsciiArtTool.o: tool/AsciiArtTool.c $(RLELIST_H) tool/AsciiArtTool.h
	$(CC) -c $(COMP_FLAG) $*.c -o tool/AsciiArtTool.o

RLEList.o: RLEList.c $(RLELIST_H)
	$(CC) -c $(COMP_FLAG) $*.c
	
clean:
	rm -f $(OBJS) $(EXEC)
