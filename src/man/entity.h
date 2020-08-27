#pragma once
#include <cpctelera.h>

enum {
    E_TYPE_INVALID = 0x00,
    E_TYPE_RENDER  = 0x01,
    E_TYPE_MOVABLE = 0x02,
    E_TYPE_INPUT   = 0x04,
    E_TYPE_AI      = 0x08,
    E_TYPE_DEAD    = 0x80,
    E_TYPE_DEFAULT = 0x7F,  
    MAX_ENTITIES   = 12,
};

typedef struct {
    u8 type;
    u8 x, y;
    u8 w, h;
    i8 vx, vy;
    u8 *sprite;
} Entity_t;

void      manEntityInit();
Entity_t *manEntityCreate();
void      manEntityForAll (void (*pfunUpdateEntity)(Entity_t *) );
void      manEntityForAllMatching(
              void (*pfunUpdateEntity)(Entity_t *),
              u8 signature);
void      manEntityDelete(Entity_t *e);
void      manEntityUpdate();
u8        manEntityAvailable();
