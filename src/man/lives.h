#pragma once

// In bytes, not in pixels!
#define LIVES_X		  7	
#define LIVES_Y		192
#define LIVES_GAP	  9

void manLivesInit();
void manLivesUpdate();
int manLivesGetNumber();
int manLivesNeedDraw();