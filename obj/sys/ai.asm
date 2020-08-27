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
	.globl _manEntityForAllMatching
	.globl _sysAIUpdate
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
;src/sys/ai.c:5: void sysAIUpdateEntity(Entity_t *e)
;	---------------------------------
; Function sysAIUpdateEntity
; ---------------------------------
_sysAIUpdateEntity::
	push	ix
	ld	ix,#0
	add	ix,sp
;src/sys/ai.c:7: const u8 rbound = 80 - e->w;
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
;src/sys/ai.c:8: if (e->x == 0)      e->vx =  1;
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
;src/sys/ai.c:9: if (e->x == rbound) e->vx = -1;
	ld	a, 0 (iy)
	sub	a, e
	jr	NZ,00105$
	ld	a, #0xff
	ld	(bc), a
00105$:
	pop	ix
	ret
;src/sys/ai.c:12: void sysAIUpdate()
;	---------------------------------
; Function sysAIUpdate
; ---------------------------------
_sysAIUpdate::
;src/sys/ai.c:15: sysAIUpdateEntity, 
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
