#include <stdlib.h>
#include "unity.h"
#include "../include/ordered_array.h"

typedef struct _record {
    int id;
    int n;
} record;

static int compare(int *x, int *y) {
    return *x - *y;
}

static record *init_record(int id, int n) {
    record *new_record = (record *) malloc(sizeof(record));
    new_record->id = id;
    new_record->n = n;
    return new_record;
}

static void ordered_array_zero_sized() {
    OrderedArray *oa = OrderedArray_new(100);
    TEST_ASSERT_EQUAL(0, get_size(oa));
    TEST_ASSERT_EQUAL(100, get_capacity(oa));
    OrderedArray_free(oa);
}

static void insert_obj() {
    OrderedArray *oa = OrderedArray_new(100);
    OrderedArray_insert(oa, init_record(1,11));
    OrderedArray_insert(oa, init_record(2,7));
    OrderedArray_insert(oa, init_record(3,9));
    record *record1=get_obj(oa, 0);
    record *record2=get_obj(oa, 1);
    record *record3=get_obj(oa, 2);

    TEST_ASSERT_EQUAL(3, get_size(oa));
    TEST_ASSERT_EQUAL(11,record1->n);
    TEST_ASSERT_EQUAL(7,record2->n);
    TEST_ASSERT_EQUAL(9,record3->n);
    
    OrderedArray_free(oa);
}

static void remove_obj_from_array() {
    OrderedArray *oa = OrderedArray_new(10);

    OrderedArray_insert(oa, init_record(1,24));
    OrderedArray_insert(oa, init_record(2,16));
    OrderedArray_remove(oa, 0);
    record *record1=get_obj(oa, 0);

    TEST_ASSERT_EQUAL(1, get_size(oa));
    TEST_ASSERT_EQUAL(2, record1->id);
    OrderedArray_free(oa);
}

static void test_insertion_sort() {
    OrderedArray *oa = OrderedArray_new(5);
    OrderedArray_insert(oa, init_record(4, 50));
    OrderedArray_insert(oa, init_record(3, 50));
    OrderedArray_insert(oa, init_record(1, 50));
    OrderedArray_insert(oa, init_record(5, 50));
    OrderedArray_insert(oa, init_record(2, 50));
    insertionSort(oa, (OrderedArrayCmp) compare, sizeof(int));
    record* record1;
    for (int i = 0; i < 5; i++) {
        record1 = get_obj(oa,i);
        TEST_ASSERT_EQUAL(i + 1, record1->id);
    }
    OrderedArray_free(oa);
}

static void test_quick_sort() {
    OrderedArray *oa = OrderedArray_new(5);
    OrderedArray_insert(oa, init_record(4, 50));
    OrderedArray_insert(oa, init_record(3, 50));
    OrderedArray_insert(oa, init_record(1, 50));
    OrderedArray_insert(oa, init_record(5, 50));
    OrderedArray_insert(oa, init_record(2, 50));
    record* record1;
    quickSort(oa, 0, get_size(oa)-1 , (OrderedArrayCmp) compare, sizeof(int));
    for (int i = 0; i < 5; i++) {
        record1 = get_obj(oa,i);
        TEST_ASSERT_EQUAL(i + 1, record1->id);
    }
    OrderedArray_free(oa);
}

int main(int argc, char *argv[]) {
    UNITY_BEGIN();
    RUN_TEST(ordered_array_zero_sized);
    RUN_TEST(insert_obj);
    RUN_TEST(remove_obj_from_array);
    RUN_TEST(test_insertion_sort);
    RUN_TEST(test_quick_sort);
    UNITY_END();
}