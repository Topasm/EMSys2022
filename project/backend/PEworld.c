
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "PEobject.h"

#define STRUCT_ZERO(T) ((T){0})

float calculatePose(object *mass, float gravity)
{
    mass->acc.y = gravity;
    mass->vel.y += gravity;
    mass->pos.y += mass->vel.y;
    return mass->pos.y;
}


void ContactGround(object *a, float elastic)
{
    if(a->pos.y>400 && a->vel.y>0)
    {
        if(a->vel.y<1)
        {
            a->vel.y+=2;
        }
        a->vel.y*=-elastic;
        printf("contact%d", a->pos.x);

    }
}

// void ContactEdges();
