;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.8 #9946 (Linux)
;--------------------------------------------------------
	.module physics
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _sysPhysicsUpdateEntity
	.globl _sysPhysicsCheckKeyboard
	.globl _manEntityForAllMatching
	.globl _cpct_isKeyPressed
	.globl _cpct_scanKeyboard_f
	.globl _sysPhysicsUpdate
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
;src/sys/physics.c:6: void sysPhysicsCheckKeyboard(Entity_t *e)
;	---------------------------------
; Function sysPhysicsCheckKeyboard
; ---------------------------------
_sysPhysicsCheckKeyboard::
;src/sys/physics.c:8: cpct_scanKeyboard_f();
	call	_cpct_scanKeyboard_f
;src/sys/physics.c:9: e->vx = 0;
	pop	de
	pop	bc
	push	bc
	push	de
	ld	hl, #0x0005
	add	hl, bc
	ld	(hl), #0x00
;src/sys/physics.c:10: if      (cpct_isKeyPressed(Key_O)) e->vx = -1;
	push	hl
	ld	hl, #0x0404
	call	_cpct_isKeyPressed
	ld	a, l
	pop	hl
	or	a, a
	jr	Z,00104$
	ld	(hl), #0xff
	ret
00104$:
;src/sys/physics.c:11: else if (cpct_isKeyPressed(Key_P)) e->vx = +1;
	push	hl
	ld	hl, #0x0803
	call	_cpct_isKeyPressed
	ld	a, l
	pop	hl
	or	a, a
	ret	Z
	ld	(hl), #0x01
	ret
;src/sys/physics.c:14: void sysPhysicsUpdateEntity(Entity_t *e) {
;	---------------------------------
; Function sysPhysicsUpdateEntity
; ---------------------------------
_sysPhysicsUpdateEntity::
	push	ix
	ld	ix,#0
	add	ix,sp
;src/sys/physics.c:16: if (e->type & E_TYPE_INPUT)
	ld	e,4 (ix)
	ld	d,5 (ix)
	ld	a, (de)
	bit	2, a
	jr	Z,00102$
;src/sys/physics.c:17: sysPhysicsCheckKeyboard(e);
	push	de
	push	de
	call	_sysPhysicsCheckKeyboard
	pop	af
	pop	de
00102$:
;src/sys/physics.c:19: i8 vx= e->vx;
	push	de
	pop	iy
	ld	c, 5 (iy)
;src/sys/physics.c:20: e->x += vx;  
	ld	l, e
	ld	h, d
	inc	hl
	ld	a, (hl)
	add	a, c
	ld	(hl), a
;src/sys/physics.c:21: e->y += e->vy;
	ld	c, e
	ld	b, d
	inc	bc
	inc	bc
	ld	a, (bc)
	ex	de,hl
	ld	de, #0x0006
	add	hl, de
	ld	e, (hl)
	add	a, e
	ld	(bc), a
	pop	ix
	ret
;src/sys/physics.c:25: void sysPhysicsUpdate() 
;	---------------------------------
; Function sysPhysicsUpdate
; ---------------------------------
_sysPhysicsUpdate::
;src/sys/physics.c:28: sysPhysicsUpdateEntity, 
	ld	a, #0x02
	push	af
	inc	sp
	ld	hl, #_sysPhysicsUpdateEntity
	push	hl
	call	_manEntityForAllMatching
	pop	af
	inc	sp
	ret
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
