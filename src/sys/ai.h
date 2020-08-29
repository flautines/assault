#pragma once
#include <man/entity.h>

void sysAIInit();
void sysAIUpdate();

// AI Behaviors
void sysAIBehaviorLeftRight(Entity_t *e);
void sysAIBehaviorMotherShip(Entity_t *e);
