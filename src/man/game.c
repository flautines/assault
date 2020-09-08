#include "game.h"
#include <man/entity.h>
#include <man/entity_templates.h>
#include <man/lives.h>
#include <sys/physics.h>
#include <sys/render.h>
#include <sys/ai.h>
#include <sys/animation.h>
#include <sys/collisions.h>

u8 m_lane_status[3];
u8 m_player_shot;
u8 m_enemy_shot;

/////////////////////////////////////////////////////////////////////////////
void wait(u8 n)
{
	do {
		cpct_waitHalts(n);
		cpct_waitVSYNC();
	} while (--n);
}

/////////////////////////////////////////////////////////////////////////////
Entity_t *manGameCreateFromTemplate(const Entity_t *tmpl)
{
	Entity_t *e = manEntityCreate();
	cpct_memcpy (e, tmpl, sizeof (Entity_t));
	return e;
}

/////////////////////////////////////////////////////////////////////////////
int manGameCreateEnemy(Entity_t *e)
{
	Entity_t *e_spawn;
	u8 x;

	// No enemy created
	if (m_lane_status[2] != 0) return 0;

	// Spawn rays
	e_spawn = manGameCreateFromTemplate(&spawn_ray_tmpl);
	x = e->x;
	x += 5;
	e_spawn->x = x;
	// Create minion
	{
		e_spawn = manGameCreateFromTemplate (&enemy01_tmpl);
		x -= 2;
		e_spawn->x = x;
		e_spawn->vx = e->vx;
	}

	// Mark enemy is on lane
	m_lane_status[2] = 1;

	// Return enemy created
	return 1;
}

/////////////////////////////////////////////////////////////////////////////
void manGameInit()
{
	manEntityInit();
	manLivesInit();
	sysRenderInit();
	sysAIInit();

	// Nave nodriza
	manGameCreateFromTemplate (&nave_nodriza_tmpl);

	cpct_memset (m_lane_status, 0, sizeof(m_lane_status));
	m_player_shot = 0;

	manGameCreateFromTemplate(&jugador_tmpl);

  // Puntuacion
  /*
  {
	Entity_t num;
	u8 d = 6;
	do {
	  --d;
	  cpct_memcpy(&num, &num_tmpl, sizeof(Entity_t));
	  num.sprite += d * SPR_NUMEROS_00_H * SPR_NUMEROS_00_W;
	  num.x += d * (SPR_NUMEROS_00_W+2);
	  manGameCreateFromTemplate(&num);

	} while (d);

  }
  */
}

/////////////////////////////////////////////////////////////////////////////
int manGameGetEnemyLane(Entity_t *e)
{
	u8 lane = 2;
	if ( e->y > LANE1_Y ) lane = 0;
	else if ( e->y > LANE2_Y ) lane = 1;
	return lane;
}

void manGameEnemyLaneDown(Entity_t *e)
{
	u8 lane = manGameGetEnemyLane(e);
	if (lane == 0) return;

	// Check lane empty first
	if ( m_lane_status[lane-1] ) return;

	// Create phantom entity to erase trail
	{
	Entity_t *e_trail = manEntityClone(e);
	e_trail->components = E_COMPONENT_RENDER;
	manEntityDelete(e_trail);
	}
	// Go down
	e->y += LANE_DY;
	m_lane_status[lane  ] = 0;
	m_lane_status[lane-1] = 1;
}

/////////////////////////////////////////////////////////////////////////////
void manGameEntityDestroy(Entity_t *e)
{
	if (e->type == E_TYPE_SHOT) {
		m_player_shot = 0;
	}

	if (e->type == E_TYPE_ENEMY_SHOT) {
		m_enemy_shot = 0;
	}

	if (e->type == E_TYPE_ENEMY) {
		u8 lane = manGameGetEnemyLane(e);
		m_lane_status[lane] = 0;
	}

	if (e->type == E_TYPE_PLAYER) {
		manLivesChange(-1);
	}

	if (e->type != E_TYPE_PLAYER) {
		manEntityDelete(e);
	}
	
}

/////////////////////////////////////////////////////////////////////////////
void manGamePlayerShoot(Entity_t *player)
{
  // We can't shoot more than one bullet at a time
	if (m_player_shot != 0) return;

  {
	Entity_t *shot = manGameCreateFromTemplate(&player_shot_tmpl);
	shot->x = player->x + 2;
  }
	m_player_shot = 1;
}

/////////////////////////////////////////////////////////////////////////////
void manGameEnemyShoot(Entity_t *enemy)
{
	if (m_enemy_shot) return;
	else {
		// Only the enemy @ lower lane can shoot
		u8 lane = manGameGetEnemyLane(enemy);
		if ( lane == 0) {
		
			Entity_t *shot = manGameCreateFromTemplate(&enemy_shot_tmpl);
			shot->y = enemy->y + SPR_ENEMIGO_01_0_H-1;
			shot->x = enemy->x + 5;
			m_enemy_shot = 1;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
void manGamePlay()
{
  while (1) {
	sysAIUpdate();
	sysPhysicsUpdate();
	sysAnimationUpdate();
	sysCollisionsUpdate();
	sysRenderUpdate();
	manEntityUpdate();
	manLivesUpdate();
	wait(1);
  }
}