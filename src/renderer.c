#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include "parser.h"

float z_buffer[800][800];

float max(float f1, float f2, float f3){
	if(f1 >= f3 && f1 >= f2){
		return f1;
	}
	else if(f2 >= f3 && f2 >= f1){
		return f2;
	}
	else{
		return f3;
	}
}

float min(float f1, float f2, float f3){
        if(f1 <= f3 && f1 <= f2){
                return f1;
        }
        else if(f2 <= f3 && f2 <= f1){
                return f2;
        }
        else{
                return f3;
        }
}

Vector3 clip(Vector3 v){
	return (Vector3) {v.x, v.y, 0.0};
}

void Rasterize(Vector3 A, Vector3 B, Vector3 C){
	float a = A.z, b = B.z, c = C.z;
        A = clip(A);
	B = clip(B);
	C = clip(C);
        Vector3 P = Vector3CrossProduct(Vector3Subtract(A,C), Vector3Subtract(B,A));
        float area = Vector3Length(P);
	float maxX = max(A.x, B.x, C.x);
	float maxY = max(A.y, B.y, C.y);
	float minX = min(A.x, B.x, C.x);
	float minY = min(A.y, B.y, C.y);
	for(int i = minX; i <= maxX; i++){
		for(int j = minY; j <= maxY; j++){
		Vector3 st = {i, j, 0.0};
		Vector3 uVec = Vector3CrossProduct(Vector3Subtract(st,B), Vector3Subtract(C,st));
        	if(Vector3DotProduct(uVec, P) > 0){
                	continue;
		}
        	Vector3 vVec = Vector3CrossProduct(Vector3Subtract(st,C), Vector3Subtract(A,st));
        	if(Vector3DotProduct(vVec, P) > 0){
			continue;
		}
        	Vector3 wVec = Vector3CrossProduct(Vector3Subtract(st,A), Vector3Subtract(B,st));
        	if(Vector3DotProduct(wVec, P) > 0){
                	continue;
		}
        	float u = Vector3Length(uVec)/area;
        	float v = Vector3Length(vVec)/area;
        	float w = 1 - u - v;
		float inv_z = a * u + b * v + c * w;
		if(inv_z < z_buffer[j][i]){
			continue;
		}
		Color color = {u * 255, v * 255, w * 255, 255};
		DrawPixel(i, j, GREEN);
		z_buffer[j][i] = inv_z;
	}
        }
}

Vector3 NDCToScreen(Vector3 v, int screenWidth, int screenHeight){
	float newX = (v.x + 1) * screenWidth / 2;
	float newY = (1 - v.y) * screenHeight / 2;
	return (Vector3) {newX, newY, v.z};
}

Vector3 TranslateZ(Vector3 v, float dz){
	return (Vector3) {v.x, v.y, v.z + dz};
}

Vector3 Project(Vector3 v){
	return (Vector3) {v.x / v.z, v.y / v.z, v.z};
}

Vector3 RotateAlongY(Vector3 v, float angle){
	return (Vector3) {v.x * cos(angle) + v.z * sin(angle), v.y, v.z * cos(angle) - v.x * sin(angle)};
}

Vector3 RotateAlongZ(Vector3 v, float angle){
        return (Vector3) {v.x * cos(angle) + v.y * sin(angle), v.y * cos(angle) - v.x * sin(angle), v.z};
}

Vector3 VertexShader(Vector3 vertex){
	float distance = 200.0;
	float angle = GetTime() * 3.14 / 2;
	vertex = Project(TranslateZ(RotateAlongY(RotateAlongZ(vertex, (float) 3.14/16), angle), distance));
	return vertex;
}


int main(){
	const int screenWidth = 800;
        const int screenHeight = 800;
        InitWindow(screenWidth, screenHeight, "tinypixels");
	SetTargetFPS(60);
	Vector3 vertices[20000];
	int num_triangle_vertices = parse_obj("models/teapot.obj", vertices);
	while(!WindowShouldClose()){
		for(int i = 0; i < screenWidth; i++){
                for(int j = 0; j < screenHeight; j++){
                        z_buffer[j][i] = -10000;
                }
        }
		BeginDrawing();
		ClearBackground(BLACK);
		for(int i = 0; i < num_triangle_vertices; i+=3){
			Vector3 A = NDCToScreen(VertexShader(vertices[i]), screenWidth, screenHeight);
			Vector3 B = NDCToScreen(VertexShader(vertices[i+1]), screenWidth, screenHeight);
			Vector3 C = NDCToScreen(VertexShader(vertices[i+2]), screenWidth, screenHeight);
			Rasterize(A, B, C);
		}
		EndDrawing();
	}
	CloseWindow();
		
}
