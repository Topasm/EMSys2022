#include "PEobject.h"




bool AabbAabbIntersection(Aabb a, Aabb b)
{
    if (a.max.x < b.min.x || a.min.x > b.max.x) return 0;
    if (a.max.y < b.min.y || a.min.y > b.max.y) return 0;
    if (a.max.z < b.min.z || a.min.z > b.max.z) return 0;
    return 1;
}
//충돌 방향마다 검출하기
