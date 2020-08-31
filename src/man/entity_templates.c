#include <man/entity.h>
#include <man/animation.h>
#include <sys/ai.h>
#include <sys/animation.h>
#include <sprites/nave_nodriza_01.h>
#include <sprites/nave_jugador.h>
#include <sprites/numeros.h>
#include <sprites/enemigo_01.h>


/*------------------------------------*/
const Entity_t nave_nodriza_tmpl = {
  E_TYPE_MOVABLE | E_TYPE_RENDER |  // type
  E_TYPE_AI,
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
  E_TYPE_MOVABLE | E_TYPE_RENDER |  // type
  E_TYPE_AI | E_TYPE_ANIM,  
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
  E_TYPE_RENDER,                    // type           
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
  E_TYPE_MOVABLE | E_TYPE_INPUT |   // type
  E_TYPE_RENDER,                    
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
  E_TYPE_RENDER,                    // type
  24, 0,                            // x, y
  SPR_NUMEROS_00_W,                 // w
  SPR_NUMEROS_00_H,                 // h
  0,  0,  0,                        // vx, vy
  spr_numeros_00,                   // sprite
  0x0000,                           // ai_behavior
  0x0000, 0,                        // anim, anim_counter
  0,                                // current_frame
};
