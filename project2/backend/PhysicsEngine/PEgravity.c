int m_g = 9.81;

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "PErigidbody.h"
#include "PEmath.h"

#define STRUCT_ZERO(T) ((T){0})

float calculateGravity(object *mass)
{
    float gravity = 9.81;
    float dropSpeed = 0.0;
    dropSpeed += gravity;
    mass->pos.y += dropSpeed;
    return mass->pos.y;
}

void Constraint()
{
    const Vector2 position = {212, 123};
}

void update()
{
    for (int i = 0; i < (int)body.size(); ++i)
    {
        object *b = bodies[i];

        b->pos += timeStep * b->vel;
        b->th += timeStep * b->thd;

        b->Force.STRUCT_ZERO;
        b->Torque = 0.0f;
    }
}

void Set

    //필요한거 바닥 충도
    void
    main()
{
    object *ball;
    ball = (object *)malloc(sizeof(object));
    ball->pos.y = 0;
    float position = 0;
    while (1)
    {
        position = calculateGravity(ball);

        printf("position y = %f\n", position);
        Sleep(100);
    }
}