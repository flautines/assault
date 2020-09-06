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
/**************************************/
void sysAIBehaviorMotherShip(Entity_t *e)
{
  if ( (e->x & 7) == 0 ) {
    manGameCreateEnemy (e);
  }

  if ( (e->current_frame&15) == 0 ) {
    sysPhysicsUpDown(e, updown);
    updown ^= 1;
  }
  sysAIBehaviorLeftRight(e);
  
}
/**************************************/
void sysAIBehaviorChangeDir(Entity_t *e)
{  
  if (cpct_rand() < 20) {
    e->vx = -(e->vx);
  }
}

void sysAIBehaviorEnemy01(Entity_t *e)
{
  if ( (e->x & 7) == 0 ) {
    manGameEnemyLaneDown(e);
  }
  if ( (e->x &15)  == 0) {
    sysAIBehaviorChangeDir(e);
  }

  sysAIBehaviorLeftRight(e); 
}
/**************************************/
void sysAIBehaviorAutoDestroy(Entity_t *e)
{
  if ( --(e->ai_counter) == 0 ) {
    manGameEntityDestroy(e);
  }
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
      E_COMPONENT_MOVABLE | E_COMPONENT_AI);
}