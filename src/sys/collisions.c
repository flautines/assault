#include <man/entity.h>
#include <man/game.h>
#include "collisions.h"

int overlapping(u8 minA, u8 maxA, u8 minB, u8 maxB)
{
    return minB <= maxA && minA <= maxB;
}

int aabb_collide(Entity_t *e1, Entity_t *e2)
{
    u8 aLeft = e1->x;
    u8 aRight = aLeft + e1->w;
    u8 bLeft = e2->x;
    u8 bRight = bLeft + e2->w;

    u8 aTop = e1->y;
    u8 aBottom = aTop + e1->h;
    u8 bTop = e2->y;
    u8 bBottom = bTop + e2->h;

    return overlapping(aLeft, aRight, bLeft, bRight) 
        && overlapping(aTop, aBottom, bTop, bBottom);
}

void sysCollisionsUpdateEntityPairs(Entity_t *e1, Entity_t *e2)
{
    u8 e1_collides_with_e2 = e1->collides_with & e2->type;
    u8 e2_collides_with_e1 = e2->collides_with & e1->type;
    if (e1_collides_with_e2 || e2_collides_with_e1) {
        
        if ( aabb_collide(e1, e2) ) {

            u8 e_type = e1_collides_with_e2 ? e1->type : e2->type;
            if (e_type & E_TYPE_SHOT) {
                manGameEntityDestroy(e1);
                manGameEntityDestroy(e2);
            }
        }
        //return;
    }
}

void sysCollisionsUpdate()
{
    manEntityForAllPairsMatching(
        sysCollisionsUpdateEntityPairs, 
        E_COMPONENT_COLLIDE);
}

