#include <man/entity_templates.h>
#include <man/entity.h>
#include <man/animation.h>
#include <sys/ai.h>
#include <sys/animation.h>
#include <sprites/nave_nodriza_01.h>
#include <sprites/nave_jugador.h>
#include <sprites/numeros.h>
#include <sprites/enemigo_01.h>
#include <sprites/player_shot.h>
#include <sprites/enemy_shot.h>

/*------------------------------------*/
Entity_t const nave_nodriza_tmpl = {
  E_TYPE_MOTHERSHIP,
  E_COMPONENT_MOVABLE | E_COMPONENT_RENDER |  // components
  E_COMPONENT_AI,
  38,                               // x
  MOTHERSHIP_Y,                     // y   
  SPR_NAVE_NODRIZA_W,               // w         
  SPR_NAVE_NODRIZA_H,               // h         
  -1,  0,  1,                       // vx, vy, move_counter                                
  spr_nave_nodriza,                 // sprite       
  sysAIBehaviorMotherShip,          // ai_behavior               
  0,
  0x0000, 0,                        // anim, anim_counter
  0,                                // current_frame  
  0,                                // collides_with
};
Entity_t const enemy01_tmpl = {
  E_TYPE_ENEMY,
  E_COMPONENT_MOVABLE | E_COMPONENT_RENDER |  // components
  E_COMPONENT_AI | E_COMPONENT_ANIM | 
  E_COMPONENT_COLLIDE, 
  0,                                // x
  LANE2_Y,                          // y
  SPR_ENEMIGO_01_0_W,               // w
  SPR_ENEMIGO_01_0_H,               // h
  -1, 0,  1,                        // vx, vy, move_counter
  spr_enemigo_01_0,                 
  sysAIBehaviorEnemy01,           
  0,
  animEnemy01,                      
  ANIM_COUNTER_ENEMY_01,            
  0,                                // current_frame
  0,                                // collides_with
};
/*
  TODO: manager de vidas
Entity_t const nave_vidas_tmpl = {
  E_TYPE_DEFAULT,
  E_COMPONENT_RENDER,                    // components
  0, 192,                           // x, y
  SPR_NAVE_JUGADOR_1_W,             // w
  SPR_NAVE_JUGADOR_1_H,             // h
  0,  0,  0,                        // vx, vy, move_counter
  spr_nave_jugador_1,               // sprite
  0x0000,                           // ai_behavior
  0x0000, 0,                        // anim, anim_counter
  0,                                // current_frame
  0,                                  // collides_with
};
*/
Entity_t const jugador_tmpl = {
  E_TYPE_PLAYER,
  E_COMPONENT_MOVABLE | E_COMPONENT_INPUT |   // components
  E_COMPONENT_RENDER | E_COMPONENT_COLLIDE, 
  38,                               // x
  PLAYER_Y,                         // y
  SPR_NAVE_JUGADOR_0_W,             // w
  SPR_NAVE_JUGADOR_0_H,             // h
  0,  0,  0,                        // vx, vy, move_counter
  spr_nave_jugador_0,               // sprite
  0x0000,                           // ai_behavior
  0,                                // ai_counter
  0x0000, 0 ,                       // anim, anim_counter
  0,                                // current_frame
  0,                                // collides_with
};
Entity_t const player_shot_tmpl = {
  E_TYPE_SHOT,
  E_COMPONENT_MOVABLE | E_COMPONENT_AI |      // components
  E_COMPONENT_RENDER | E_COMPONENT_COLLIDE,
  0,                                // x
  PLAYER_SHOT_Y,                    // y
  SPR_PLAYER_SHOT_W,                // w
  SPR_PLAYER_SHOT_H,                // h
  0,  -8,  0,                       // vx, vy, move_counter
  spr_player_shot,                  // sprite
  sysAIBehaviorAutoDestroy,         // ai_behavior
  16,                               // ai_counter
  0x0000, 0,                        // anim, anim_counter
  0,                                // current_frame
  E_TYPE_ENEMY,                     // collides_with
};

Entity_t const enemy_shot_tmpl = {
  E_TYPE_ENEMY_SHOT,
  E_COMPONENT_MOVABLE | E_COMPONENT_AI |      // components
  E_COMPONENT_RENDER | E_COMPONENT_COLLIDE,
  0,                                // x
  0,                    			// y
  SPR_ENEMY_SHOT_W,                 // w
  SPR_ENEMY_SHOT_H,                 // h
  0,   8,  0,                       // vx, vy, move_counter
  spr_enemy_shot,                   // sprite
  sysAIBehaviorEnemyShot,           // ai_behavior
  0,                                // ai_counter
  0x0000, 0,                        // anim, anim_counter
  0,                                // current_frame
  E_TYPE_ENEMY,                     // collides_with
};
/*
  TODO: manager de puntuacion
Entity_t const num_tmpl = {
  E_TYPE_DEFAULT,
  E_COMPONENT_RENDER,                    // components
  24, 0,                            // x, y
  SPR_NUMEROS_00_W,                 // w
  SPR_NUMEROS_00_H,                 // h                                // collides_with
  0,  0,  0,                        // vx, vy
  spr_numeros_00,                   // sprite
  0x0000,                           // ai_behavior
  0x0000, 0,                        // anim, anim_counter
  0,                                // current_frame
};
*/