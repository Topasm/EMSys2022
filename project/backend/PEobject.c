#include "PEobject.h"
float DotProduct(PEVector2 v1, PEVector2 v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y);
}
object* generate_ball(float x, float y)
{
    object *ball;
    ball = (object *)malloc(sizeof(object));
    ball->pos.x = x;
    ball->pos.y = y;
    ball->inv_mass = 0.6;
    ball->poly.count=4;
    ball->poly.normals[0] = {0,1,1,0,0,-1,-1,0};
    return (object*)ball;
}

object* generate_character(float x, float y)
{
    object *character;
    character = (object *)malloc(sizeof(object));
    character->pos.x = x;
    character->pos.y = y;
   
    character->inv_mass = 0.1;
    character->poly.count=4;

    return (object*)character;
}

typedef struct Rectangle {
	float x;
	float y;
	float width;
	float height;
} Rectangle;
