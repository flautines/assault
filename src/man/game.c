#include "game.h"
#include <man/entity.h>
#include <man/animation.h>
#include <sys/physics.h>
#include <sys/render.h>
#include <sys/ai.h>
#include <sys/animation.h>
#include <sprites/nave_nodriza_01.h>
#include <sprites/nave_jugador.h>
#include <sprites/numeros.h>
#include <sprites/enemigo_01.h>

u8 enemy_on_lane;

/*------------------------------------*/
const Entity_t nave_nodriza_tmpl = {
  E_TYPE_MOVABLE | E_TYPE_RENDER |  // type
  E_TYPE_AI,
  38, 18,                           // x, y   
  SPR_NAVE_NODRIZA_W,               // w         
  SPR_NAVE_NODRIZA_H,               // h         
  -1,  0,                           // vx, vy   
  spr_nave_nodriza,                 // sprite       
  sysAIBehaviorMotherShip,          // ai_behavior               
  0x0000, 0                         // anim
  
};
const Entity_t enemy01_tmpl = {
  E_TYPE_MOVABLE | E_TYPE_RENDER |  // type
  E_TYPE_AI | E_TYPE_ANIM,  
  0, 18+SPR_NAVE_NODRIZA_H+14,      // x, y
  SPR_ENEMIGO_01_0_H,               // w
  SPR_ENEMIGO_01_0_H,               // h
  -1,  0,                           // vx, vy
  spr_enemigo_01_0,                 // sprite
  sysAIBehaviorLeftRight,           // ai_behavior
  animEnemy01, 12                    // anim
};
const Entity_t nave_vidas_tmpl = {
  E_TYPE_RENDER,                    // type           
  0, 192,                           // x, y
  SPR_NAVE_JUGADOR_1_W,             // w
  SPR_NAVE_JUGADOR_1_H,             // h
  0,  0,                            // vx, vy
  spr_nave_jugador_1,               // sprite
  0x0000,                           // ai_behavior
  0x0000, 0                         // anim
};
const Entity_t jugador_tmpl = {
  E_TYPE_MOVABLE | E_TYPE_INPUT |   // type
  E_TYPE_RENDER,                    // x, y
  38, 176,                          // w
  SPR_NAVE_JUGADOR_0_W,             // h
  SPR_NAVE_JUGADOR_0_H,             // vx, vy
  0,  0,                            // sprite
  spr_nave_jugador_0,               // ai_behavior
  0x0000, 0                         // anim
};
const Entity_t num_tmpl = {
  E_TYPE_RENDER,                    // type
  24, 0,                            // x, y
  SPR_NUMEROS_00_W,                 // w
  SPR_NUMEROS_00_H,                 // h
  0,  0,                            // vx, vy
  spr_numeros_00,                   // sprite
  0x0000,                           // ai_behavior
  0x0000, 0                         // anim
};
/**************************************/
void wait(u8 n)
{
  do {
      cpct_waitHalts(n);
      cpct_waitVSYNC();
  } while (--n);
}
/**************************************/
Entity_t *manGameCreateFromTemplate(const Entity_t *tmpl)
{
  Entity_t *e = manEntityCreate();
  cpct_memcpy (e, tmpl, sizeof (Entity_t));
  return e;    
}
/**************************************/
void manGameCreateEnemy(Entity_t *e)
{
  if (enemy_on_lane) return;

  // Create minion
  {
    Entity_t *minion = manGameCreateFromTemplate (&enemy01_tmpl);
    minion->x = e->x+4;
    minion->vx = e->vx;
  }

  // Mark enemy is on lane
  enemy_on_lane = 1;
}
/**************************************/
void manGameInit()
{
  manEntityInit();
  sysRenderInit();

  // Nave nodriza  
  manGameCreateFromTemplate (&nave_nodriza_tmpl);

  enemy_on_lane = 0;

  // Vidas
  {
  u8 x = 30;
  do {
      Entity_t *e = 
        manGameCreateFromTemplate (&nave_vidas_tmpl);
      x -= 10;
      e->x = x;
  } while (x);
  }

  manGameCreateFromTemplate(&jugador_tmpl);

  // Puntuacion
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
}
/**************************************/
void manGamePlay()
{
  while (1) {
    sysAIUpdate();
    sysPhysicsUpdate();
    sysAnimationUpdate();
    sysRenderUpdate();
    manEntityUpdate();
  }
}
