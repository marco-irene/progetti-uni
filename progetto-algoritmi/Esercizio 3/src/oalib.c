#include "../inc/oalib.h"
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

struct _OrderedArray {
    void **array;
    int capacity;
    int size;
};

OrderedArray *new_ordered_array(int capacity) {
    OrderedArray *oa = (OrderedArray *) malloc(sizeof(OrderedArray));
    oa->array = (void **) malloc(sizeof(void *) * capacity);
    oa->capacity = capacity;
    oa->size = 0;
    return oa;
}

void free_ordered_array(OrderedArray *oa) {
    for (int i = 0; i < get_size_arr(oa) - 1; i++) {
        free(oa->array[i]);
    }
    free(oa);
}

void resize_ordered_array(OrderedArray *oa) {
    oa->capacity = oa->capacity * 2;
    oa->array = (void **) realloc(oa->array, sizeof(void *) * oa->capacity);
}

int get_size_arr(OrderedArray *oa) {
    return oa->size;
}

int get_capacity_arr(OrderedArray *oa) {
    return oa->capacity;
}

void *get_obj(OrderedArray *oa, int i) {
    if (i > oa->size - 1 || i < 0) {
        return NULL;
    }
    return oa->array[i];
}

void remove_obj(OrderedArray *oa, int pos) {
    if ((pos >= 0) && (pos > oa->size) - 1) {
        for (int i = pos; i < oa->size - 1; i++) {
            oa->array[i] = oa->array[i + 1];
        }
        oa->size--;
    }
}

void insert_obj(OrderedArray *oa, void *obj) {
    if (oa->size == oa->capacity) {
        resize_ordered_array(oa);
    }
    oa->array[oa->size] = obj;
    oa->size++;
}

int is_ordered(OrderedArray *oa, compare_fun cmp) {
    for (int i = 0; i < oa->size - 1; i++) {
        if (cmp(oa->array[i], oa->array[i + 1]) > 0) {
            return FALSE;
        }
    }
    return TRUE;
}

void swap(void *a, void *b, int obj_size) {
    void *tmp = (void*)malloc(obj_size);
    memcpy(tmp, a, obj_size);
    memcpy(a, b, obj_size);
    memcpy(b, tmp, obj_size);
    free(tmp);
}

int partition(OrderedArray *oa, int low, int high, compare_fun cmp, int obj_size) {
    int i = low, j = high;
    while (i <= j) {
        while (cmp(oa->array[low], oa->array[j]) < 0) { j--; }
        while ((i <= j) && cmp(oa->array[i], oa->array[low]) <= 0) { i++; }
        if (i < j) {
            swap(oa->array[i], oa->array[j], obj_size);
            i++;
            j--;
        }
    }
    swap(oa->array[low], oa->array[j], obj_size);
    return j;
}

void quickSort_rec(OrderedArray *oa, int low, int high, compare_fun cmp, int obj_size) {
    if (low < high) {
        int pivot = partition(oa, low, high, cmp, obj_size);
        quickSort_rec(oa, low, pivot - 1, cmp, obj_size);
        quickSort_rec(oa, pivot + 1, high, cmp, obj_size);
    }
}

void quickSort(OrderedArray *oa, compare_fun cmp, int obj_size) {
    if (!is_ordered(oa, cmp)) {
        quickSort_rec(oa, 0, get_size_arr(oa) - 1, cmp, obj_size);
    }
}

void insertionSort(OrderedArray *oa, compare_fun cmp, int obj_size) {
    if (!is_ordered(oa, cmp)) {
        int i, j;
        for (i = 1; i < oa->size; i++) {
            for (j = i - 1; j >= 0; j--) {
                if (cmp(oa->array[j], oa->array[j + 1]) > 0) {
                    swap(oa->array[j + 1], oa->array[j], obj_size);
                }
            }
        }
    }
}