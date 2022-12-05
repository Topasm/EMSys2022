#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "PEobject.h"
#include "PEworld.h"

object *ball;
object *mari_obj;
object *maru_obj;

void PE_init()
{
    ball = generate_ball(10.0, 0.0);
    mari_obj = generate_character(10, 10);
    maru_obj = generate_character(20, 10);
}

int main()
{
    PE_init();
    while (1)
    {
        calculateGravity(ball);
        printf("ball pose x = %f y = %f\n", ball->pos.x, ball->vel.y);
        sleep(1);
    }
}