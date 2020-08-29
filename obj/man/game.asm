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
	.globl _sysAnimationUpdate
	.globl _sysAIUpdate
	.globl _sysAIInit
	.globl _sysRenderInit
	.globl _sysRenderUpdate
	.globl _sysPhysicsUpdate
	.globl _manEntityUpdate
	.globl _manEntityCreate
	.globl _manEntityInit
	.globl _cpct_waitVSYNC
	.globl _cpct_waitHalts
	.globl _cpct_memcpy
	.globl _enemy_on_lane
	.globl _num_tmpl
	.globl _jugador_tmpl
	.globl _nave_vidas_tmpl
	.globl _enemy01_tmpl
	.globl _nave_nodriza_tmpl
	.globl _manGameCreateEnemy
	.globl _manGameInit
	.globl _manGamePlay
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_enemy_on_lane::
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
;src/man/game.c:75: void wait(u8 n)
;	---------------------------------
; Function wait
; ---------------------------------
_wait::
;src/man/game.c:77: do {
	ld	hl, #2+0
	add	hl, sp
	ld	c, (hl)
00101$:
;src/man/game.c:78: cpct_waitHalts(n);
	push	bc
	ld	l, c
	call	_cpct_waitHalts
	call	_cpct_waitVSYNC
	pop	bc
;src/man/game.c:80: } while (--n);
	dec c
	jr	NZ,00101$
	ret
_nave_nodriza_tmpl:
	.db #0x0b	; 11
	.db #0x26	; 38
	.db #0x12	; 18
	.db #0x12	; 18
	.db #0x12	; 18
	.db #0xff	; -1
	.db #0x00	;  0
	.db #0x01	; 1
	.dw _spr_nave_nodriza
	.dw _sysAIBehaviorMotherShip
	.dw #0x0000
	.db #0x00	; 0
	.db #0x00	; 0
_enemy01_tmpl:
	.db #0x1b	; 27
	.db #0x00	; 0
	.db #0x32	; 50	'2'
	.db #0x0a	; 10
	.db #0x0a	; 10
	.db #0xff	; -1
	.db #0x00	;  0
	.db #0x01	; 1
	.dw _spr_enemigo_01_0
	.dw _sysAIBehaviorLeftRight
	.dw _animEnemy01
	.db #0x0c	; 12
	.db #0x00	; 0
_nave_vidas_tmpl:
	.db #0x01	; 1
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0x06	; 6
	.db #0x08	; 8
	.db #0x00	;  0
	.db #0x00	;  0
	.db #0x00	; 0
	.dw _spr_nave_jugador_1
	.dw #0x0000
	.dw #0x0000
	.db #0x00	; 0
	.db #0x00	; 0
_jugador_tmpl:
	.db #0x07	; 7
	.db #0x26	; 38
	.db #0xb0	; 176
	.db #0x06	; 6
	.db #0x08	; 8
	.db #0x00	;  0
	.db #0x00	;  0
	.db #0x00	; 0
	.dw _spr_nave_jugador_0
	.dw #0x0000
	.dw #0x0000
	.db #0x00	; 0
	.db #0x00	; 0
_num_tmpl:
	.db #0x01	; 1
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x08	; 8
	.db #0x00	;  0
	.db #0x00	;  0
	.db #0x00	; 0
	.dw _spr_numeros_00
	.dw #0x0000
	.dw #0x0000
	.db #0x00	; 0
	.db #0x00	; 0
;src/man/game.c:83: Entity_t *manGameCreateFromTemplate(const Entity_t *tmpl)
;	---------------------------------
; Function manGameCreateFromTemplate
; ---------------------------------
_manGameCreateFromTemplate::
	push	ix
	ld	ix,#0
	add	ix,sp
;src/man/game.c:85: Entity_t *e = manEntityCreate();
	call	_manEntityCreate
;src/man/game.c:86: cpct_memcpy (e, tmpl, sizeof (Entity_t));
	ld	c,4 (ix)
	ld	b,5 (ix)
	push	hl
	pop	iy
	push	hl
	ld	de, #0x0010
	push	de
	push	bc
	push	iy
	call	_cpct_memcpy
	pop	hl
;src/man/game.c:87: return e;    
	pop	ix
	ret
;src/man/game.c:90: void manGameCreateEnemy(Entity_t *e)
;	---------------------------------
; Function manGameCreateEnemy
; ---------------------------------
_manGameCreateEnemy::
	push	ix
	ld	ix,#0
	add	ix,sp
