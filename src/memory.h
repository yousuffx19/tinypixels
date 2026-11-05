#ifndef MEMORY_H
#define MEMORY_H

struct dynamic_array{
        int element_size;
        int position;
        int length;
        Vector3* start;
};

typedef struct dynamic_array array;

array* init_array();
int add_element(array* new_array, Vector3 element);
Vector3 get_element(array* now_array, int index);
int get_length(array* now_array);

#endif
