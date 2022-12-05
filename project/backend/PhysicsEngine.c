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
    mari_obj = generate_character(10, 300);
    maru_obj = generate_character(20, 10);
}

int main()
{
    PE_init();
    while (1)
    {
        calculatePose(ball, 9.8);
        int contact = CheckCollisionAnB(ball, mari_obj);
        if(contact = 1)
        {
            CheckImpulseAnB(ball, mari_obj);
            contact = 0;
        }
        ContactGround(ball);
        printf("ball pose x = %f y = %f contact = %d\n", ball->pos.x, ball->pos.y, contact);
        printf("mari_obj pose x = %f y = %f contact = %d\n", mari_obj->pos.x, mari_obj->pos.y, contact);
        sleep(1);
    }
}