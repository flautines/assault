#include "ai.h"
#include <man/entity.h>
#include <man/entity_templates.h>
#include <man/game.h>
#include <sys/physics.h>

i8 vdir;
u8 vframes;

////////////////////////////////////////////////////////////////////////////
void sysAIBehaviorUpDown(Entity_t *e)
{	
	if (e->ai_counter != 0) return;
	if ( (e->current_frame&15) == 0 ) {
		e->vy = vdir;
		vdir = -vdir;
	}

	if (--vframes == 0) {
		e->vy = 0;
		vframes = 4;
	}
}

/////////////////////////////////////////////////////////////////////////////
void sysAIBehaviorLeftRight(Entity_t *e)
{
	const u8 rbound = 80 - e->w;
	if (e->x == 0)      e->vx =  1;
	if (e->x == rbound) e->vx = -1;
}

/////////////////////////////////////////////////////////////////////////////
void sysAIBehaviorMotherShip(Entity_t *e)
{
	sysAIBehaviorUpDown(e);

	if ( (e->current_frame&15) == 0 ) {
		if ( e->y == MOTHERSHIP_Y-2 && e->ai_counter == 0 && manGameCreateEnemy (e) ) {
			e->ai_counter = 8;
			e->components &= ~E_COMPONENT_MOVABLE;
		}
	}

	sysAIBehaviorLeftRight(e);			
	if (e->ai_counter != 0) {
		--(e->ai_counter);
		if (e->ai_counter == 0)
			e->components |= E_COMPONENT_MOVABLE;
	}
}

/////////////////////////////////////////////////////////////////////////////
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
    
    if ( cpct_rand() < 5) {
        manGameEnemyShoot(e);
    }

	sysAIBehaviorLeftRight(e);
}

/////////////////////////////////////////////////////////////////////////////
void sysAIBehaviorEnemyShot(Entity_t *e)
{
    if ( e->y >= PLAYER_Y-9) {
        manGameEntityDestroy(e);
    }
}

/////////////////////////////////////////////////////////////////////////////
void sysAIBehaviorAutoDestroy(Entity_t *e)
{
	if ( --(e->ai_counter) == 0 ) {
		manGameEntityDestroy(e);
	}
}

/////////////////////////////////////////////////////////////////////////////
void sysAIUpdateEntity(Entity_t *e)
{
	e->ai_behavior(e);
}

/////////////////////////////////////////////////////////////////////////////
void sysAIInit()
{
	vdir = -1;
	vframes = 4;
}

/////////////////////////////////////////////////////////////////////////////
void sysAIUpdate()
{
    manEntityForAllMatching(
        sysAIUpdateEntity,
        E_COMPONENT_AI);
}