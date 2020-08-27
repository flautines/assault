;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.8 #9946 (Linux)
;--------------------------------------------------------
	.module entity
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _manEntityDestroy
	.globl _cpct_memcpy
	.globl _cpct_memset
	.globl _m_entities_end
	.globl _m_next_free
	.globl _m_invalid
	.globl _m_entities
	.globl _manEntityInit
	.globl _manEntityCreate
	.globl _manEntityForAll
	.globl _manEntityForAllMatching
	.globl _manEntityDelete
	.globl _manEntityUpdate
	.globl _manEntityAvailable
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_m_entities::
	.ds 108
_m_invalid::
	.ds 1
_m_next_free::
	.ds 2
_m_entities_end::
	.ds 2
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
;src/man/entity.c:10: void manEntityInit() { 
;	---------------------------------
; Function manEntityInit
; ---------------------------------
_manEntityInit::
;src/man/entity.c:11: m_next_free = m_entities; 
	ld	bc, #_m_entities+0
	ld	(_m_next_free), bc
;src/man/entity.c:12: m_invalid = E_TYPE_INVALID;
	ld	hl,#_m_invalid + 0
	ld	(hl), #0x00
;src/man/entity.c:13: m_entities_end = m_entities + MAX_ENTITIES;
	ld	hl, #0x006c
	add	hl, bc
	ld	(_m_entities_end), hl
;src/man/entity.c:14: cpct_memset(m_next_free, 0, sizeof(m_entities));
	ld	hl, #0x006c
	push	hl
	xor	a, a
	push	af
	inc	sp
	ld	hl, #_m_entities
	push	hl
	call	_cpct_memset
	ret
;src/man/entity.c:17: Entity_t *manEntityCreate() {
;	---------------------------------
; Function manEntityCreate
; ---------------------------------
_manEntityCreate::
;src/man/entity.c:18: Entity_t *next = m_next_free;
	ld	bc, (_m_next_free)
;src/man/entity.c:19: m_next_free = next + 1;
	ld	hl, #0x0009
	add	hl,bc
	ld	(_m_next_free), hl
;src/man/entity.c:20: next->type = E_TYPE_DEFAULT;
	ld	a, #0x7f
	ld	(bc), a
;src/man/entity.c:21: return next;
	ld	l, c
	ld	h, b
	ret
;src/man/entity.c:24: void manEntityForAll(void (*pfunUpdateEntity)(Entity_t *)) {
;	---------------------------------
; Function manEntityForAll
; ---------------------------------
_manEntityForAll::
;src/man/entity.c:25: Entity_t *e = m_entities;
	ld	bc, #_m_entities+0
;src/man/entity.c:26: while (e->type != E_TYPE_INVALID) {
00101$:
	ld	a, (bc)
	or	a, a
	ret	Z
;src/man/entity.c:27: pfunUpdateEntity(e++);
	ld	e, c
	ld	d, b
	ld	hl, #0x0009
	add	hl,bc
	push	hl
	push	de
	ld	hl, #6
	add	hl, sp
	ld	a, (hl)
	inc	hl
	ld	h, (hl)
	ld	l, a
	call	___sdcc_call_hl
	pop	af
	pop	bc
	jr	00101$
;src/man/entity.c:31: void manEntityForAllMatching(
;	---------------------------------
; Function manEntityForAllMatching
; ---------------------------------
_manEntityForAllMatching::
;src/man/entity.c:35: Entity_t *e = m_entities;  
	ld	bc, #_m_entities+0
;src/man/entity.c:36: while (e->type != E_TYPE_INVALID) {
00103$:
	ld	a, (bc)
	or	a, a
	ret	Z
;src/man/entity.c:37: if ((e->type & signature) == signature)
	ld	iy, #4
	add	iy, sp
	and	a, 0 (iy)
	ld	e, a
	ld	a, 0 (iy)
	sub	a, e
	jr	NZ,00102$
;src/man/entity.c:38: pfunUpdateEntity(e);
	push	bc
	push	bc
	ld	hl, #6
	add	hl, sp
	ld	a, (hl)
	inc	hl
	ld	h, (hl)
	ld	l, a
	call	___sdcc_call_hl
	pop	af
	pop	bc
00102$:
;src/man/entity.c:39: e++;
	ld	hl, #0x0009
	add	hl,bc
	ld	c, l
	ld	b, h
	jr	00103$
;src/man/entity.c:44: void manEntityDestroy(Entity_t *e) {
;	---------------------------------
; Function manEntityDestroy
; ---------------------------------
_manEntityDestroy::
	push	ix
	ld	ix,#0
	add	ix,sp
;src/man/entity.c:45: Entity_t *dead_e = e;
	ld	c,4 (ix)
	ld	b,5 (ix)
;src/man/entity.c:46: --m_next_free;
	ld	hl, #_m_next_free
	ld	a, (hl)
	add	a, #0xf7
	ld	(hl), a
	inc	hl
	ld	a, (hl)
	adc	a, #0xff
	ld	(hl), a
;src/man/entity.c:48: if (dead_e != m_next_free)
	ld	iy, #_m_next_free
	ld	a, 0 (iy)
	sub	a, c
	jr	NZ,00109$
	ld	a, 1 (iy)
	sub	a, b
	jr	Z,00102$
00109$:
;src/man/entity.c:49: cpct_memcpy(dead_e, m_next_free, sizeof(Entity_t));
	ld	hl, (_m_next_free)
	ld	de, #0x0009
	push	de
	push	hl
	push	bc
	call	_cpct_memcpy
00102$:
;src/man/entity.c:51: m_next_free->type = E_TYPE_INVALID;
	ld	hl, (_m_next_free)
	ld	(hl), #0x00
	pop	ix
	ret
;src/man/entity.c:54: void manEntityDelete(Entity_t *e)
;	---------------------------------
; Function manEntityDelete
; ---------------------------------
_manEntityDelete::
;src/man/entity.c:56: e->type |= E_TYPE_DEAD;
	pop	de
	pop	bc
	push	bc
	push	de
	ld	a, (bc)
	set	7, a
	ld	(bc), a
	ret
;src/man/entity.c:59: void manEntityUpdate()
;	---------------------------------
; Function manEntityUpdate
; ---------------------------------
_manEntityUpdate::
;src/man/entity.c:61: Entity_t *e = m_entities;
	ld	hl, #_m_entities+0
;src/man/entity.c:62: while (e->type != E_TYPE_INVALID) {
00104$:
	ld	a, (hl)
	or	a, a
	ret	Z
;src/man/entity.c:63: if (e->type & E_TYPE_DEAD) {
	rlca
	jr	NC,00102$
;src/man/entity.c:64: manEntityDestroy(e);
	push	hl
	push	hl
	call	_manEntityDestroy
	pop	af
	pop	hl
	jr	00104$
00102$:
;src/man/entity.c:67: ++e;
	ld	bc, #0x0009
	add	hl, bc
	jr	00104$
;src/man/entity.c:72: u8 manEntityAvailable()
;	---------------------------------
; Function manEntityAvailable
; ---------------------------------
_manEntityAvailable::
;src/man/entity.c:74: return (m_next_free < m_entities_end);
	ld	hl, #_m_entities_end
	ld	iy, #_m_next_free
	ld	a, 0 (iy)
	sub	a, (hl)
	ld	a, 1 (iy)
	inc	hl
	sbc	a, (hl)
	ld	a, #0x00
	rla
	ld	l, a
	ret
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
