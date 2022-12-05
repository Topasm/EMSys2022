
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "PEobject.h"

#define STRUCT_ZERO(T) ((T){0})

float calculateGravity(object *mass)
{
    float gravity = 9.81;
    float dropSpeed = 0.0;
    dropSpeed += gravity;
    mass->pos.y += dropSpeed;
    return mass->pos.y;
}

// void Constraint()
// {
//     const Vector2 position = {212, 123};
// }


// void ContactGround();

// void ContactEdges();
