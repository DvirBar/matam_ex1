#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "RLEList.h"
#include "AsciiArtTool.h"

RLEList asciiArtRead(FILE* in_stream) {
    if(!in_stream) {
        return NULL;
    }
    
    RLEList compressedFile = RLEListCreate();
    char currentFileChar = 0;
    // TODO: What if it fails?
    while(fscanf(in_stream, "%c", &currentFileChar) != EOF) {
        RLEListAppend(compressedFile, currentFileChar);
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

    if(decompressedStr == NULL) {
        result = RLE_LIST_NULL_ARGUMENT;
        return result;
    }

//    decompressedStr[decompressedStrLen] = '\0';
//
    for(int i = 0; i < decompressedStrLen; i++) {
        decompressedStr[i] = RLEListGet(list, i, &result);
        if(!decompressedStr[i]) {
            return result;
        }
    }
    
    fprintf(out_stream, "%s", decompressedStr);
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
