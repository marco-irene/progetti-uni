#include "../inc/hashmap.h"
#include "../inc/oalib.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

time_t time_start, time_end;
int entries_number = 6321078;
int random_numbers = 10000000;

typedef struct _Association {
    int key;
    int value;
} Association;

/**
 * function to compare two keys
 * @param a1: first association to compare
 * @param a2 second  association to compare
 * @return : a number greater than zero if a1->key > a2->key, 0 if a1->key = a2->key, a negative number otherwise
 */
int compare_func_array(Association *a1, Association *a2) {
    return a1->key - a2->key;
}

/**
 * function to read file and fill hashmap
 * @param hashMap: hashmap to fill
 * @param path: file's location
 */
void load_data_into_hashmap(HashMap *hashMap, char *path) {
    time(&time_start);
    printf("Starting to copy records into hashmap...\n");
    FILE *file = fopen(path, "r");
    CATCH_ERROR
    while (!feof(file)) {
        int k, v;
        fscanf(file, "%d,%d\n", &k, &v);
        CATCH_ERROR
        add(hashMap, &k, &v);
    }
    time(&time_end);
    printf("Done! hashmap copied in %d seconds\n", (int) difftime(time_end, time_start));
}

/**
 * function to read file, fill array and order it
 * @param orderedArray: array to fill and order
 * @param path: file's location
 */
void load_data_into_array(OrderedArray *orderedArray, char *path) {
    time(&time_start);
    printf("Starting to copy records into array...\n");
    FILE *file = fopen(path, "r");
    CATCH_ERROR
    int i = 0;
    while (!feof(file)) {
        Association *association = (Association *) malloc(sizeof(Association));
        fscanf(file, "%d,%d\n", &association->key, &association->value);
        insert_obj(orderedArray, association);
        CATCH_ERROR
        i++;
    }
    quickSort(orderedArray, (compare_fun) compare_func_array, sizeof(Association));
    time(&time_end);
    printf("Done! array copied and ordered in %d seconds\n", (int) difftime(time_end, time_start));
}

/**
 * function to select 10000000 random integers between 0 and 10000000
 * @return array containing the random integers
 */
int *select_random() {
    int *random_array = (int *) malloc(sizeof(int) * random_numbers);
    for (int i = 0; i < random_numbers; i++) {
        int random = rand() % random_numbers;
        random_array[i] = random;
    }
    return random_array;
}

/**
 * function to find some values in the hashmap using the random integers generated as keys
 * @param hashMap: hashmap to search
 * @param random_array: array of random integers
 */
void search_in_hashmap(HashMap *hashMap, int *random_array) {
    time(&time_start);
    int found=0;
    for (int i = 0; i < random_numbers; i++) {
        if (get(hashMap, &random_array[i]) != NULL) {
            found++;
        }
    }
    time(&time_end);
    printf("Done! %d values restored from hashmap in %d seconds\n", found, (int) difftime(time_end, time_start));
}

/**
 * function to find some values in the ordered array using the random integers generated as keys (via binary search)
 * @param orderedArray: array to search
 * @param random_array: array of random integers
 */
void search_in_array(OrderedArray *orderedArray, int *random_array) {
    time(&time_start);
    int first, last, middle, search, found=0;
    Association *association;
    for (int i = 0; i < random_numbers; i++) {
        search = random_array[i];
        first = 0;
        last = entries_number;
        middle = (first + last) / 2;
        while (first <= last) {
            association = get_obj(orderedArray, middle);
            if (association->key < search)
                first = middle + 1;
            else if (association->key == search) {
                found++;
                break;
            } else
                last = middle - 1;
            middle = (first + last) / 2;
        }
    }
    time(&time_end);
    printf("Done! %d values restored from array in %d seconds\n", found, (int) difftime(time_end, time_start));
}

int main(int argc, char *argv[]) {
    srand(time(0));

    char *path;
    if (strlen(argv[1]) != 0) {
        path = argv[1];
    } else {
        path = "data/hashes.csv";
    }

    OrderedArray *orderedArray = new_ordered_array(entries_number);
    HashMap *hashMap = new_hashMap();
    load_data_into_hashmap(hashMap, path);
    load_data_into_array(orderedArray, path);
    int *random_array = select_random();
    search_in_hashmap(hashMap, random_array);
    search_in_array(orderedArray, random_array);

    free_ordered_array(orderedArray);
    delete_hashMap(hashMap);

}