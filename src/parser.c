#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <raymath.h>

float vertices[5000][3];
int pvertices;
int ptriangles;

int parse_obj(char* fname, Vector3* final_vertices){
	int has_textures = 0;
	int has_normals = 0;
	FILE* f = fopen(fname, "r");
	char line_buffer[100];
	pvertices = 0;
	ptriangles = 0;
	while(fgets(line_buffer, 100, f) != NULL){
	if(line_buffer[0] == 'v' && line_buffer[1] == ' '){
		float v1, v2, v3;
		sscanf(line_buffer+2, "%f %f %f", &v1, &v2, &v3);
		vertices[pvertices][0] = v1;
		vertices[pvertices][1] = v2;
		vertices[pvertices][2] = v3;
		pvertices++;
	}
	if(line_buffer[0] == 'v' && line_buffer[1] == 't'){
		has_textures = 1;
	}
	if(line_buffer[0] == 'v' && line_buffer[1] == 't'){
                has_normals = 1;
        }
	if(line_buffer[0] == 'f' && line_buffer[1] == ' '){
		int n1, n2, n3, m1, m2, m3, p1, p2, p3;
		if(has_textures == 1 && has_normals == 1){
			sscanf(line_buffer+2, "%d/%d/%d %d/%d/%d %d/%d/%d", &n1, &m1, &p1, &n2, &m2, &p2, &n3, &m3, &p3);
		}
		else if(has_textures == 0 && has_normals == 0){
			sscanf(line_buffer+2, "%d %d %d", &n1, &n2, &n3);
		}
		//else if(has_textures == 0 && has_normals == 1){
		//	sscanf(line_buffer+2, "%d//%d %d//%d %d//%d", &n1, &m1, &n2, &m2, &n3, &m3);
		//}
		else{
			sscanf(line_buffer+2, "%d %d %d", &n1, &n2, &n3);
		}
		n1--;
		n2--;
		n3--;
		Vector3 A = (Vector3) {vertices[n1][0], vertices[n1][1], vertices[n1][2]};
		Vector3 B = (Vector3) {vertices[n2][0], vertices[n2][1], vertices[n2][2]};
		Vector3 C = (Vector3) {vertices[n3][0], vertices[n3][1], vertices[n3][2]};
		final_vertices[ptriangles] = A;
		printf("%f %f %f\n", A.x, A.y, A.z);
		final_vertices[ptriangles+1] = B;
		printf("%f %f %f\n", B.x, B.y, B.z);
		final_vertices[ptriangles+2] = C;
		printf("%f %f %f\n", C.x, C.y, C.z);
		ptriangles+=3;	
	}
	}
	return ptriangles;
}

