#pragma once
#include <man/entity.h>

void sysAIInit();
void sysAIUpdate();

// AI Behaviors
void sysAIBehaviorLeftRight(Entity_t *e);
void sysAIBehaviorMotherShip(Entity_t *e);
void sysAIBehaviorEnemy01(Entity_t *e);
void sysAIBehaviorAutoDestroy(Entity_t *e);
void sysAIBehaviorEnemyShot(Entity_t *e);