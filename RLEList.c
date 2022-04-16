#include "RLEList.h"
#include "stdlib.h"

struct RLEList_t {
    char value;
    int num;
    struct RLEList_t* next;
};

RLEList RLEListCreate() {
    RLEList list = malloc(sizeof(*list));
    
    if(list == NULL) {
        return NULL;
    }
    
    return list;
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

//TODO: implement
int RLEListSize(RLEList list);

RLEListResult RLEListRemove(RLEList list, int index) {
    if(list == NULL || !index) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    
    if(index < 0 || index > RLEListSize(list)) {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    
    RLEList lastNode = NULL;
    RLEList ptr = list->next;
    
    for(int i=0; i+list->num <= index; i+=list->num) {
        lastNode = ptr;
        ptr = ptr->next;
    }
    
    //TODO: Should we free this node? see here: https://piazza.com/class/l0tbx31evh31vr?cid=238
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
