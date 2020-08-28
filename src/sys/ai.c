#include "ai.h"
#include <man/entity.h>
#include <man/game.h>

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

  sysAIBehaviorLeftRight(e);
  
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