;src/man/game.c:92: if (enemy_on_lane) return;
	ld	a,(#_enemy_on_lane + 0)
	or	a, a
	jr	NZ,00103$
;src/man/game.c:96: Entity_t *minion = manGameCreateFromTemplate (&enemy01_tmpl);
	ld	hl, #_enemy01_tmpl
	push	hl
	call	_manGameCreateFromTemplate
	pop	af
	ld	c, l
	ld	b, h
;src/man/game.c:97: minion->x = e->x+4;
	ld	e, c
	ld	d, b
	inc	de
	push	hl
	ld	l, 4 (ix)
	ld	h, 5 (ix)
	push	hl
	pop	iy
	pop	hl
	push	iy
	pop	hl
	inc	hl
	ld	a, (hl)
	add	a, #0x04
	ld	(de), a
;src/man/game.c:98: minion->vx = e->vx;
	inc	bc
	inc	bc
	inc	bc
	inc	bc
	inc	bc
	ld	a, 5 (iy)
	ld	(bc), a
;src/man/game.c:102: enemy_on_lane = 1;
	ld	hl,#_enemy_on_lane + 0
	ld	(hl), #0x01
00103$:
	pop	ix
	ret
;src/man/game.c:105: void manGameInit()
;	---------------------------------
; Function manGameInit
; ---------------------------------
_manGameInit::
	push	ix
	ld	ix,#0
	add	ix,sp
	ld	hl, #-19
	add	hl, sp
	ld	sp, hl
;src/man/game.c:107: manEntityInit();
	call	_manEntityInit
;src/man/game.c:108: sysRenderInit();
	call	_sysRenderInit
;src/man/game.c:109: sysAIInit();
	call	_sysAIInit
;src/man/game.c:112: manGameCreateFromTemplate (&nave_nodriza_tmpl);
	ld	hl, #_nave_nodriza_tmpl
	push	hl
	call	_manGameCreateFromTemplate
	pop	af
;src/man/game.c:114: enemy_on_lane = 0;
	ld	hl,#_enemy_on_lane + 0
	ld	(hl), #0x00
;src/man/game.c:119: do {
	ld	c, #0x1e
00101$:
;src/man/game.c:120: Entity_t *e = 
	push	bc
	ld	hl, #_nave_vidas_tmpl
	push	hl
	call	_manGameCreateFromTemplate
	pop	af
	pop	bc
;src/man/game.c:122: x -= 10;
	ld	a, c
	add	a, #0xf6
	ld	c, a
;src/man/game.c:123: e->x = x;
	inc	hl
	ld	(hl), c
;src/man/game.c:124: } while (x);
	ld	a, c
	or	a, a
	jr	NZ,00101$
;src/man/game.c:127: manGameCreateFromTemplate(&jugador_tmpl);
	ld	hl, #_jugador_tmpl
	push	hl
	call	_manGameCreateFromTemplate
	pop	af
;src/man/game.c:133: do {
	ld	hl, #0x0001
	add	hl, sp
	ld	c, l
	ld	b, h
	ld	-2 (ix), c
	ld	-1 (ix), b
	ld	-19 (ix), #0x06
00104$:
;src/man/game.c:134: --d;        
	dec	-19 (ix)
;src/man/game.c:135: cpct_memcpy(&num, &num_tmpl, sizeof(Entity_t));      
	ld	e, c
	ld	d, b
	push	bc
	ld	hl, #0x0010
	push	hl
	ld	hl, #_num_tmpl
	push	hl
	push	de
	call	_cpct_memcpy
	pop	bc
;src/man/game.c:136: num.sprite += d * SPR_NUMEROS_00_H * SPR_NUMEROS_00_W;
	ld	iy, #0x0008
	add	iy, bc
	ld	e, 0 (iy)
	ld	d, 1 (iy)
	push	de
	ld	e,-19 (ix)
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
;src/man/game.c:137: num.x += d * (SPR_NUMEROS_00_W+2);
	push	bc
	pop	iy
	inc	iy
	ld	d, 0 (iy)
	ld	l, -19 (ix)
	ld	e, l
	add	hl, hl
	add	hl, hl
	add	hl, de
	ld	a, d
	add	a, l
	ld	0 (iy), a
;src/man/game.c:138: manGameCreateFromTemplate(&num);
	ld	e,-2 (ix)
	ld	d,-1 (ix)
	push	bc
	push	de
	call	_manGameCreateFromTemplate
	pop	af
	pop	bc
;src/man/game.c:140: } while (d);
	ld	a, -19 (ix)
	or	a, a
	jr	NZ,00104$
	ld	sp, ix
	pop	ix
	ret
;src/man/game.c:145: void manGamePlay()
;	---------------------------------
; Function manGamePlay
; ---------------------------------
_manGamePlay::
;src/man/game.c:147: while (1) {
00102$:
;src/man/game.c:148: sysAIUpdate();
	call	_sysAIUpdate
;src/man/game.c:149: sysPhysicsUpdate();
	call	_sysPhysicsUpdate
;src/man/game.c:150: sysAnimationUpdate();
	call	_sysAnimationUpdate
;src/man/game.c:151: sysRenderUpdate();
	call	_sysRenderUpdate
;src/man/game.c:152: manEntityUpdate();
	call	_manEntityUpdate
	jr	00102$
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
