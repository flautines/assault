#include <man/entity.h>

void sysAnimationUpdateEntity(Entity_t *e)
{
    // Change sprite when anim counter is 0
    if ( --(e->anim_counter) == 0 ) {
        ++e->anim;
        // Cycle animation on end of sprites
        if ( e->anim->time == 0) {
            e->anim = e->anim->val.next;
        }
        // Load next sprite from animation
        e->sprite = e->anim->val.sprite;
        e->anim_counter = e->anim->time;        
    }

}

void sysAnimationUpdate()
{
    manEntityForAllMatching (sysAnimationUpdateEntity, E_COMPONENT_ANIM);
}