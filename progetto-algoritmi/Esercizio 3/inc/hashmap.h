#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define CAPACITY_INIT 256
#define SIZE_INIT 0
#define PRIME_NUM 7

#define CATCH_ERROR     if(errno) { dprintf(STDERR_FILENO, \
                        "Error PID %d, file %s at line %d: errno %d (%s)\n", \
                        getpid(), __FILE__, __LINE__, errno, strerror(errno));}

/**
 * Hashmap struct
 */
typedef struct _HashMap HashMap;

/**
 * function to create a new Hashmap
 * @return: pointer to the new hashmap
 */
HashMap *new_hashMap();

/**
 * function to delete a hashmap and free the memory it was occupying
 * @param hashMap: pointer to the hashmap to delete
 */
void delete_hashMap(HashMap *);

/**
 * @param hashMap: pointer to hashmap
 * @return true if hashmap is empty, false otherwise
 */
int is_empty(HashMap *);

/**
 * @param hashMap: pointer to the hashmap
 * @return: number of Associations currently in the hashmap
 */
int get_size(HashMap *);

/**
 * function to empty the array inside of the hashmap struct and to free the memory it occupied
 * @param hashMap: pointer to hashmap
 */
void empty_hashMap(HashMap *);

/**
 * function to determine whether a key has already been used in the hashmap
 * @param hashMap: pointer to hashmap
 * @param k: key to look for
 * @return element's index in the hashmap if the key has already been used, -1 if there's no element with this key
 */
int contains(HashMap *, void *);

/**
 * function to add a new association to the hashmap using a hash function.
 * if the key specified already exists in the map, the previous value associated to that key will be changed with the new one.
 * @param hashMap: pointer to the hashmap
 * @param k: pointer to the key
 * @param v: pointer to the value
 * @return: index where the association was added
 */
int add(HashMap *, void *, void *);

/**
 * function to get the value associated to a specific key
 * @param hashMap: pointer to the hashmap
 * @param k: key to search
 * @return pointer to the requested value
 */
void *get(HashMap *, void *);

/**
 * function to delete an association with a specific key
 * @param hashMap: pointer to the hashmap
 * @param k: key to search
 */
void delete(HashMap *, void *);

/**
 * function to get the set of keys in the hashmap
 * @param hashMap: hashmap
 * @return array of pointers to keys
 */
void **get_keys(HashMap *);

/**
 * function to print the hashmap stats -DEBUG
 */
void print(HashMap *);