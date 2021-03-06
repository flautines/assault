#include "ai.h"
#include <man/entity.h>
#include <man/game.h>
#include <sys/physics.h>

u8 updown;

/**************************************/
void sysAIBehaviorLeftRight(Entity_t *e)
{
  const u8 rbound = 80 - e->w;
  if (e->x == 0)      e->vx =  1;
  if (e->x == rbound) e->vx = -1;
}
void sysAIBehaviorMotherShip(Entity_t *e)
{
  if (e->x == 20) {
    manGameCreateEnemy (e);
  }

  // Every 16 frames go up or down
  if ( (e->current_frame&15) == 0 ) {
    sysPhysicsUpDown(e, updown);
    updown ^= 1;
  }
  sysAIBehaviorLeftRight(e);
  
}

/**************************************/
void sysAIInit()
{
  updown = 0;
}
/**************************************/
void sysAIUpdateEntity(Entity_t *e)
{
  e->ai_behavior(e);
}
/**************************************/
void sysAIUpdate()
{
  manEntityForAllMatching(
      sysAIUpdateEntity, 
      E_TYPE_MOVABLE | E_TYPE_AI);
}
