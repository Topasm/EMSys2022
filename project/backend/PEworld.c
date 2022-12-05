
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

inline PEVector2 mul(float a, PEVector2 v)
{
    return (PEVector2) { v.x * a, v.y * a };
}

void ContactGround(object *a)
{
    if(a->pos.y>400)
    {
        a->vel.y*=-0.8;
        printf("contact%d", a->pos.x);

    }
}

// void ContactEdges();
