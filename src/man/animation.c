#include <sprites/enemigo_01.h>
#include <man/entity.h>
#include <man/animation.h>


const AnimFrame_t animEnemy01[] = {
    { 12, { .sprite = spr_enemigo_01_0} }
,   { 12, { .sprite = spr_enemigo_01_1} }
,   {  0, { .next   = animEnemy01  } }
};