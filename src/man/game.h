#pragma once

#include <man/entity.h>
void manGameInit();
void manGamePlay();
void manGameCreateEnemy(Entity_t *e);
void manGameEnemyLaneDown(Entity_t *e);
void manGameEntityDestroy(Entity_t *e);
void manGamePlayerShot(Entity_t *player);