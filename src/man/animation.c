#include <sprites/enemigo_01.h>
#include <man/entity.h>
#include <man/animation.h>


AnimFrame_t const animEnemy01[] = {
    { ANIM_COUNTER_ENEMY_01, { .sprite = spr_enemigo_01_0} }
,   { ANIM_COUNTER_ENEMY_01, { .sprite = spr_enemigo_01_1} }
,   {  0, { .next   = animEnemy01  } }
};