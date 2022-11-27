#pragma once
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <float.h>

#define PI = 3.14159265358979323846264f;

// the Minimum Value is Returned
#define min(a,b) ((a > b)? (b) : (a))
// the Maximum value is Returned
#define max(a,b) ((a < b)? (b) : (a))


//2차원 벡터 자료형 구현
typedef struct Vector2 {
	float x, y;
}Vector2;

//사각형 자료형 구현
typedef struct Rectangle {
	float x;
	float y;
	float width;
	float height;
} Rectangle;

/*2차원 좌표 이동 행렬
[rot tans]
[ 0    1 ]*/

typedef struct Transform {
	Vector2 position;
	float rotation;
	struct {
		bool valid;
		float sinA;
		float cosA;
	} cache;
} Transform;

inline float DotProduct(Vector2 v1, Vector2 v2) {
	return (v1.x * v2.x) + (v1.y * v2.y);
}


/* Rotates `v` around the origin. */
inline Vector2 Vec2Rotate(Vector2 v, float angle) {
	const float sinA = sinf(angle);
	const float cosA = cosf(angle);

	return (Vector2) { (v.x * cosA - v.y * sinA), (v.x * sinA + v.y * cosA) };
}