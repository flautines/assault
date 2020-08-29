;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.8 #9946 (Linux)
;--------------------------------------------------------
	.module render
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _sysRenderUpdateEntity
	.globl _manEntityForAllMatching
	.globl _cpct_getScreenPtr
	.globl _cpct_setPALColour
	.globl _cpct_setPalette
	.globl _cpct_waitVSYNC
	.globl _cpct_setVideoMode
	.globl _cpct_drawSprite
	.globl _cpct_drawSolidBox
	.globl _cpct_px2byteM0
	.globl _cpct_disableFirmware
	.globl _sysRenderInit
	.globl _sysRenderLine
	.globl _sysRenderUpdate
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;src/sys/render.c:8: void sysRenderInit() {
;	---------------------------------
; Function sysRenderInit
; ---------------------------------
_sysRenderInit::
;src/sys/render.c:9: cpct_disableFirmware();
	call	_cpct_disableFirmware
;src/sys/render.c:10: cpct_setVideoMode(0);
	ld	l, #0x00
	call	_cpct_setVideoMode
;src/sys/render.c:11: cpct_setBorder(HW_BLACK);
	ld	hl, #0x1410
	push	hl
	call	_cpct_setPALColour
;src/sys/render.c:12: cpct_setPalette(main_palette, 16);
	ld	hl, #0x0010
	push	hl
	ld	hl, #_main_palette
	push	hl
	call	_cpct_setPalette
;src/sys/render.c:15: CPCT_VMEM_START,
	ld	hl, #0xb900
	push	hl
	ld	h, #0xc0
	push	hl
	call	_cpct_getScreenPtr
	push	hl
	call	_sysRenderLine
	pop	af
	ret
;src/sys/render.c:19: void sysRenderUpdateEntity(Entity_t *e) {
;	---------------------------------
; Function sysRenderUpdateEntity
; ---------------------------------
_sysRenderUpdateEntity::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
;src/sys/render.c:20: Entity_t *render_e  = e;
	ld	c,4 (ix)
	ld	b,5 (ix)
;src/sys/render.c:22: if (!(render_e->type & E_TYPE_DEAD)) {
	ld	a, (bc)
	rlca
	jr	C,00103$
;src/sys/render.c:23: u8 *pvmem = 
	ld	l, c
	ld	h, b
	inc	hl
	inc	hl
	ld	d, (hl)
	ld	l, c
	ld	h, b
	inc	hl
	ld	a, (hl)
	push	bc
	ld	e, a
	push	de
	ld	hl, #0xc000
	push	hl
	call	_cpct_getScreenPtr
	ex	de,hl
	pop	bc
;src/sys/render.c:31: render_e->h);
	push	bc
	pop	iy
	ld	a, 4 (iy)
	ld	-1 (ix), a
;src/sys/render.c:30: render_e->w, 
	push	bc
	pop	iy
	ld	a, 3 (iy)
	ld	-2 (ix), a
;src/sys/render.c:29: pvmem, 
;src/sys/render.c:28: render_e->sprite, 
	ld	l, c
	ld	h, b
	ld	bc, #0x0008
	add	hl, bc
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	h, -1 (ix)
	ld	l, -2 (ix)
	push	hl
	push	de
	push	bc
	call	_cpct_drawSprite
00103$:
	ld	sp, ix
	pop	ix
	ret
;src/sys/render.c:35: void sysRenderLine(u8 *pvmem) {
;	---------------------------------
; Function sysRenderLine
; ---------------------------------
_sysRenderLine::
;src/sys/render.c:36: cpct_drawSolidBox (pvmem, cpct_px2byteM0(10,10), 64, 3);
	ld	hl, #0x0a0a
	push	hl
	call	_cpct_px2byteM0
	ld	h, #0x00
	pop	de
	pop	bc
	push	bc
	push	de
	ld	de, #0x0340
	push	de
	push	hl
	push	bc
	call	_cpct_drawSolidBox
;src/sys/render.c:37: pvmem += 64;
	ld	hl, #2
	add	hl, sp
	ld	a, (hl)
	add	a, #0x40
	ld	(hl), a
	inc	hl
	ld	a, (hl)
	adc	a, #0x00
	ld	(hl), a
;src/sys/render.c:38: cpct_drawSolidBox (pvmem, cpct_px2byteM0(10,10), 16, 3);
	ld	hl, #0x0a0a
	push	hl
	call	_cpct_px2byteM0
	ld	h, #0x00
	pop	de
	pop	bc
	push	bc
	push	de
	ld	de, #0x0310
	push	de
	push	hl
	push	bc
	call	_cpct_drawSolidBox
	ret
;src/sys/render.c:41: void sysRenderUpdate() {  
;	---------------------------------
; Function sysRenderUpdate
; ---------------------------------
_sysRenderUpdate::
;src/sys/render.c:42: cpct_waitVSYNC();  
	call	_cpct_waitVSYNC
;src/sys/render.c:44: sysRenderUpdateEntity, 
	ld	a, #0x01
	push	af
	inc	sp
	ld	hl, #_sysRenderUpdateEntity
	push	hl
	call	_manEntityForAllMatching
	pop	af
	inc	sp
	ret
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
