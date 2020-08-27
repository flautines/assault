#include "physics.h"
#include <man/entity.h>
#include <cpctelera.h>

/**************************************/
void sysPhysicsCheckKeyboard(Entity_t *e)
{
    cpct_scanKeyboard_f();
    e->vx = 0;
    if      (cpct_isKeyPressed(Key_O)) e->vx = -1;
    else if (cpct_isKeyPressed(Key_P)) e->vx = +1;
}
/**************************************/
void sysPhysicsUpdateEntity(Entity_t *e) {
  
    if (e->type & E_TYPE_INPUT)
        sysPhysicsCheckKeyboard(e);
    {
    i8 vx= e->vx;
    e->x += vx;  
    e->y += e->vy;
    }
}

void sysPhysicsUpdate() 
{
  manEntityForAllMatching (
        sysPhysicsUpdateEntity, 
        E_TYPE_MOVABLE);
}
