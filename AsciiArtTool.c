#include <stdio.h>
#include <stdlib.h>
#include "RLEList.h"
#include "AsciiArtTool.h"

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream) {
    RLEListResult result = RLE_LIST_SUCCESS;
    char* encodedStr = RLEListExportToString(list, &result);
    fprintf(out_stream, encodedStr);
    free(encodedStr);
    return result;
}
