#pragma once
#include <cpctelera.h>
#include <man/animation.h>

#define isValid(E) ((E)->type != E_TYPE_INVALID)
#define signatureMatches(E, S) (((E)->components & (S)) == (S))

enum Type_t {
    E_TYPE_INVALID      = 0x00,
    E_TYPE_PLAYER       = 0x01,
    E_TYPE_ENEMY        = 0x02,
    E_TYPE_MOTHERSHIP   = 0x04,
    E_TYPE_SHOT         = 0x08,
	E_TYPE_ENEMY_SHOT	= 0x10,
    E_TYPE_DEAD         = 0x80,
    E_TYPE_DEFAULT      = E_TYPE_ENEMY,
};

enum Component_t {
    E_COMPONENT_DEFAULT = 0x00,    
    E_COMPONENT_RENDER  = 0x01,
    E_COMPONENT_MOVABLE = 0x02,
    E_COMPONENT_INPUT   = 0x04,
    E_COMPONENT_AI      = 0x08,
    E_COMPONENT_ANIM    = 0x10,
    E_COMPONENT_COLLIDE = 0x20,
};

enum Limits_t {
    MAX_ENTITIES   = 12,
};

typedef struct _Entity_t Entity_t;
typedef void (*AiBehaviorFn_t)(Entity_t*);
typedef void (*UpdateEntityFn_t)(Entity_t*);
typedef void (*UpdateEntityPairsFn_t)(Entity_t*, Entity_t*);

struct _Entity_t {
    u8                  type;
    u8                  components;
    u8                  x, y;
    u8                  w, h;
    i8                  vx, vy;
    u8                  move_counter;
    u8 const            *sprite;
    AiBehaviorFn_t      ai_behavior;
    u8                  ai_counter;
    AnimFrame_t const   *anim;
    u8                  anim_counter;
    u8                  current_frame;
    u8                  collides_with;
};

void      manEntityInit();
Entity_t *manEntityCreate();
Entity_t *manEntityClone(Entity_t *e_src);
void      manEntityForAll(UpdateEntityFn_t fnUpdateEntity);
void      manEntityForAllMatching(UpdateEntityFn_t fnUpdateEntity, u8 signature);
void      manEntityForAllPairsMatching(UpdateEntityPairsFn_t fnUpdatePairs, u8 signature);
void      manEntityDelete(Entity_t *e);
void      manEntityUpdate();
u8        manEntityAvailable();
