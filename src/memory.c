#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>
#include "memory.h"

array* init_array(){
        array* new_array = (array* ) malloc(sizeof(array));
        new_array->element_size = (int) sizeof(Vector3);
        new_array->position = 0;
        new_array->length = 1000;
        new_array->start = malloc(new_array->element_size * new_array->length);
        return new_array;
}

int add_element(array* now_array, Vector3 element){
        if(now_array->position >= now_array->length){
                now_array->length *= 2;
                if((now_array->start = realloc(now_array->start, now_array->element_size * now_array->length)) == NULL){
                        printf("error: ran out of memory\n");
                        return 0;
                }
        }
        *(now_array->start + now_array->position) = element;
        now_array->position++;
        return 1;
}

Vector3 get_element(array* now_array, int index){
        return *(now_array->start+index);
}

int get_length(array* now_array){
	return now_array->position;
}
