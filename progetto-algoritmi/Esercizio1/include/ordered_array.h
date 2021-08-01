#pragma once

#define CATCH_ERROR     if(errno) { dprintf(STDERR_FILENO, \
                        "Error PID %d, file %s at line %d: errno %d (%s)\n", \
                        getpid(), __FILE__, __LINE__, errno, strerror(errno));}

/**
 * Defined the OrderedArray structure that contains the array information
 */
typedef struct _OrderedArray OrderedArray;

/**
 * Pointer to function for sorting generic elements,
 * return value < 0 if void* < void*
 * return value == 0 if void* == void*
 * return value > 0 if void* > void*
 */
typedef int (*OrderedArrayCmp)(void*, void*) ;

/**
 * Constructor
 */
OrderedArray *OrderedArray_new(int);

/**
 * Free the allocated memory
 */
void OrderedArray_free(OrderedArray *);

/**
 * return how many element inside array
 */
int get_size(OrderedArray*);

/**
 * return array capacity
 */
int get_capacity(OrderedArray*);

/**
 * insert of generic elemente into array
 */
void OrderedArray_insert(OrderedArray *, void *);

/**
 * return the element into i position
 */
void *get_obj(OrderedArray *, int);

/**
 * removing an object from i position
 */
void OrderedArray_remove(OrderedArray*, int);

/**
 * InsertionSort sorting algorithm
 */
void insertionSort(OrderedArray *, OrderedArrayCmp, int);

/**
 * Quicksort sorting algorithm
 */
void quickSort(OrderedArray *,int , int ,OrderedArrayCmp, int);

/**
 * change value of two object
 */
void swap(void *, void *, int);

/**
 * partition of quicksort algorithm
 */
int partition(OrderedArray *, int , int , OrderedArrayCmp , int );
