#include "RLEList.h"
#include <stdlib.h> // TODO: Verify this

#define UNDEFINED -1
#define STR_FORMAT_BASE_LEN 2

struct RLEList_t {
    char value;
    int num;
    struct RLEList_t* next;
};

static int RLEListNodeNumber(RLEList list) {
    int nodesInList = 0;
    RLEList temporaryList = list;

    while(temporaryList) {
        nodesInList++;
        temporaryList = temporaryList->next;
    }

    return nodesInList;
}

static int getNumDigits(int num) {
    int counter = 1;
    int base = 10;
    
    while(num/base) {
        counter++;
        base*=base;
    }
    
    return counter;
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
    if(list == NULL || !value) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    
    RLEList ptr = list->next;
    
    while(ptr) {
        ptr = ptr->next;
    }
    
    if(!list->value || list->value == value) {
        list->num++;
        return RLE_LIST_SUCCESS;
    }
    
    RLEList newList = RLEListCreate();
    
    if(newList == NULL) {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    
    newList->value = value;
    newList->num = 1;
    newList->next = NULL;
    list->next = newList;
    
    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list) {
    if(list == NULL) {
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
    if(list == NULL || !index) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    if(index < 0 || index >= RLEListSize(list)) {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    
    RLEList lastNode = NULL;
    RLEList ptr = list->next;
    
    for(int i = 0; i + list->num <= index; i += list->num) {
        lastNode = ptr;
        ptr = ptr->next;
    }
    
    if(ptr->num == 1) {
        if(lastNode != NULL) {
            lastNode->next = ptr->next;
        }
        
        free(ptr);
    }
    
    else {
        ptr->num--;
    }
    
    return RLE_LIST_SUCCESS;
}

char RLEListGet(RLEList list, int index, RLEListResult *result) {
    if(list == NULL) {
        if(result != NULL) {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        
        return 0;
    }

    if((index < 0) || (index >= RLEListSize(list))) {
        if(result != NULL) {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }

        return 0;
    }

    RLEList tempList = list;
    
   
    for (int i = 0; i + tempList->num <= index; i += tempList->num) {
        tempList = tempList->next;
    }

    if(result != NULL) {
        *result = RLE_LIST_SUCCESS;
    }

    return tempList->value;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function) {
    if(list == NULL || map_function == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    
    RLEList ptr = list;
    
    while(ptr) {
        ptr->value = map_function(ptr->value);
        ptr = ptr->next;
    }
    
    return RLE_LIST_SUCCESS;
}

char* RLEListExportToString(RLEList list, RLEListResult* result) {
    if(list == NULL) {
        if(result != NULL) {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }
    
    int nodesInList = RLEListNodeNumber(list);
    int stringIndex = 0;

    char* exportedString = malloc((nodesInList * STR_FORMAT_BASE_LEN) + 1);

    if(exportedString == NULL) {
        if (result != NULL) {
            *result = RLE_LIST_OUT_OF_MEMORY;
        }
        return NULL;
    }

    RLEList tempList = list;
    
    while(tempList) {
        exportedString[stringIndex] = tempList->value;
        stringIndex++;
        exportedString[stringIndex] = tempList->num;
        stringIndex++;
        exportedString[stringIndex] = '\n';
        stringIndex++;
        tempList = tempList->next;
    }

    if (result != NULL) {
        *result = RLE_LIST_SUCCESS;
    }

    return exportedString;
}

