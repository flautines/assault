;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.8 #9946 (Linux)
;--------------------------------------------------------
	.module ai
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _sysAIUpdateEntity
	.globl _sysPhysicsUpDown
	.globl _manGameCreateEnemy
	.globl _manEntityForAllMatching
	.globl _updown
	.globl _sysAIBehaviorLeftRight
	.globl _sysAIBehaviorMotherShip
	.globl _sysAIInit
	.globl _sysAIUpdate
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_updown::
	.ds 1
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
;src/sys/ai.c:9: void sysAIBehaviorLeftRight(Entity_t *e)
;	---------------------------------
; Function sysAIBehaviorLeftRight
; ---------------------------------
_sysAIBehaviorLeftRight::
	push	ix
	ld	ix,#0
	add	ix,sp
;src/sys/ai.c:11: const u8 rbound = 80 - e->w;
	ld	c,4 (ix)
	ld	b,5 (ix)
	ld	l, c
	ld	h, b
	inc	hl
	inc	hl
	inc	hl
	ld	e, (hl)
	ld	a, #0x50
	sub	a, e
	ld	e, a
;src/sys/ai.c:12: if (e->x == 0)      e->vx =  1;
	push	bc
	pop	iy
	inc	iy
	ld	l, 0 (iy)
	inc	bc
	inc	bc
	inc	bc
	inc	bc
	inc	bc
	ld	a, l
	or	a, a
	jr	NZ,00102$
	ld	a, #0x01
	ld	(bc), a
00102$:
;src/sys/ai.c:13: if (e->x == rbound) e->vx = -1;
	ld	a, 0 (iy)
	sub	a, e
	jr	NZ,00105$
	ld	a, #0xff
	ld	(bc), a
00105$:
	pop	ix
	ret
;src/sys/ai.c:15: void sysAIBehaviorMotherShip(Entity_t *e)
;	---------------------------------
; Function sysAIBehaviorMotherShip
; ---------------------------------
_sysAIBehaviorMotherShip::
;src/sys/ai.c:17: if (e->x == 20) {
	pop	de
	pop	bc
	push	bc
	push	de
	ld	l, c
	ld	h, b
	inc	hl
	ld	a, (hl)
	sub	a, #0x14
	jr	NZ,00102$
;src/sys/ai.c:18: manGameCreateEnemy (e);
	push	bc
	push	bc
	call	_manGameCreateEnemy
	pop	af
	pop	bc
00102$:
;src/sys/ai.c:22: if ( (e->current_frame&15) == 0 ) {
	ld	l, c
	ld	h, b
	ld	de, #0x000f
	add	hl, de
	ld	a, (hl)
	and	a, #0x0f
	jr	NZ,00104$
;src/sys/ai.c:23: sysPhysicsUpDown(e, updown);
	ld	a, (_updown)
	push	af
	inc	sp
	ld	hl, #3
	add	hl, sp
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	push	bc
	call	_sysPhysicsUpDown
	pop	af
	inc	sp
;src/sys/ai.c:24: updown ^= 1;
	ld	iy, #_updown
	ld	a, 0 (iy)
	xor	a, #0x01
	ld	0 (iy), a
00104$:
;src/sys/ai.c:26: sysAIBehaviorLeftRight(e);
	pop	bc
	pop	hl
	push	hl
	push	bc
	push	hl
	call	_sysAIBehaviorLeftRight
	pop	af
	ret
;src/sys/ai.c:31: void sysAIInit()
;	---------------------------------
; Function sysAIInit
; ---------------------------------
_sysAIInit::
;src/sys/ai.c:33: updown = 0;
	ld	hl,#_updown + 0
	ld	(hl), #0x00
	ret
;src/sys/ai.c:36: void sysAIUpdateEntity(Entity_t *e)
;	---------------------------------
; Function sysAIUpdateEntity
; ---------------------------------
_sysAIUpdateEntity::
	push	ix
	ld	ix,#0
	add	ix,sp
;src/sys/ai.c:38: e->ai_behavior(e);
	ld	c,4 (ix)
	ld	b,5 (ix)
	push	bc
	pop	iy
	ld	l, 10 (iy)
	ld	h, 11 (iy)
	push	bc
	call	___sdcc_call_hl
	pop	af
	pop	ix
	ret
;src/sys/ai.c:41: void sysAIUpdate()
;	---------------------------------
; Function sysAIUpdate
; ---------------------------------
_sysAIUpdate::
;src/sys/ai.c:44: sysAIUpdateEntity, 
	ld	a, #0x0a
	push	af
	inc	sp
	ld	hl, #_sysAIUpdateEntity
	push	hl
	call	_manEntityForAllMatching
	pop	af
	inc	sp
	ret
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
