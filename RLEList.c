#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "RLEList.h"


#define UNDEFINED -1
#define STR_FORMAT_BASE_LEN 2
#define NEW_LINE_ASCII '\n'
#define ZERO_ASCII '0'
#define DECIMAL_BASE 10

struct RLEList_t {
    char value;
    int num;
    struct RLEList_t* next;
};

static int RLEListNodeNumber(RLEList list) {
    int nodesInList = 0;

    RLEList tempList = list->next;

    while(tempList) {
        nodesInList++;
        tempList = tempList->next;
    }
    
    return nodesInList;
}

static int getNumDigits(int num) {
    int counter = 1;
    int base = DECIMAL_BASE;
    
    while(num/base) {
        counter++;
        base*=DECIMAL_BASE;
    }
    
    return counter;
}

static int getRLEStringLength(RLEList list) {
    int RLEStrLength = (RLEListNodeNumber(list) * STR_FORMAT_BASE_LEN);
    RLEList tmpList = list;
    while (tmpList) {
        RLEStrLength += getNumDigits(tmpList->num);
        tmpList = tmpList->next;
    }
    return RLEStrLength;
}

static void RLENodeToString(RLEList list, char* outputStr) {
    int nodeNumOfDigits = getNumDigits(list->num);
    int strSize = nodeNumOfDigits + STR_FORMAT_BASE_LEN;
    outputStr[0] = list->value;
    outputStr[strSize - 1] = NEW_LINE_ASCII;
    int nodeCurrentDigit = list->num;

    for (int i = 1; i <= nodeNumOfDigits; i++)
    {
        outputStr[strSize - 1 - i] = (nodeCurrentDigit % 10) + ZERO_ASCII;
        nodeCurrentDigit /= 10;
    }
}

RLEList RLEListCreate() {
    RLEList list = malloc(sizeof(*list));
    
    if(list == NULL) {
        return NULL;
    }
    
    list->value = 0;
    list->num = 0;
    list->next = NULL;
    
    return list;
}

void RLEListDestroy(RLEList list) {
    RLEList currentNodeToDestroy;
    while(list) {
        currentNodeToDestroy = list;
        list = list->next;
        free(currentNodeToDestroy);
    }
}

RLEListResult RLEListAppend(RLEList list, char value) {
    if(!list || !value) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    
    RLEList tempList = list;
    
    while(tempList->next) {
        tempList = tempList->next;
    }
    
    if(tempList->value && tempList->value == value) {
        tempList->value = value;
        tempList->num++;
        return RLE_LIST_SUCCESS;
    }
    
    RLEList newList = RLEListCreate();
    
    if(!newList) {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    
    newList->value = value;
    newList->num = 1;
    newList->next = NULL;
    tempList->next = newList;
    
    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list) {
    if(!list) {
        return UNDEFINED;
    }
        
    RLEList tempList = list;
    int listCharacterNumber = 0;

    while (tempList) {
        listCharacterNumber += tempList->num;
        tempList = tempList->next;
    }

    return listCharacterNumber;
}


RLEListResult RLEListRemove(RLEList list, int index) {
    if(!list) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    if(index < 0 || index >= RLEListSize(list)) {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

    assert(!list->value);

    RLEList lastNode = list;
    RLEList tempList = list->next;

    int lastNum = 0;
    for (int i = 0; i + tempList->num <= index; i += lastNum) {
        lastNode = tempList;
        lastNum = tempList->num;
        tempList = tempList->next;
    }

    if(tempList->num == 1) {
        if(lastNode->next) {
            lastNode->next = tempList->next;
        }

        free(tempList);
    }
    else {
        tempList->num--;
    }

    return RLE_LIST_SUCCESS;
}



char RLEListGet(RLEList list, int index, RLEListResult *result) {
    if(!list) {
        if(result) {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        
        return 0;
    }

    if(index < 0 || index >= RLEListSize(list)) {
        if(result) {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }

        return 0;
    }

    RLEList tempList = list;
    int lastNum = 0;
    for (int i = 0; i + tempList->num <= index; i += lastNum) {
        lastNum = tempList->num;
        tempList = tempList->next;
    }
    
    if(result) {
        *result = RLE_LIST_SUCCESS;
    }

    return tempList->value;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function) {
    if(!list || !map_function) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    
    RLEList tempList = list;
    
    while(tempList) {
        tempList->value = map_function(tempList->value);
        tempList = tempList->next;
    }
    
    return RLE_LIST_SUCCESS;
}

char* RLEListExportToString(RLEList list, RLEListResult* result) {
    if(!list) {
        if(result) {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        
        return NULL;
    }

    assert(!list->value);
    
    int listLen = getRLEStringLength(list);
    char* exportedString = malloc(listLen + 1);

    if(!exportedString) {
        if (result) {
            *result = RLE_LIST_OUT_OF_MEMORY;
        }
        
        return NULL;
    }

    exportedString[listLen] = '\0';
    char* tmpStr = exportedString;
    
    RLEList tempList = list->next;

    while(tempList) {
        RLENodeToString(tempList, tmpStr);
        tmpStr += getNumDigits(tempList->num) + STR_FORMAT_BASE_LEN;
        tempList = tempList->next;
    }

    if (result) {
        *result = RLE_LIST_SUCCESS;
    }

    return exportedString;
}
