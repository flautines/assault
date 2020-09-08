#include "physics.h"
#include <man/game.h>
#include <man/entity.h>
#include <cpctelera.h>

/////////////////////////////////////////////////////////////////////////////
void sysPhysicsCheckKeyboard(Entity_t *e)
{
	const u8 rbound = 80 - e->w - 10;
	const u8 lbound = 4;

    cpct_scanKeyboard_f();
    e->vx = 0;
    if      (cpct_isKeyPressed(Key_O) && e->x > lbound) e->vx = -1;
    else if (cpct_isKeyPressed(Key_P) && e->x < rbound) e->vx = +1;

    // Check for shoot action
    if (cpct_isKeyPressed(Key_Space))
        manGamePlayerShoot(e);
}

/////////////////////////////////////////////////////////////////////////////
void sysPhysicsUpdateEntity(Entity_t *e) {
    u8 current_frame = e->current_frame;
    u8 move_counter = e->move_counter;
    
    if (e->components & E_COMPONENT_INPUT)
        sysPhysicsCheckKeyboard(e);
    
    if ( (current_frame & move_counter) == 0 )
    {
        i8 vx= e->vx;
        e->x += vx;  
        e->y += e->vy;
    }
    ++current_frame;
    e->current_frame = current_frame;
}

/////////////////////////////////////////////////////////////////////////////
void sysPhysicsUpdate() 
{
  manEntityForAllMatching (
        sysPhysicsUpdateEntity, 
        E_COMPONENT_MOVABLE);
}
