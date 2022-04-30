#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "RLEList.h"
#include "AsciiArtTool.h"


RLEList asciiArtRead(FILE* in_stream) {
    if(!in_stream) {
        return NULL;
    }

    // Create a dummy node
    RLEList list = RLEListCreate();

    char currentChar = fgetc(in_stream);
    RLEListResult result = RLE_LIST_SUCCESS;

    while(currentChar != EOF && result == RLE_LIST_SUCCESS) {
        result = RLEListAppend(list, currentChar);
        currentChar = fgetc(in_stream);
    }
    
    if(result != RLE_LIST_SUCCESS) {
        return NULL;
    }

    return list;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream) {
    if(!list || !out_stream) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    
    RLEListResult result = RLE_LIST_SUCCESS;
    
    int strLen = RLEListSize(list);
    char currentChar = 0;
    for(int i = 0; i < strLen && result == RLE_LIST_SUCCESS; i++) {
        currentChar = RLEListGet(list, i, &result);
        if(result == RLE_LIST_SUCCESS) {
            fputc(currentChar, out_stream);
        }
    }
    
    return result;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream) {
    if(!list || !out_stream) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    
    RLEListResult result = RLE_LIST_SUCCESS;
    char* encodedStr = RLEListExportToString(list, &result);
    fprintf(out_stream, "%s", encodedStr);
    free(encodedStr);
    
    return result;
}
