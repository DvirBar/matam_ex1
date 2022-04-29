#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/time.h>

#include "RLEList.h"
#include "AsciiArtTool.h"

#define BUFFER_SIZE 256


static long long current_timestamp() {
    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    // printf("milliseconds: %lld\n", milliseconds);
    return milliseconds;
}

RLEList asciiArtRead(FILE* in_stream) {
    long long timeStp1 = current_timestamp();
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
    long long timeStp2 = current_timestamp();
    printf("AsciiRead took: %lld ms\n", timeStp2-timeStp1);

    return compressedFile;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream) {
    if(!list || !out_stream) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    long long timeStp1 = current_timestamp();
    RLEListResult result = RLE_LIST_SUCCESS;
    
    int strLen = RLEListSize(list);
//    char* decompressedStr = malloc(decompressedStrLen + 1);
//
//    decompressedStr = strcpy(decompressedStr, "");
//
//    if(decompressedStr == NULL) {
//        result = RLE_LIST_NULL_ARGUMENT;
//        return result;
//    }
//
//    for(int i = 0; i < decompressedStrLen; i++) {
//        decompressedStr[i] = RLEListGet(list, i, &result);
//        if(!decompressedStr[i]) {
//            return result;
//        }
//    }
    char currentChar = 0;
    for(int i = 0; i < strLen && result == RLE_LIST_SUCCESS; i++) {
        currentChar = RLEListGet(list, i, &result);
        if(result == RLE_LIST_SUCCESS) {
            fputc(currentChar, out_stream);
        }
    }
    
//    fputs(decompressedStr, out_stream);
//    free(decompressedStr);
    long long timeStp2 = current_timestamp();
    printf("AsciiPrint took: %lld ms\n", timeStp2-timeStp1);
    
    return result;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream) {
    if(!list || !out_stream) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    
    long long timeStp1 = current_timestamp();
    
    RLEListResult result = RLE_LIST_SUCCESS;
    char* encodedStr = RLEListExportToString(list, &result);
    fprintf(out_stream, "%s", encodedStr);
    free(encodedStr);
    
    long long timeStp2 = current_timestamp();
    printf("AsciiPrintEncoded took: %lld ms\n", timeStp2-timeStp1);
    
    return result;
}
