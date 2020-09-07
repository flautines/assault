#include "render.h"
#include <man/entity.h>
#include <cpctelera.h>
#include <sprites/main_palette.h>

void sysRenderLine(u8 *pvmem);
/////////////////////////////////////////////////////////////////////////////
void sysRenderInit() {
  cpct_disableFirmware();
  cpct_setVideoMode(0);
  cpct_setBorder(HW_BLACK);
  cpct_setPalette(main_palette, 16);
  sysRenderLine(cpct_getScreenPtr(CPCT_VMEM_START, 0, 185));
}

/////////////////////////////////////////////////////////////////////////////
void sysRenderUpdateEntity(Entity_t *e) {
  Entity_t *render_e  = e;
  u8 *pvmem = cpct_getScreenPtr(CPCT_VMEM_START, render_e->x, render_e->y);

  // Entidad viva
  if (!(render_e->type & E_TYPE_DEAD)) {    
    cpct_drawSprite (render_e->sprite, pvmem, render_e->w, render_e->h);
  }
  // Entidad muerta
  else {
    cpct_drawSolidBox(pvmem, 0x0000, render_e->w, render_e->h);
  }

	// Borrar el rastro del disparo
	if (render_e->type & (E_TYPE_SHOT | E_TYPE_ENEMY_SHOT)) {		
		u8 y = render_e->y;
		if (render_e->type & E_TYPE_SHOT)
			y += render_e->h;
		else
			y -= render_e->h;
			
		pvmem = cpct_getScreenPtr(CPCT_VMEM_START, render_e->x, y);
    	cpct_drawSolidBox(pvmem, 0x0000, render_e->w, render_e->h);
  }
}

/////////////////////////////////////////////////////////////////////////////
void sysRenderLine(u8 *pvmem) {
  cpct_drawSolidBox (pvmem, cpct_px2byteM0(10,10), 64, 3);
  pvmem += 64;
  cpct_drawSolidBox (pvmem, cpct_px2byteM0(10,10), 16, 3);
}

/////////////////////////////////////////////////////////////////////////////
void sysRenderUpdate() {  
  //cpct_waitVSYNC();  
  manEntityForAllMatching (
      sysRenderUpdateEntity, 
      E_COMPONENT_RENDER);
}
