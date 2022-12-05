#include <stdbool.h>
#include <stdio.h>
#include <float.h>
#define MAX_VERTEX_COUNT 3

//물체 선언 완료

//강체의 물리량을 나타내는 구조체체
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <float.h>

// the Minimum Value is Returned
#define min(a, b) ((a > b) ? (b) : (a))
// the Maximum value is Returned
#define max(a, b) ((a < b) ? (b) : (a))

typedef struct
{
    float x;
    float y;
} PEVector2;


typedef struct
{
    PEVector2 vertices[MAX_VERTEX_COUNT]; //꼭짓점 배열
    PEVector2 normals[MAX_VERTEX_COUNT];  //법선 벡터 배열
    int count;                            //꼭짓점 갯수
} Polygon;

typedef struct
{
    PEVector2 pos;   //좌표xy
    PEVector2 vel;   //속도xy
    PEVector2 acc;   //가속도xy
    PEVector2 Force; //힘 2방향
    float inv_mass;  // mass 인버스
    bool stable;     //안정성 유무
    Polygon poly;
} object;

object *generate_ball(float x, float y);

object *generate_character(float x, float y);

//충돌이 일어났을때 콜백 함수 생성
