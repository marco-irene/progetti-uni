#include <stdlib.h>
#include <string.h>
#include "../include/ordered_array.h"

#define TRUE 1 
#define FALSE 0
/*
* struct of array created with record
*/
struct _OrderedArray {
    void **array;
    int capacity;
    int size;
};

OrderedArray *OrderedArray_new(int capacity) {
    OrderedArray *oa = (OrderedArray*) malloc(sizeof(OrderedArray));
    oa->array = (void**) malloc(sizeof(void*)* capacity);
    oa->capacity = capacity;
    oa->size = 0;
    return oa;
}

/*
* Free memory occupated from array
*/
void OrderedArray_free(OrderedArray* oa) {
    for(int i = 0; i < get_size(oa) - 1; i++){
    free(oa->array[i]);
    }
    free(oa);
}
/*
* increase capacity of array
*/
void OrderedArray_resize(OrderedArray *oa) {
    oa->capacity = oa->capacity * 2;
    oa->array = (void**) realloc(oa->array, sizeof(void*)* oa->capacity);    
}

int get_size(OrderedArray*oa){
    return oa->size;
}

int get_capacity(OrderedArray *oa){
    return oa->capacity;
}

void *get_obj(OrderedArray *oa, int i) {
    if (i > oa->size - 1 || i < 0) {
        return NULL;
    }
    return oa->array[i];
}

void OrderedArray_insert(OrderedArray* oa, void* obj){
    if(oa->size == oa->capacity){
        OrderedArray_resize(oa);
    }
    oa->array[oa->size] = obj;
    oa->size++;
}

void OrderedArray_remove(OrderedArray* oa, int i) {
    if(i >= 0 ){
       for (int j = i; j < oa->size - 1 ; j++) {
           oa->array[j] = oa ->array[j + 1];
       }
       oa->size--;
    }
}
/*
* check if the array is sorted
*/
int is_ordered(OrderedArray *oa, OrderedArrayCmp cmp) {
    for(int i = 0; i < oa->size - 1; i++){
        if (cmp(oa->array[i], oa->array[i + 1]) > 0) {
            return FALSE;
        }
    }
    return TRUE;
}

void insertionSort(OrderedArray *oa,OrderedArrayCmp cmp, int obj_size) {
    int i, j;
    for (i = 1; i < oa->size; i++) {
        for (j = i - 1; j >= 0; j--) {
            if (cmp(oa->array[j], oa->array[j + 1]) > 0) {
                swap(oa->array[j + 1], oa->array[j], obj_size);
            }
        }
    }
}

void swap(void *a, void *b, int obj_size) {
    void *tmp = (void*)malloc(obj_size);
    memcpy(tmp, a, obj_size);
    memcpy(a, b, obj_size);
    memcpy(b, tmp, obj_size);
    free(tmp);
}

void quickSort(OrderedArray *oa, int first, int last, OrderedArrayCmp cmp, int obj_size) {
    if (first < last) {
        int pivot = partition(oa, first, last, cmp, obj_size);
        quickSort(oa, first, pivot - 1, cmp, obj_size);
        quickSort(oa, pivot + 1, last, cmp, obj_size);
    }
}

int partition(OrderedArray *oa, int first, int last, OrderedArrayCmp cmp, int obj_size) {
    int i = first, j = last;
    while (i <= j) {
        while (cmp(oa->array[first], oa->array[j]) < 0) { 
            j--; 
        }
        while ((i <= j) && cmp(oa->array[i], oa->array[first]) <= 0) { 
            i++; 
            }
        if (i < j) {
            swap(oa->array[i], oa->array[j], obj_size);
            i++;
            j--;
        }
    }
    swap(oa->array[first], oa->array[j], obj_size);
    return j;
}