#include "../inc/hashmap.h"

typedef struct _Association {
    void *key;
    void *value;
} Association;

struct _HashMap {
    Association **array;
    int capacity;
    int size;
};

/**
 * double hash function to associate an index to every association to add
 * @param capacity: current hashmap capacity
 * @param k: key of the element that needs to be added to the hashmap
 * @param i: counter used to scan different possible locations within the hashmap
 * @return: index where the key's Association will be added
 */

int hash(int capacity, void *k, int i) {
    int key = *(int *) (k);
    return ((key % capacity) + (i * (PRIME_NUM - (key % PRIME_NUM)))) % capacity;
}

/**
 * function to create a new Hashmap
 * @return: pointer to the new hashmap
 */
HashMap *new_hashMap() {
    HashMap *hashMap = (HashMap *) malloc(sizeof(HashMap));
    hashMap->capacity = CAPACITY_INIT;
    hashMap->array = (Association **) malloc(sizeof(Association *) * CAPACITY_INIT);
    hashMap->size = SIZE_INIT;
    for (int i = 0; i < CAPACITY_INIT; i++) {
        hashMap->array[i] = NULL;
    }
    return hashMap;
}

/**
 * function to delete a hashmap and free the memory it was occupying
 * @param hashMap: pointer to the hashmap to delete
 */
void delete_hashMap(HashMap *hashMap) {
    for (int i = 0; i < hashMap->capacity; i++) {
        if (hashMap->array[i] != NULL) {
            free(hashMap->array[i]->key);
            free(hashMap->array[i]->value);
        }
        free(hashMap->array[i]);
    }
    free(hashMap);
}

/**
 * @param hashMap: pointer to the hashmap
 * @return: number of Associations currently in the hashmap
 */
int get_size(HashMap *hashMap) {
    return hashMap->size;
}

/**
 * @param hashMap: pointer to hashmap
 * @return true if hashmap is empty, false otherwise
 */
int is_empty(HashMap *hashMap) {
    return hashMap->size == 0 ? TRUE : FALSE;
}

/**
 * @param hashMap: pointer to hashmap
 * @return TRUE is the hashmap is 50% full and needs resizing, FALSE otherwise
 */
int is_full(HashMap *hashMap) {
    //int percentage = (75 * hashMap->capacity) / 100;
    return hashMap->size >= hashMap->capacity / 2 ? TRUE : FALSE;
}

/**
 * function to double the size of the hashmap and reposition all of the elements it already had inside
 * @param hashMap: pointer to hashmap
 */
void rehash(HashMap *hashMap, int flag) {
    int old_capacity = hashMap->capacity;
    Association **tmp_arr = hashMap->array;

    if (flag) {
        hashMap->capacity = hashMap->capacity / 2;
    } else {
        hashMap->capacity = hashMap->capacity * 2;
    }
    hashMap->size = SIZE_INIT;
    hashMap->array = (Association **) malloc(sizeof(Association *) * hashMap->capacity);

    for (int i = 0; i < old_capacity; i++) {
        if (tmp_arr[i] != NULL && tmp_arr[i]->key != NULL) {
            add(hashMap, tmp_arr[i]->key, tmp_arr[i]->value);
        }
    }

    for (int i = 0; i < old_capacity; i++) {
        if (tmp_arr[i] != NULL) {
            free(tmp_arr[i]->key);
            free(tmp_arr[i]->value);
        }
        free(tmp_arr[i]);
    }
    free(tmp_arr);
}

/**
 * function to empty the array inside of the hashmap struct and to free the memory it occupied
 * @param hashMap: pointer to hashmap
 */
void empty_hashMap(HashMap *hashMap) {
    for (int i = 0; i < get_size(hashMap) - 1; i++) {
        free(hashMap->array[i]);
    }
    hashMap->capacity = 50;
    hashMap->array = (Association **) malloc(sizeof(Association *) * hashMap->capacity);
    hashMap->size = 0;
}

/**
 * function to determine whether a key has already been used in the hashmap
 * @param hashMap: pointer to hashmap
 * @param k: key to look for
 * @return element's index in the hashmap if the key has already been used, -1 if there's no element with this key
 */
