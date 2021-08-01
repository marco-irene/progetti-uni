#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "../include/ordered_array.h"

#define ARRAY_CAPACITY 20000000

time_t time_start, time_end;

typedef struct _record {
    int id;
    char *field1;
    int field2;
    float field3;
} record;

int compare_field1(record *record1, record *record2) {
    return strcmp(record1->field1, record2->field1);
}

int compare_field2(record *record1, record *record2) {
    return record1->field2 - record2->field2;
}

int compare_field3(record *record1, record *record2) {
    float result = record1->field3 - record2->field3;
    if (result < 0) {
        return -1;
    } else if (result > 0) {
        return 1;
    } else {
        return 0;
    }
}

void print_array(OrderedArray *orderedArray) {
    time(&time_start);
    printf("Inizio a copiare l'array ordinato in records_ordered...\n");
    FILE *file = fopen("data/records_ordered", "w");
    for (int i = 0; i < get_size(orderedArray); i++) {
        record *rec = get_obj(orderedArray, i);
        fprintf(file, "%d,%s,%d,%f\n", rec->id, rec->field1, rec->field2,rec->field3);
    }
    time(&time_end);
    printf("File finito in %d seconds\n", (int) difftime(time_end, time_start));
}

void records_into_array(OrderedArray *orderedArray, char *filename) {
    time(&time_start);
    printf("Copio i dati dentro l'array...\n");
    FILE *file = fopen(filename, "r");
    CATCH_ERROR
    while (!feof(file)) {
        record *rec = (record *) malloc(sizeof(record));
        rec->field1 = (char *) malloc(sizeof(20)); 
        fscanf(file, "%d,%20[^,],%d,%f\n", &rec->id, rec->field1, &rec->field2, &rec->field3);
        CATCH_ERROR
        OrderedArray_insert(orderedArray, rec);
    }
    time(&time_end);
    printf("Dati copiati in %d secondi\n", (int) difftime(time_end, time_start));
}

void sort_array(OrderedArray *oa, int *s) {
    void *cmp;
    printf("Inizio ordinamento array...\n");
    time(&time_start);
    if (s[1] == 1) {
        cmp = (OrderedArrayCmp) compare_field1;
    } else if (s[1] == 2) {
        cmp = (OrderedArrayCmp) compare_field2;
    } else {
        cmp = (OrderedArrayCmp) compare_field3;
    }

    if (s[0] == 1) {
        quickSort(oa ,0,get_size(oa)-1, cmp, sizeof(record));
    } else {
        insertionSort(oa, cmp, sizeof(record));
    }
    time(&time_end);
    printf("Array ordinato in %d seconds\n", (int) difftime(time_end, time_start));
}



int main(int argc, char *argv[]) {
    char *path;
    if (strlen(argv[1]) != 0) {
        path = argv[1];
    } else {
        path = "data/records.csv";
    }
    int *s;
    s=malloc(2*sizeof(int));
    do {
        printf("Seleziona algoritmo: 1)QUICKSORT 2)INSERTIONSORT ==>");
        
        scanf("%d", &s[0]);
    } while ((s[0] != 1) && (s[0]!=2));


    do {    
        printf("Seleziona il tipo di elementi da ordinare: 1)[char*], 2)[int], 3)[float] ==> ");
        
        scanf("%d", &s[1]);
    } while ((s[1] != 1) && (s[1]!=2) && (s[1]!=3));
 
    
    OrderedArray *oa = OrderedArray_new(ARRAY_CAPACITY);
    records_into_array(oa, path);
    sort_array(oa, s);
    print_array(oa);
    OrderedArray_free(oa);
    free(s);
    exit(0);
}
