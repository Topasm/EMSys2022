#include "PEobject.h"




int CheckCollisionAnB(object* a, object* b)
{
    int ax_h = a->size.x/2;
    int ay_h = a->size.y/2;
    int bx_h = b->size.x/2;
    int by_h = b->size.y/2;

    if (a->pos.x+ax_h < b->pos.x - bx_h|| a->pos.x- ax_h > b->pos.x+ bx_h) return 0;
    if (a->pos.y+ay_h < b->pos.y - by_h|| a->pos.y- ay_h > b->pos.y+ by_h) return 0;
    return 1;
}


int CheckImpulseAnB(object* a, object* b)
{
    PEVector2 bvel = b->vel;
    PEVector2 avel = a->vel;
    float mass1 = 1;
    float mass2 = 0.01;
    a->vel.x = -mass1*avel.x;
    a->vel.y = -mass1*avel.y;
    b->vel.x = -mass2*bvel.x;
    b->vel.y = -mass2*bvel.y;

    printf("objec collide\n");
    
}


//충돌 방향마다 검출하기
