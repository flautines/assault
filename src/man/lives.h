#pragma once

#define MAX_LIVES	  3

// In bytes, not in pixels!
#define LIVES_X		  7	
#define LIVES_Y		192
#define LIVES_GAP	  9

void manLivesInit();
void manLivesUpdate();
void manLivesChange(i8 ammount);
int  manLivesGetNumber();
int  manLivesGetMax();
int  manLivesNeedDraw();