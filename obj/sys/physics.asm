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
	.globl _sysPhysicsUpDown
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
	push	af
	dec	sp
;src/sys/physics.c:15: u8 current_frame = e->current_frame;
	ld	c,4 (ix)
	ld	b,5 (ix)
	ld	hl, #0x000f
	add	hl,bc
	ex	(sp), hl
	pop	hl
	push	hl
	ld	a, (hl)
	ld	-1 (ix), a
;src/sys/physics.c:16: u8 move_counter = e->move_counter;
	push	bc
	pop	iy
	ld	e, 7 (iy)
;src/sys/physics.c:17: if (e->type & E_TYPE_INPUT)
	ld	a, (bc)
	bit	2, a
	jr	Z,00102$
;src/sys/physics.c:18: sysPhysicsCheckKeyboard(e);
	push	bc
	push	de
	push	bc
	call	_sysPhysicsCheckKeyboard
	pop	af
	pop	de
	pop	bc
00102$:
;src/sys/physics.c:20: if ( (current_frame & move_counter) == 0 )
	ld	a, -1 (ix)
	and	a,e
	jr	NZ,00104$
;src/sys/physics.c:22: i8 vx= e->vx;
	ld	l, c
	ld	h, b
	ld	de, #0x0005
	add	hl, de
	ld	d, (hl)
;src/sys/physics.c:23: e->x += vx;  
	ld	l, c
	ld	h, b
	inc	hl
	ld	a, (hl)
	add	a, d
	ld	(hl), a
;src/sys/physics.c:24: e->y += e->vy;
	ld	e, c
	ld	d, b
	inc	de
	inc	de
	ld	a, (de)
	ld	l, c
	ld	h, b
	ld	bc, #0x0006
	add	hl, bc
	ld	c, (hl)
	add	a, c
	ld	(de), a
00104$:
;src/sys/physics.c:26: ++current_frame;
	ld	c, -1 (ix)
	inc	c
;src/sys/physics.c:27: e->current_frame = current_frame;
	pop	hl
	push	hl
	ld	(hl), c
	ld	sp, ix
	pop	ix
	ret
;src/sys/physics.c:30: void sysPhysicsUpDown(Entity_t *e, u8 up)
;	---------------------------------
; Function sysPhysicsUpDown
; ---------------------------------
_sysPhysicsUpDown::
;src/sys/physics.c:32: e->vy = up ? -1 : 1;
	pop	de
	pop	bc
	push	bc
	push	de
	ld	hl, #0x0006
	add	hl, bc
	ld	iy, #4
	add	iy, sp
	ld	a, 0 (iy)
	or	a, a
	jr	Z,00103$
	ld	c, #0xff
	jr	00104$
00103$:
	ld	c, #0x01
00104$:
	ld	(hl), c
	ret
;src/sys/physics.c:35: void sysPhysicsUpdate() 
;	---------------------------------
; Function sysPhysicsUpdate
; ---------------------------------
_sysPhysicsUpdate::
;src/sys/physics.c:38: sysPhysicsUpdateEntity, 
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
