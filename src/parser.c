#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <string.h>
#include "memory.h"

array* vertices;
int pvertices;
int ptriangles;

void strip_spaces(char *line){
        int n = strlen(line);
        int p = 0;
        int num_space = 0;
        for(int i = 0; i < n; i++){
                if(line[i] == ' '){
                        if(p == 0){
                                continue;
                        }
                        num_space++;
                }
                else{
                        num_space = 0;
                }
                if(num_space > 1){
                        continue;
                }
                line[p] = line[i];
                p++;
        }
        line[p] = '\0';
}

int parse_line(char *line, array* vertex_index){
        char* current_word;
	strip_spaces(line);
	int line_length = (int) strlen(line);
        int cp = 0;
        int first_vertex;
        int prev_vertex;
        int vertex;
	Vector3 final_vertex;
        int *saveptr;
	int vp = 0;
	char *has_slash = strchr(line, '/');
        while((current_word = strtok(line+cp, " ")) != NULL && cp < line_length){
		if(has_slash == NULL){
			sscanf(current_word, "%d", &vertex);
		}
		else{
			sscanf(current_word, "%d/", &vertex);
		}
                if(vp == 0){
                        first_vertex = vertex;
                }
                if(vp > 2){
                        add_element(vertex_index, get_element(vertices, first_vertex - 1));
			add_element(vertex_index, get_element(vertex_index, ptriangles-1));
			ptriangles+=2;
                        vp += 2;
                }
                add_element(vertex_index, get_element(vertices, vertex - 1));
                vp++;
		ptriangles++;
                cp += strlen(current_word)+1;
        }
        return vp;
}

int parse_obj(char* fname, array* final_vertices){
	int has_textures = 0;
	int has_normals = 0;
	FILE* f = fopen(fname, "r");
	char line_buffer[100];
	vertices = init_array();
	ptriangles = 0;
	while(fgets(line_buffer, 100, f) != NULL){
	if(line_buffer[0] == 'v' && line_buffer[1] == ' '){
		float v1, v2, v3;
		sscanf(line_buffer+2, "%f %f %f", &v1, &v2, &v3);
		Vector3 v = (Vector3) {v1, v2, v3};
		add_element(vertices, v);
	}
	if(line_buffer[0] == 'v' && line_buffer[1] == 't'){
		has_textures = 1;
	}
	if(line_buffer[0] == 'v' && line_buffer[1] == 't'){
                has_normals = 1;
        }
	if(line_buffer[0] == 'f' && line_buffer[1] == ' '){
		parse_line(line_buffer+2, final_vertices);
	}
	}
	printf("T:%d\n", get_length(final_vertices));
	return get_length(final_vertices);
}

