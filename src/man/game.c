#include "game.h"
#include <man/entity.h>
#include <sys/physics.h>
#include <sys/render.h>
#include <sys/ai.h>
#include <sprites/nave_nodriza_01.h>
#include <sprites/nave_jugador.h>
#include <sprites/numeros.h>

/*------------------------------------*/
const Entity_t nave_nodriza_tmpl = {
  E_TYPE_MOVABLE | E_TYPE_RENDER | E_TYPE_AI,
  38, 18,
  SPR_NAVE_NODRIZA_W,
  SPR_NAVE_NODRIZA_H,
  -1,  0,
  spr_nave_nodriza,
};
const Entity_t nave_marcador_tmpl = {
  E_TYPE_RENDER,
  0, 192,
  SPR_NAVE_JUGADOR_1_W,
  SPR_NAVE_JUGADOR_1_H,
  0,  0,
  spr_nave_jugador_1,
};
const Entity_t jugador_tmpl = {
  E_TYPE_MOVABLE | E_TYPE_INPUT | E_TYPE_RENDER,
  38, 176,
  SPR_NAVE_JUGADOR_0_W,
  SPR_NAVE_JUGADOR_0_H,
  0,  0,
  spr_nave_jugador_0,
};
const Entity_t num_tmpl = {
  E_TYPE_RENDER,
  24, 0,
  SPR_NUMEROS_00_W,
  SPR_NUMEROS_00_H,
  0,  0,
  spr_numeros_00,
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
void manGameInit()
{
  manEntityInit();
  sysRenderInit();
    
  manGameCreateFromTemplate (&nave_nodriza_tmpl);

  // Vidas
  {
  u8 x = 30;
  do {
      Entity_t *e = 
        manGameCreateFromTemplate (&nave_marcador_tmpl);
      x -= 10;
      e->x = x;
  } while (x);
  }

  manGameCreateFromTemplate(&jugador_tmpl);

  // Marcador
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
    sysRenderUpdate();
    manEntityUpdate();
  }
}