int contains(HashMap *hashMap, void *k) {
    int i = 0;
    for (;;) {
        int j = hash(hashMap->capacity, k, i);
        if (hashMap->array[j] == NULL) {
            return -1;
        } else if (hashMap->array[j]->key != NULL && *(int *) (hashMap->array[j]->key) == *(int *) (k)) {
            return j;
        }
        //printf("loop\n");
        i++;
    }
}

/**
 * function to create a new association
 * @param k: pointer to the key
 * @param v: pointer to the value
 * @return: new association
 */
Association *new_association(void *k, void *v) {
    Association *association = (Association *) malloc(sizeof(Association));
    association->key = (void *) malloc(sizeof(void *));
    association->value = (void *) malloc(sizeof(void *));
    memcpy(association->key, k, sizeof(k));
    memcpy(association->value, v, sizeof(v));
    return association;
}

/**
 * function to add a new association to the hashmap using a hash function.
 * if the key specified already exists in the map, the previous value associated to that key will be changed with the new one.
 * @param hashMap: pointer to the hashmap
 * @param k: pointer to the key
 * @param v: pointer to the value
 * @return: index where the association was added
 */
int add(HashMap *hashMap, void *k, void *v) {
    int c = contains(hashMap, k);
    if (c == -1) {
        Association *association = new_association(k, v);
        int i = 0;

        if (is_full(hashMap)) { rehash(hashMap, 0); }

        int j = hash(hashMap->capacity, k, i);
        if (hashMap->array[j] == NULL || hashMap->array[j]->key == NULL) {
            hashMap->array[j] = association;
            hashMap->size++;
            //printf("AGGIUNTO => HASH(%d) => %d, i => %d\n", *(int *) k, j, i);
            return j;
        } else {
            for (;;) {
                i++;
                j = hash(hashMap->capacity, k, i);
                if (hashMap->array[j] != NULL && hashMap->array[j]->key == NULL) {
                    free(hashMap->array[j]);
                    hashMap->array[j] = NULL;
                }
                if (hashMap->array[j] == NULL) {
                    hashMap->array[j] = association;
                    hashMap->size++;
                    //printf("AGGIUNTO => HASH(%d) => %d, i => %d\n", *(int *) k, j, i);
                    return j;
                }
                /*if (i == hashMap->capacity/2) {
                    rehash(hashMap);
                    i = -1;
                }*/
            }
        }
    } else {
        hashMap->array[c]->value = v;
        return c;
    }
}

/**
 * function to get the value associated to a specific key
 * @param hashMap: pointer to the hashmap
 * @param k: key to search
 * @return pointer to the requested value
 */
void *get(HashMap *hashMap, void *k) {
    int j = contains(hashMap, k);
    if (j == -1) {
        return NULL;
    } else {
        return hashMap->array[j]->value;
    }
}

/**
 * function to delete an association with a specific key
 * @param hashMap: pointer to the hashmap
 * @param k: key to search
 */
void delete(HashMap *hashMap, void *k) {
    int j = contains(hashMap, k);
    if (j != -1) {
        hashMap->array[j]->key = NULL;
        hashMap->array[j]->value = NULL;
        hashMap->size--;
    }
    
    if (hashMap->size == hashMap->capacity / 5) {
        rehash(hashMap, 1);
    }
}

/**
 * function to get the set of keys in the hashmap
 * @param hashMap: hashmap
 * @return array of pointers to keys
 */
void **get_keys(HashMap *hashMap) {
    void **keys_arr = (void *) malloc(sizeof(void *) * hashMap->size);
    int j = 0;
    for (int i = 0; i < hashMap->capacity; i++) {
        if (hashMap->array[i] != NULL && hashMap->array[i]->key != NULL) {
            keys_arr[j] = hashMap->array[i]->key;
            j++;
        }
    }
    return keys_arr;
}

/**
 * function to print the hashmap stats
 */
void print(HashMap *hashMap) {
    printf("================= hash stats ========================\n");
    printf("CAPACITY => %d\n", hashMap->capacity);
    printf("SIZE => %d\n", hashMap->size);
    for (int i = 0; i < hashMap->capacity; i++) {
        if (hashMap->array[i] != NULL && hashMap->array[i]->key != NULL) {
            printf("Association pointer => %p, Key => %d, value => %d, index => %d\n", hashMap->array[i],
                   *(int *) hashMap->array[i]->key,
                   *(int *) hashMap->array[i]->value, i);
        }
    }
    printf("=========================================\n");
}
