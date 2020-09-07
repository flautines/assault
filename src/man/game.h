#pragma once

#include <man/entity.h>
void manGameInit();
void manGamePlay();
int manGameCreateEnemy(Entity_t *e);
void manGameEnemyLaneDown(Entity_t *e);
void manGameEntityDestroy(Entity_t *e);
void manGamePlayerShoot(Entity_t *player);
void manGameEnemyShoot(Entity_t *enemy);