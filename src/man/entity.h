#pragma once
#include <cpctelera.h>

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

enum {
    E_TYPE_INVALID = 0x00,
    E_TYPE_RENDER  = 0x01,
    E_TYPE_MOVABLE = 0x02,
    E_TYPE_INPUT   = 0x04,
    E_TYPE_AI      = 0x08,
    E_TYPE_ANIM    = 0x10,
    E_TYPE_DEAD    = 0x80,
    E_TYPE_DEFAULT = 0x7F,  
    MAX_ENTITIES   = 12,
};

typedef struct _Entity_t Entity_t;
typedef void (*AiBehaviorFn_t)(Entity_t*);
typedef void (*UpdateEntityFn_t)(Entity_t*);

struct _Entity_t {
    u8              type;
    u8              x, y;
    u8              w, h;
    i8              vx, vy;
    u8              move_counter;
    u8             *sprite;
    AiBehaviorFn_t  ai_behavior;
    AnimFrame_t    *anim;
    u8              anim_counter;
    u8              current_frame;
};

void      manEntityInit();
Entity_t *manEntityCreate();
void      manEntityForAll(UpdateEntityFn_t fnUpdateEntity);
void      manEntityForAllMatching(UpdateEntityFn_t fnUpdateEntity, u8 signature);
void      manEntityDelete(Entity_t *e);
void      manEntityUpdate();
u8        manEntityAvailable();
