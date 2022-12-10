
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "PEobject.h"

#define STRUCT_ZERO(T) ((T){0})

void calculateG(object *mass, float gravity)
{
    mass->acc.y = gravity;
    mass->vel.y += gravity;
}

void calculateP(object *mass)
{
    
    mass->pos.y += mass->vel.y;
    mass->pos.x += mass->vel.x;
    //return mass->pos.y;
}

void ContactGround(object *a, float elastic)
{
    if (a->pos.y > 350)
    {
        if (a->vel.y < 0.1)
        {
            a->vel.y = 0;
            a->pos.y = 350;
        }
        a->vel.y *= -elastic;
        printf("contact%f", a->vel.y);
    }
    // else
    // {
    //     a->vel.y = 0;
    //     a->pos.y = 400;
    // }
}

// player 변수
// int x1 = 0, x2 = 520; //초기위치

void CharContactEdge(object *a, object *b)
{

    // mari
    if (a->pos.x >= 240) // not to over net
    {
        printf("mari saturation\n");
        a->vel.x = 0;
        a->pos.x = 295;
    }

    else if (a->pos.x <= 0) // not to over left wall
    {
        printf("mari saturation\n");
        a->vel.x = 0;
        a->pos.x = 0;
        ;
    }
    // maru
    if (b->pos.x <= 520) // not to over net
    {
        printf("maru saturation\n");
        b->vel.x = 0;
        b->pos.x = 620;
    }

    else if (b->pos.x >= 830) // not to over right wall
    {
        printf("maru saturation\n");
        b->vel.x = 0;
        b->pos.x = 830;
    }
}

void ballContactEdge(object *ball)
{

    if (ball->pos.x <= 0) // not to over left wall
    {
        printf("mari saturation\n");
        ball->vel.x *= -1;
    }

    if (ball->pos.x >= 830) // not to over right wall
    {
        printf("maru saturation\n");
        ball->vel.x *= -1;
    }
}

// void ContactEdges();
