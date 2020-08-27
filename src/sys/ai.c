#include "ai.h"
#include <man/entity.h>

/**************************************/
void sysAIUpdateEntity(Entity_t *e)
{
  const u8 rbound = 80 - e->w;
  if (e->x == 0)      e->vx =  1;
  if (e->x == rbound) e->vx = -1;
}
/**************************************/
void sysAIUpdate()
{
  manEntityForAllMatching(
      sysAIUpdateEntity, 
      E_TYPE_MOVABLE | E_TYPE_AI);
}
