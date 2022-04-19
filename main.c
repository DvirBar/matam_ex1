#include <stdio.h>
#include "RLEList.h"
#include "AsciiArtTool.h"

#define ENCODED_FLAG 'e'
#define INVERTED_FLAG 'i'

int main(int argc, char** argv) {
    if(argc != 3) {
        // TODO: Should we raise another error here?
        return 0;
    }
    
    char flag = argv[0][1];
    
    if(argv[0][0] != '-' || flag != ENCODED_FLAG || flag != INVERTED_FLAG) {
        return 0;
    }
    
    FILE* source = fopen(argv[1], "r");
    if(!source) {
        return 0;
    }
    
    FILE* target = fopen(argv[2], "w");
    if(!target) {
        fclose(source);
        return 0;
    }
    
    RLEList list = asciiArtRead(source);
    RLEListResult result = RLE_LIST_ERROR;
    
    if(flag == ENCODED_FLAG) {
        result = asciiArtPrintEncoded(list, target);
    }
    else {
        result = asciiArtPrint(list, target);
    }
    
    // TODO: Should we destroy it here?
    RLEListDestroy(list);
    
    fclose(source);
    fclose(target);
    
    return result;
}
