;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.8 #9946 (Linux)
;--------------------------------------------------------
	.module game
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _manGameCreateFromTemplate
	.globl _wait
	.globl _sysAIUpdate
	.globl _sysRenderInit
	.globl _sysRenderUpdate
	.globl _sysPhysicsUpdate
	.globl _manEntityUpdate
	.globl _manEntityCreate
	.globl _manEntityInit
	.globl _cpct_waitVSYNC
	.globl _cpct_waitHalts
	.globl _cpct_memcpy
	.globl _num_tmpl
	.globl _jugador_tmpl
	.globl _nave_marcador_tmpl
	.globl _nave_nodriza_tmpl
	.globl _manGameInit
	.globl _manGamePlay
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
;src/man/game.c:44: void wait(u8 n)
;	---------------------------------
; Function wait
; ---------------------------------
_wait::
;src/man/game.c:46: do {
	ld	hl, #2+0
	add	hl, sp
	ld	c, (hl)
00101$:
;src/man/game.c:47: cpct_waitHalts(n);
	push	bc
	ld	l, c
	call	_cpct_waitHalts
	call	_cpct_waitVSYNC
	pop	bc
;src/man/game.c:49: } while (--n);
	dec c
	jr	NZ,00101$
	ret
_nave_nodriza_tmpl:
	.db #0x0b	; 11
	.db #0x26	; 38
	.db #0x12	; 18
	.db #0x12	; 18
	.db #0x10	; 16
	.db #0xff	; -1
	.db #0x00	;  0
	.dw _spr_nave_nodriza
_nave_marcador_tmpl:
	.db #0x01	; 1
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0x06	; 6
	.db #0x08	; 8
	.db #0x00	;  0
	.db #0x00	;  0
	.dw _spr_nave_jugador_1
_jugador_tmpl:
	.db #0x07	; 7
	.db #0x26	; 38
	.db #0xb0	; 176
	.db #0x06	; 6
	.db #0x08	; 8
	.db #0x00	;  0
	.db #0x00	;  0
	.dw _spr_nave_jugador_0
_num_tmpl:
	.db #0x01	; 1
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x08	; 8
	.db #0x00	;  0
	.db #0x00	;  0
	.dw _spr_numeros_00
;src/man/game.c:52: Entity_t *manGameCreateFromTemplate(const Entity_t *tmpl)
;	---------------------------------
; Function manGameCreateFromTemplate
; ---------------------------------
_manGameCreateFromTemplate::
	push	ix
	ld	ix,#0
	add	ix,sp
;src/man/game.c:54: Entity_t *e = manEntityCreate();
	call	_manEntityCreate
;src/man/game.c:55: cpct_memcpy (e, tmpl, sizeof (Entity_t));
	ld	c,4 (ix)
	ld	b,5 (ix)
	push	hl
	pop	iy
	push	hl
	ld	de, #0x0009
	push	de
	push	bc
	push	iy
	call	_cpct_memcpy
	pop	hl
;src/man/game.c:56: return e;    
	pop	ix
	ret
;src/man/game.c:59: void manGameInit()
;	---------------------------------
; Function manGameInit
; ---------------------------------
_manGameInit::
	push	ix
	ld	ix,#0
	add	ix,sp
	ld	hl, #-12
	add	hl, sp
	ld	sp, hl
;src/man/game.c:61: manEntityInit();
	call	_manEntityInit
;src/man/game.c:62: sysRenderInit();
	call	_sysRenderInit
;src/man/game.c:64: manGameCreateFromTemplate (&nave_nodriza_tmpl);
	ld	hl, #_nave_nodriza_tmpl
	push	hl
	call	_manGameCreateFromTemplate
	pop	af
;src/man/game.c:69: do {
	ld	c, #0x1e
00101$:
;src/man/game.c:70: Entity_t *e = 
	push	bc
	ld	hl, #_nave_marcador_tmpl
	push	hl
	call	_manGameCreateFromTemplate
	pop	af
	pop	bc
;src/man/game.c:72: x -= 10;
	ld	a, c
	add	a, #0xf6
	ld	c, a
;src/man/game.c:73: e->x = x;
	inc	hl
	ld	(hl), c
;src/man/game.c:74: } while (x);
	ld	a, c
	or	a, a
	jr	NZ,00101$
;src/man/game.c:77: manGameCreateFromTemplate(&jugador_tmpl);
	ld	hl, #_jugador_tmpl
	push	hl
	call	_manGameCreateFromTemplate
	pop	af
;src/man/game.c:83: do {
	ld	hl, #0x0001
	add	hl, sp
	ld	c, l
	ld	b, h
	ld	-2 (ix), c
	ld	-1 (ix), b
	ld	-12 (ix), #0x06
00104$:
;src/man/game.c:84: --d;        
	dec	-12 (ix)
;src/man/game.c:85: cpct_memcpy(&num, &num_tmpl, sizeof(Entity_t));      
	ld	e, c
	ld	d, b
	push	bc
	ld	hl, #0x0009
	push	hl
	ld	hl, #_num_tmpl
	push	hl
	push	de
	call	_cpct_memcpy
	pop	bc
;src/man/game.c:86: num.sprite += d * SPR_NUMEROS_00_H * SPR_NUMEROS_00_W;
	ld	iy, #0x0007
	add	iy, bc
	ld	e, 0 (iy)
	ld	d, 1 (iy)
	push	de
	ld	e,-12 (ix)
	ld	d,#0x00
	ld	l, e
	ld	h, d
	add	hl, hl
	add	hl, de
	add	hl, hl
	add	hl, hl
	add	hl, hl
	pop	de
	add	hl, de
	ld	0 (iy), l
	ld	1 (iy), h
;src/man/game.c:87: num.x += d * (SPR_NUMEROS_00_W+2);
	push	bc
	pop	iy
	inc	iy
	ld	d, 0 (iy)
	ld	l, -12 (ix)
	ld	e, l
	add	hl, hl
	add	hl, hl
	add	hl, de
	ld	a, d
	add	a, l
	ld	0 (iy), a
;src/man/game.c:88: manGameCreateFromTemplate(&num);
	ld	e,-2 (ix)
	ld	d,-1 (ix)
	push	bc
	push	de
	call	_manGameCreateFromTemplate
	pop	af
	pop	bc
;src/man/game.c:90: } while (d);
	ld	a, -12 (ix)
	or	a, a
	jr	NZ,00104$
	ld	sp, ix
	pop	ix
	ret
;src/man/game.c:96: void manGamePlay()
;	---------------------------------
; Function manGamePlay
; ---------------------------------
_manGamePlay::
;src/man/game.c:98: while (1) {
00102$:
;src/man/game.c:99: sysAIUpdate();
	call	_sysAIUpdate
;src/man/game.c:100: sysPhysicsUpdate();   
	call	_sysPhysicsUpdate
;src/man/game.c:101: sysRenderUpdate();
	call	_sysRenderUpdate
;src/man/game.c:102: manEntityUpdate();
	call	_manEntityUpdate
	jr	00102$
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
