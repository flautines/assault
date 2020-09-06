#include "game.h"
#include <man/entity.h>
#include <man/entity_templates.h>
#include <sys/physics.h>
#include <sys/render.h>
#include <sys/ai.h>
#include <sys/animation.h>
#include <sys/collisions.h>

u8 m_lane_status[3];  
u8 m_player_shot;

/*------------------------------------
const Entity_t nave_nodriza_tmpl = {
  E_COMPONENT_MOVABLE | E_COMPONENT_RENDER |  // type
  E_COMPONENT_AI,
  38, 18,                           // x, y   
  SPR_NAVE_NODRIZA_W,               // w         
  SPR_NAVE_NODRIZA_H,               // h         
  -1,  0,  1,                       // vx, vy, move_counter                                
  spr_nave_nodriza,                 // sprite       
  sysAIBehaviorMotherShip,          // ai_behavior               
  0x0000, 0,                        // anim, anim_counter
  0,                                // current_frame  
};
const Entity_t enemy01_tmpl = {
  E_COMPONENT_MOVABLE | E_COMPONENT_RENDER |  // type
  E_COMPONENT_AI | E_COMPONENT_ANIM,  
  0, 18+SPR_NAVE_NODRIZA_H+14,      // x, y
  SPR_ENEMIGO_01_0_H,               // w
  SPR_ENEMIGO_01_0_H,               // h
  -1, 0,  1,                        // vx, vy, move_counter
  spr_enemigo_01_0,                 // sprite
  sysAIBehaviorLeftRight,           // ai_behavior
  animEnemy01, 12,                  // anim, anim_counter
  0,                                // current_frame
};
const Entity_t nave_vidas_tmpl = {
  E_COMPONENT_RENDER,                    // type           
  0, 192,                           // x, y
  SPR_NAVE_JUGADOR_1_W,             // w
  SPR_NAVE_JUGADOR_1_H,             // h
  0,  0,  0,                        // vx, vy, move_counter
  spr_nave_jugador_1,               // sprite
  0x0000,                           // ai_behavior
  0x0000, 0,                        // anim, anim_counter
  0,                                // current_frame
};
const Entity_t jugador_tmpl = {
  E_COMPONENT_MOVABLE | E_COMPONENT_INPUT |   // type
  E_COMPONENT_RENDER,                    
  38, 176,                          // x, y
  SPR_NAVE_JUGADOR_0_W,             // w
  SPR_NAVE_JUGADOR_0_H,             // h
  0,  0,  0,                        // vx, vy, move_counter
  spr_nave_jugador_0,               // sprite
  0x0000,                           // ai_behavior
  0x0000, 0 ,                       // anim, anim_counter
  0,                                // current_frame
};
const Entity_t num_tmpl = {
  E_COMPONENT_RENDER,                    // type
  24, 0,                            // x, y
  SPR_NUMEROS_00_W,                 // w
  SPR_NUMEROS_00_H,                 // h
  0,  0,  0,                        // vx, vy
  spr_numeros_00,                   // sprite
  0x0000,                           // ai_behavior
  0x0000, 0,                        // anim, anim_counter
  0,                                // current_frame
};
*/
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
void manGameCreateEnemy(Entity_t *e)
{
  if (m_lane_status[2] != 0) return;

  // Create minion
  {
    Entity_t *minion = manGameCreateFromTemplate (&enemy01_tmpl);
    minion->x = e->x+4;
    minion->vx = e->vx;
  }

  // Mark enemy is on lane
  m_lane_status[2] = 1;
}

/////////////////////////////////////////////////////////////////////////////
void manGameInit()
{
  manEntityInit();
  sysRenderInit();
  sysAIInit();

  // Nave nodriza  
  manGameCreateFromTemplate (&nave_nodriza_tmpl);

  cpct_memset (m_lane_status, 0, sizeof(m_lane_status));
  m_player_shot = 0;

  // Vidas
/*  
  {
  u8 x = 30;
  do {
      Entity_t *e = 
        manGameCreateFromTemplate (&nave_vidas_tmpl);
      x -= 10;
      e->x = x;
  } while (x);
  }
*/
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
  /*
  u8 lane = 2;
  if ( e->y > LANE1_Y ) return;
  else if ( e->y > LANE2_Y ) lane = 1;
  */
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

  if (e->type == E_TYPE_ENEMY) {
    u8 lane = manGameGetEnemyLane(e);
    m_lane_status[lane] = 0;
  }

  manEntityDelete(e);
}

/////////////////////////////////////////////////////////////////////////////
void manGamePlayerShot(Entity_t *player)
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
void manGamePlay()
{
  while (1) {
    sysAIUpdate();
    sysPhysicsUpdate();
    sysAnimationUpdate();
    sysCollisionsUpdate();
    sysRenderUpdate();
    manEntityUpdate();
    wait(1);
  }
}