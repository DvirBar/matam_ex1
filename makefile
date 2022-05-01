CC = gcc
MAIN = tool/main
RLELIST = RLEList
ASCIITOOLS = tool/AsciiArtTool
OBJS = $(MAIN).o $(RLELIST).o $(ASCIITOOLS).o
EXEC = AsciiArtTool
DEBUG_FLAG = -g
RLELIST_H = /home/mtm/public/2122b/ex1/$(RLELIST).h
COMP_FLAG = -std=c99 -I/home/mtm/public/2122b/ex1 -Itool -Wall -pedantic-errors -Werror

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(COMP_FLAG) $(DEBUG_FLAG) -o $(EXEC)
	
$(MAIN).o: $(MAIN).c $(RLELIST_H) $(ASCIITOOLS).h
	$(CC) -c $(COMP_FLAG) $*.c -o $(MAIN).o
	
$(ASCIITOOLS).o: $(ASCIITOOLS).c $(RLELIST_H) $(ASCIITOOLS).h
	$(CC) -c $(COMP_FLAG) $*.c -o $(ASCIITOOLS).o

$(RLELIST).o: $(RLELIST).c $(RLELIST_H)
	$(CC) -c $(COMP_FLAG) $*.c
	
clean:
	rm -f $(OBJS) $(EXEC)
