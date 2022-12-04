#include <stdbool.h>
#include <stdio.h>


struct object
{
    Shape * shape;

    float x[2];
    float v[2];
    float a[2];

    float th;
    float w;
    float alp;

    float F[2];

    float inv_mass;
    float inv_inertia;

    float delw;
    float delv[2];

    bool stable;
    Material material;
};
typedef struct object Object;

struct material
{
    float restitution;
    float densit;
    float us;
    float uk;
    char number;
};
typedef struct material Material;

struct shape
{
    //size and normal vectors com ,edges
    int vertex_num;
    float **vertex;
    int *vertex_contact_index;
    bool *vertex_contact;
    float **normal;
    float volume;
    float inertia_constant;
    int number;
    int layer;
    float max_distance;
};typedef struct shape Shape;

#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <float.h>
#include "PEmath.h"




//물체의 물질 특성 밀도 마찰 등
struct material
{
    float restitution;  //반발 계수
    float density;      //밀도
    float us;           //정지 마찰계수
    float uk;           //운동 마찰계수
};
typedef struct material Material;


//물체의 형태에 관한 구조체
struct shape
{
    frShapeType type;
    Material material;
    bool isRect;
    float area;
    union {
        struct {
            float radius;
        } circle;
        struct {
            frVertices vertices;
            frVertices normals;
        } polygon;
    };
}; typedef struct shape Shape;

//물체 선언 완료

//강체의 물리량을 나타내는 구조체체

typedef struct object
{
    Shape* shape;

    Vector2 pos;  //좌표xy
    Vector2 vel;  //속도xy
    Vector2 acc;  //가속도xy

    float th;   //각도
    float thd;    //각속도
    float thdd;  //각가속도

    Vector2 Force;  //힘 2방향
    float Torque;  //토크

    float inv_mass;   //mass 인버스
    float inv_inertia;   //inertia 인버스

    float delw;   //각속도 변화량
    Vector2 delv;   //속도 변화량

    bool stable;     //안정성 유무
    Material material;
}object;

//충돌이 일어났을때 콜백 함수 생성

//원 생성


shape* createCircle(Material material, float radius);
//사각형 생성

shape* createRectanle(Material material, float width, float height);
//물체 선언 완료
