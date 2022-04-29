#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "RLEList.h"
#include "AsciiArtTool.h"

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
   
    int decompressedStrLen = RLEListSize(list);
    char* decompressedStr = malloc(decompressedStrLen + 1);
    
    decompressedStr = strcpy(decompressedStr, "");

    if(decompressedStr == NULL) {
        result = RLE_LIST_NULL_ARGUMENT;
        return result;
    }

    for(int i = 0; i < decompressedStrLen; i++) {
        decompressedStr[i] = RLEListGet(list, i, &result);
        if(!decompressedStr[i]) {
            return result;
        }
    }
//    char currentChar = 0;
//    for(int i = 0; i < decompressedStrLen && result == RLE_LIST_SUCCESS; i++) {
//        currentChar = RLEListGet(list, i, &result);
//        if(result == RLE_LIST_SUCCESS) {
//            fputc(currentChar, out_stream);
//        }
//    }
    
    fputs(decompressedStr, out_stream);
    free(decompressedStr);
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
