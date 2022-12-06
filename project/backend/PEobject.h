#include <stdbool.h>
#include <stdio.h>
#include <float.h>
#include <math.h>


typedef struct
{
    float x;
    float y;
} PEVector2;



typedef struct
{
    PEVector2 pos;   //좌표xy
    PEVector2 vel;   //속도xy
    PEVector2 acc;   //가속도xy
    PEVector2 Force; //힘 2방향
    float inv_mass;  // mass 인버스
    bool stable;     //안정성 유무
    PEVector2 size; //크기
} object;

object *generate_ball(float x, float y);

object *generate_character(float x, float y);

//충돌이 일어났을때 콜백 함수 생성
