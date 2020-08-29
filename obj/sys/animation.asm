;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.8 #9946 (Linux)
;--------------------------------------------------------
	.module animation
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _sysAnimationUpdate
	.globl _sysAnimationUpdateEntity
	.globl _manEntityForAllMatching
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
;src/sys/animation.c:3: void sysAnimationUpdateEntity(Entity_t *e)
;	---------------------------------
; Function sysAnimationUpdateEntity
; ---------------------------------
_sysAnimationUpdateEntity::
	push	ix
	ld	ix,#0
	add	ix,sp
	ld	hl, #-6
	add	hl, sp
	ld	sp, hl
;src/sys/animation.c:6: if ( --(e->anim_counter) == 0 ) {
	ld	c,4 (ix)
	ld	b,5 (ix)
	ld	hl, #0x000e
	add	hl,bc
	ld	-2 (ix), l
	ld	-1 (ix), h
	ld	e, (hl)
	dec	e
	ld	l,-2 (ix)
	ld	h,-1 (ix)
	ld	(hl), e
	ld	a, e
	or	a, a
	jr	NZ,00105$
;src/sys/animation.c:7: ++e->anim;
	ld	hl, #0x000c
	add	hl,bc
	ex	(sp), hl
	pop	hl
	push	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	inc	de
	inc	de
	inc	de
	pop	hl
	push	hl
	ld	(hl), e
	inc	hl
	ld	(hl), d
;src/sys/animation.c:9: if ( e->anim->time == 0) {
	pop	hl
	push	hl
	ld	a, (hl)
	ld	-4 (ix), a
	inc	hl
	ld	a, (hl)
	ld	-3 (ix), a
	ld	a, (de)
	or	a, a
	jr	NZ,00102$
;src/sys/animation.c:10: e->anim = e->anim->val.next;
	pop	de
	pop	hl
	push	hl
	push	de
	inc	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	pop	hl
	push	hl
	ld	(hl), e
	inc	hl
	ld	(hl), d
00102$:
;src/sys/animation.c:13: e->sprite = e->anim->val.sprite;
	ld	hl, #0x0008
	add	hl,bc
	ld	c, l
	ld	b, h
	pop	hl
	push	hl
	ld	e, (hl)
	inc	hl
	ld	h, (hl)
	ld	l, e
	inc	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, e
	ld	(bc), a
	inc	bc
	ld	a, d
	ld	(bc), a
;src/sys/animation.c:14: e->anim_counter = e->anim->time;        
	pop	hl
	push	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	a, (bc)
	ld	l,-2 (ix)
	ld	h,-1 (ix)
	ld	(hl), a
00105$:
	ld	sp, ix
	pop	ix
	ret
;src/sys/animation.c:19: void sysAnimationUpdate()
;	---------------------------------
; Function sysAnimationUpdate
; ---------------------------------
_sysAnimationUpdate::
;src/sys/animation.c:21: manEntityForAllMatching (sysAnimationUpdateEntity, E_TYPE_ANIM);
	ld	a, #0x10
	push	af
	inc	sp
	ld	hl, #_sysAnimationUpdateEntity
	push	hl
	call	_manEntityForAllMatching
	pop	af
	inc	sp
	ret
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
