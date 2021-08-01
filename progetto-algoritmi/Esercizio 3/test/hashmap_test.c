#include <stdlib.h>
#include "../inc/hashmap.h"
#include "./Unity/unity.h"


static void new_hashMap_test() {
    HashMap *hashMap = new_hashMap();
    TEST_ASSERT_FALSE(hashMap == NULL);
    TEST_ASSERT_EQUAL(0, get_size(hashMap));
    delete_hashMap(hashMap);
}

static void is_empty_test() {
    HashMap *hashMap = new_hashMap();
    TEST_ASSERT_EQUAL(TRUE, is_empty(hashMap));
    delete_hashMap(hashMap);
}

static void contains_test() {
    HashMap *hashMap = new_hashMap();
    int key = 4;
    TEST_ASSERT_TRUE(contains(hashMap, &key) == -1);
    delete_hashMap(hashMap);
}

static void add_test() {
    HashMap *hashMap = new_hashMap();
    int key = 4;
    int value = 3;
    int index = add(hashMap, &key, &value);
    TEST_ASSERT_EQUAL(index, contains(hashMap, &key));
    TEST_ASSERT_EQUAL(1, get_size(hashMap));
    TEST_ASSERT_EQUAL(3, *(int *) get(hashMap, &key));
    delete(hashMap, &key);
    TEST_ASSERT_EQUAL(0, get_size(hashMap));
    add(hashMap, &key, &value);
    void **keys = get_keys(hashMap);
    TEST_ASSERT_EQUAL(key,*(int*)keys[0]);
    empty_hashMap(hashMap);
    TEST_ASSERT_EQUAL(0, get_size(hashMap));
    TEST_ASSERT_EQUAL(NULL, get(hashMap, &key));
    delete_hashMap(hashMap);
}


int main(int argc, char *argv[]) {
    UNITY_BEGIN();
    RUN_TEST(new_hashMap_test);
    RUN_TEST(is_empty_test);
    RUN_TEST(contains_test);
    RUN_TEST(add_test);
    UNITY_END();
}