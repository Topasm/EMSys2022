#include "PEobject.h"
#include "PEcollide.h"



int CheckCollisionAnB(object* a, object* b)
{
    float ax_h = a->size.x/2;
    float ay_h = a->size.y/2;
    float bx_h = b->size.x/2;
    float by_h = b->size.y/2;

    if (a->pos.x+ax_h < b->pos.x - bx_h|| a->pos.x- ax_h > b->pos.x+ bx_h) return 0;
    if (a->pos.y+ay_h < b->pos.y - by_h|| a->pos.y- ay_h > b->pos.y+ by_h) return 0;
    return 1;
}


int CheckImpulseAnB(object* a, object* b)
{
    float mass1 = 2;
    // float mass2 = 0.01;
    int state = 0;
    
    a->vel.x = mass1*b->vel.x;
    a->vel.y = -a->vel.y;


   

    printf("objec collide\n%f",a->vel.y);
    
}


//충돌 방향마다 검출하기
