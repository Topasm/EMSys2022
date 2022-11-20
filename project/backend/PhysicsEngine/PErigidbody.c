#include <stdbool.h>
#include <stdio.h>


struct object
{
    Shape * shape;

    float x[2];
    float v[2];
    float a[2];

    float th;
    float w;
    float alp;

    float F[2];

    float inv_mass;
    float inv_inertia;

    float delw;
    float delv[2];

    bool stable;
    Material material;
};
typedef struct object Object;

struct material
{
    float restitution;
    float densit;
    float us;
    float uk;
    char number;
};
typedef struct material Material;

struct shape
{
    //size and normal vectors com ,edges
    int vertex_num;
    float **vertex;
    int *vertex_contact_index;
    bool *vertex_contact;
    float **normal;
    float volume;
    float inertia_constant;
    int number;
    int layer;
    float max_distance;
};typedef struct shape Shape;

//물체 선언 완료
