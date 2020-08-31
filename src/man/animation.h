#pragma once

typedef struct AnimFrame AnimFrame_t;
typedef union SpriteOrNextFrame SpriteOrNextFrame_t;

union SpriteOrNextFrame {
    u8 const          *const sprite;
    AnimFrame_t const *const next;
};

struct AnimFrame {
    u8 const            time;   // In frames
    SpriteOrNextFrame_t val;    // Sprite for this frame or 
                                // ptr to start of animation.
};

#define ANIM_COUNTER_ENEMY_01 12

extern AnimFrame_t const animEnemy01[];