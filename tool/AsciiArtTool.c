#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/time.h>

#include "RLEList.h"
#include "AsciiArtTool.h"

#define BUFFER_SIZE 256


RLEList asciiArtRead(FILE* in_stream) {
    if(!in_stream) {
        return NULL;
    }
    
    RLEList compressedFile = RLEListCreate();

    char currentFileChar = 0;

    while(currentFileChar != EOF) {
        currentFileChar = fgetc(in_stream);
        if(currentFileChar != EOF) {
            RLEListAppend(compressedFile, currentFileChar);
        }
    }

    return compressedFile;
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
