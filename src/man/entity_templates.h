#include <man/entity.h>
#include <sprites/nave_nodriza_01.h>
#include <sprites/nave_jugador.h>
#include <sprites/numeros.h>
#include <sprites/enemigo_01.h>

#define MOTHERSHIP_Y    12  
#define LANE_DY         30
#define LANE2_Y         (MOTHERSHIP_Y + (SPR_NAVE_NODRIZA_H)+20)
#define LANE1_Y         ((LANE2_Y) + (LANE_DY))
#define LANE0_Y         ((LANE2_Y) + 2*(LANE_DY))

#define PLAYER_Y        176
#define PLAYER_SHOT_Y   ((PLAYER_Y) - 8)

/*------------------------------------*/
extern Entity_t const nave_nodriza_tmpl;
extern Entity_t const spawn_ray_tmpl;
extern Entity_t const enemy01_tmpl;
extern Entity_t const nave_vidas_tmpl;
extern Entity_t const jugador_tmpl;
extern Entity_t const num_tmpl;
extern Entity_t const player_shot_tmpl;
extern Entity_t const enemy_shot_tmpl;