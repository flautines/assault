#pragma once

typedef struct AnimFrame AnimFrame_t;
typedef union SpriteOrNextFrame SpriteOrNextFrame_t;

union SpriteOrNextFrame {
    u8          *sprite;
    AnimFrame_t *next;
};

struct AnimFrame {
    u8                  time;   // In frames
    SpriteOrNextFrame_t val;    // Sprite for this frame or 
                                // ptr to start of animation.
};

#define ANIM_COUNTER_ENEMY_01 12

extern AnimFrame_t const animEnemy01[];