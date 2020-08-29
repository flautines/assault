                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 3.6.8 #9946 (Linux)
                              4 ;--------------------------------------------------------
                              5 	.module game
                              6 	.optsdcc -mz80
                              7 	
                              8 ;--------------------------------------------------------
                              9 ; Public variables in this module
                             10 ;--------------------------------------------------------
                             11 	.globl _manGameCreateFromTemplate
                             12 	.globl _wait
                             13 	.globl _sysAnimationUpdate
                             14 	.globl _sysAIUpdate
                             15 	.globl _sysAIInit
                             16 	.globl _sysRenderInit
                             17 	.globl _sysRenderUpdate
                             18 	.globl _sysPhysicsUpdate
                             19 	.globl _manEntityUpdate
                             20 	.globl _manEntityCreate
                             21 	.globl _manEntityInit
                             22 	.globl _cpct_waitVSYNC
                             23 	.globl _cpct_waitHalts
                             24 	.globl _cpct_memcpy
                             25 	.globl _enemy_on_lane
                             26 	.globl _num_tmpl
                             27 	.globl _jugador_tmpl
                             28 	.globl _nave_vidas_tmpl
                             29 	.globl _enemy01_tmpl
                             30 	.globl _nave_nodriza_tmpl
                             31 	.globl _manGameCreateEnemy
                             32 	.globl _manGameInit
                             33 	.globl _manGamePlay
                             34 ;--------------------------------------------------------
                             35 ; special function registers
                             36 ;--------------------------------------------------------
                             37 ;--------------------------------------------------------
                             38 ; ram data
                             39 ;--------------------------------------------------------
                             40 	.area _DATA
   4BEF                      41 _enemy_on_lane::
   4BEF                      42 	.ds 1
                             43 ;--------------------------------------------------------
                             44 ; ram data
                             45 ;--------------------------------------------------------
                             46 	.area _INITIALIZED
                             47 ;--------------------------------------------------------
                             48 ; absolute external ram data
                             49 ;--------------------------------------------------------
                             50 	.area _DABS (ABS)
                             51 ;--------------------------------------------------------
                             52 ; global & static initialisations
                             53 ;--------------------------------------------------------
                             54 	.area _HOME
                             55 	.area _GSINIT
                             56 	.area _GSFINAL
                             57 	.area _GSINIT
                             58 ;--------------------------------------------------------
                             59 ; Home
                             60 ;--------------------------------------------------------
                             61 	.area _HOME
                             62 	.area _HOME
                             63 ;--------------------------------------------------------
                             64 ; code
                             65 ;--------------------------------------------------------
                             66 	.area _CODE
                             67 ;src/man/game.c:75: void wait(u8 n)
                             68 ;	---------------------------------
                             69 ; Function wait
                             70 ; ---------------------------------
   446C                      71 _wait::
                             72 ;src/man/game.c:77: do {
   446C 21 02 00      [10]   73 	ld	hl, #2+0
   446F 39            [11]   74 	add	hl, sp
   4470 4E            [ 7]   75 	ld	c, (hl)
   4471                      76 00101$:
                             77 ;src/man/game.c:78: cpct_waitHalts(n);
   4471 C5            [11]   78 	push	bc
   4472 69            [ 4]   79 	ld	l, c
   4473 CD F1 49      [17]   80 	call	_cpct_waitHalts
   4476 CD 05 4A      [17]   81 	call	_cpct_waitVSYNC
   4479 C1            [10]   82 	pop	bc
                             83 ;src/man/game.c:80: } while (--n);
   447A 0D            [ 4]   84 	dec c
   447B 20 F4         [12]   85 	jr	NZ,00101$
   447D C9            [10]   86 	ret
   447E                      87 _nave_nodriza_tmpl:
   447E 0B                   88 	.db #0x0b	; 11
   447F 26                   89 	.db #0x26	; 38
   4480 12                   90 	.db #0x12	; 18
   4481 12                   91 	.db #0x12	; 18
   4482 12                   92 	.db #0x12	; 18
   4483 FF                   93 	.db #0xff	; -1
   4484 00                   94 	.db #0x00	;  0
   4485 01                   95 	.db #0x01	; 1
   4486 18 42                96 	.dw _spr_nave_nodriza
   4488 2A 46                97 	.dw _sysAIBehaviorMotherShip
   448A 00 00                98 	.dw #0x0000
   448C 00                   99 	.db #0x00	; 0
   448D 00                  100 	.db #0x00	; 0
   448E                     101 _enemy01_tmpl:
   448E 1B                  102 	.db #0x1b	; 27
   448F 00                  103 	.db #0x00	; 0
   4490 32                  104 	.db #0x32	; 50	'2'
   4491 0A                  105 	.db #0x0a	; 10
   4492 0A                  106 	.db #0x0a	; 10
   4493 FF                  107 	.db #0xff	; -1
   4494 00                  108 	.db #0x00	;  0
   4495 01                  109 	.db #0x01	; 1
   4496 00 40               110 	.dw _spr_enemigo_01_0
   4498 F2 45               111 	.dw _sysAIBehaviorLeftRight
   449A 72 43               112 	.dw _animEnemy01
   449C 0C                  113 	.db #0x0c	; 12
   449D 00                  114 	.db #0x00	; 0
   449E                     115 _nave_vidas_tmpl:
   449E 01                  116 	.db #0x01	; 1
   449F 00                  117 	.db #0x00	; 0
   44A0 C0                  118 	.db #0xc0	; 192
   44A1 06                  119 	.db #0x06	; 6
   44A2 08                  120 	.db #0x08	; 8
   44A3 00                  121 	.db #0x00	;  0
   44A4 00                  122 	.db #0x00	;  0
   44A5 00                  123 	.db #0x00	; 0
   44A6 E8 41               124 	.dw _spr_nave_jugador_1
   44A8 00 00               125 	.dw #0x0000
   44AA 00 00               126 	.dw #0x0000
   44AC 00                  127 	.db #0x00	; 0
   44AD 00                  128 	.db #0x00	; 0
   44AE                     129 _jugador_tmpl:
   44AE 07                  130 	.db #0x07	; 7
   44AF 26                  131 	.db #0x26	; 38
   44B0 B0                  132 	.db #0xb0	; 176
   44B1 06                  133 	.db #0x06	; 6
   44B2 08                  134 	.db #0x08	; 8
   44B3 00                  135 	.db #0x00	;  0
   44B4 00                  136 	.db #0x00	;  0
   44B5 00                  137 	.db #0x00	; 0
   44B6 B8 41               138 	.dw _spr_nave_jugador_0
   44B8 00 00               139 	.dw #0x0000
   44BA 00 00               140 	.dw #0x0000
   44BC 00                  141 	.db #0x00	; 0
   44BD 00                  142 	.db #0x00	; 0
   44BE                     143 _num_tmpl:
   44BE 01                  144 	.db #0x01	; 1
   44BF 18                  145 	.db #0x18	; 24
   44C0 00                  146 	.db #0x00	; 0
   44C1 03                  147 	.db #0x03	; 3
   44C2 08                  148 	.db #0x08	; 8
   44C3 00                  149 	.db #0x00	;  0
   44C4 00                  150 	.db #0x00	;  0
   44C5 00                  151 	.db #0x00	; 0
   44C6 C8 40               152 	.dw _spr_numeros_00
   44C8 00 00               153 	.dw #0x0000
   44CA 00 00               154 	.dw #0x0000
   44CC 00                  155 	.db #0x00	; 0
   44CD 00                  156 	.db #0x00	; 0
                            157 ;src/man/game.c:83: Entity_t *manGameCreateFromTemplate(const Entity_t *tmpl)
                            158 ;	---------------------------------
                            159 ; Function manGameCreateFromTemplate
                            160 ; ---------------------------------
   44CE                     161 _manGameCreateFromTemplate::
   44CE DD E5         [15]  162 	push	ix
   44D0 DD 21 00 00   [14]  163 	ld	ix,#0
   44D4 DD 39         [15]  164 	add	ix,sp
                            165 ;src/man/game.c:85: Entity_t *e = manEntityCreate();
   44D6 CD 9D 43      [17]  166 	call	_manEntityCreate
                            167 ;src/man/game.c:86: cpct_memcpy (e, tmpl, sizeof (Entity_t));
   44D9 DD 4E 04      [19]  168 	ld	c,4 (ix)
   44DC DD 46 05      [19]  169 	ld	b,5 (ix)
   44DF E5            [11]  170 	push	hl
   44E0 FD E1         [14]  171 	pop	iy
   44E2 E5            [11]  172 	push	hl
   44E3 11 10 00      [10]  173 	ld	de, #0x0010
   44E6 D5            [11]  174 	push	de
   44E7 C5            [11]  175 	push	bc
   44E8 FD E5         [15]  176 	push	iy
   44EA CD 29 4A      [17]  177 	call	_cpct_memcpy
   44ED E1            [10]  178 	pop	hl
                            179 ;src/man/game.c:87: return e;    
   44EE DD E1         [14]  180 	pop	ix
   44F0 C9            [10]  181 	ret
                            182 ;src/man/game.c:90: void manGameCreateEnemy(Entity_t *e)
                            183 ;	---------------------------------
                            184 ; Function manGameCreateEnemy
                            185 ; ---------------------------------
   44F1                     186 _manGameCreateEnemy::
   44F1 DD E5         [15]  187 	push	ix
   44F3 DD 21 00 00   [14]  188 	ld	ix,#0
   44F7 DD 39         [15]  189 	add	ix,sp
                            190 ;src/man/game.c:92: if (enemy_on_lane) return;
   44F9 3A EF 4B      [13]  191 	ld	a,(#_enemy_on_lane + 0)
   44FC B7            [ 4]  192 	or	a, a
   44FD 20 2E         [12]  193 	jr	NZ,00103$
                            194 ;src/man/game.c:96: Entity_t *minion = manGameCreateFromTemplate (&enemy01_tmpl);
   44FF 21 8E 44      [10]  195 	ld	hl, #_enemy01_tmpl
   4502 E5            [11]  196 	push	hl
   4503 CD CE 44      [17]  197 	call	_manGameCreateFromTemplate
   4506 F1            [10]  198 	pop	af
   4507 4D            [ 4]  199 	ld	c, l
   4508 44            [ 4]  200 	ld	b, h
                            201 ;src/man/game.c:97: minion->x = e->x+4;
   4509 59            [ 4]  202 	ld	e, c
   450A 50            [ 4]  203 	ld	d, b
   450B 13            [ 6]  204 	inc	de
   450C E5            [11]  205 	push	hl
   450D DD 6E 04      [19]  206 	ld	l, 4 (ix)
   4510 DD 66 05      [19]  207 	ld	h, 5 (ix)
   4513 E5            [11]  208 	push	hl
   4514 FD E1         [14]  209 	pop	iy
   4516 E1            [10]  210 	pop	hl
   4517 FD E5         [15]  211 	push	iy
   4519 E1            [10]  212 	pop	hl
   451A 23            [ 6]  213 	inc	hl
   451B 7E            [ 7]  214 	ld	a, (hl)
   451C C6 04         [ 7]  215 	add	a, #0x04
   451E 12            [ 7]  216 	ld	(de), a
                            217 ;src/man/game.c:98: minion->vx = e->vx;
   451F 03            [ 6]  218 	inc	bc
   4520 03            [ 6]  219 	inc	bc
   4521 03            [ 6]  220 	inc	bc
   4522 03            [ 6]  221 	inc	bc
   4523 03            [ 6]  222 	inc	bc
   4524 FD 7E 05      [19]  223 	ld	a, 5 (iy)
   4527 02            [ 7]  224 	ld	(bc), a
                            225 ;src/man/game.c:102: enemy_on_lane = 1;
   4528 21 EF 4B      [10]  226 	ld	hl,#_enemy_on_lane + 0
   452B 36 01         [10]  227 	ld	(hl), #0x01
   452D                     228 00103$:
   452D DD E1         [14]  229 	pop	ix
   452F C9            [10]  230 	ret
                            231 ;src/man/game.c:105: void manGameInit()
                            232 ;	---------------------------------
                            233 ; Function manGameInit
                            234 ; ---------------------------------
   4530                     235 _manGameInit::
   4530 DD E5         [15]  236 	push	ix
   4532 DD 21 00 00   [14]  237 	ld	ix,#0
   4536 DD 39         [15]  238 	add	ix,sp
   4538 21 ED FF      [10]  239 	ld	hl, #-19
   453B 39            [11]  240 	add	hl, sp
   453C F9            [ 6]  241 	ld	sp, hl
                            242 ;src/man/game.c:107: manEntityInit();
   453D CD 7B 43      [17]  243 	call	_manEntityInit
                            244 ;src/man/game.c:108: sysRenderInit();
   4540 CD E0 47      [17]  245 	call	_sysRenderInit
                            246 ;src/man/game.c:109: sysAIInit();
   4543 CD 70 46      [17]  247 	call	_sysAIInit
                            248 ;src/man/game.c:112: manGameCreateFromTemplate (&nave_nodriza_tmpl);
   4546 21 7E 44      [10]  249 	ld	hl, #_nave_nodriza_tmpl
   4549 E5            [11]  250 	push	hl
   454A CD CE 44      [17]  251 	call	_manGameCreateFromTemplate
   454D F1            [10]  252 	pop	af
                            253 ;src/man/game.c:114: enemy_on_lane = 0;
   454E 21 EF 4B      [10]  254 	ld	hl,#_enemy_on_lane + 0
   4551 36 00         [10]  255 	ld	(hl), #0x00
                            256 ;src/man/game.c:119: do {
   4553 0E 1E         [ 7]  257 	ld	c, #0x1e
   4555                     258 00101$:
                            259 ;src/man/game.c:120: Entity_t *e = 
   4555 C5            [11]  260 	push	bc
   4556 21 9E 44      [10]  261 	ld	hl, #_nave_vidas_tmpl
   4559 E5            [11]  262 	push	hl
   455A CD CE 44      [17]  263 	call	_manGameCreateFromTemplate
   455D F1            [10]  264 	pop	af
   455E C1            [10]  265 	pop	bc
                            266 ;src/man/game.c:122: x -= 10;
   455F 79            [ 4]  267 	ld	a, c
   4560 C6 F6         [ 7]  268 	add	a, #0xf6
   4562 4F            [ 4]  269 	ld	c, a
                            270 ;src/man/game.c:123: e->x = x;
   4563 23            [ 6]  271 	inc	hl
   4564 71            [ 7]  272 	ld	(hl), c
                            273 ;src/man/game.c:124: } while (x);
   4565 79            [ 4]  274 	ld	a, c
   4566 B7            [ 4]  275 	or	a, a
   4567 20 EC         [12]  276 	jr	NZ,00101$
                            277 ;src/man/game.c:127: manGameCreateFromTemplate(&jugador_tmpl);
   4569 21 AE 44      [10]  278 	ld	hl, #_jugador_tmpl
   456C E5            [11]  279 	push	hl
   456D CD CE 44      [17]  280 	call	_manGameCreateFromTemplate
   4570 F1            [10]  281 	pop	af
                            282 ;src/man/game.c:133: do {
   4571 21 01 00      [10]  283 	ld	hl, #0x0001
   4574 39            [11]  284 	add	hl, sp
   4575 4D            [ 4]  285 	ld	c, l
   4576 44            [ 4]  286 	ld	b, h
   4577 DD 71 FE      [19]  287 	ld	-2 (ix), c
   457A DD 70 FF      [19]  288 	ld	-1 (ix), b
   457D DD 36 ED 06   [19]  289 	ld	-19 (ix), #0x06
   4581                     290 00104$:
                            291 ;src/man/game.c:134: --d;        
   4581 DD 35 ED      [23]  292 	dec	-19 (ix)
                            293 ;src/man/game.c:135: cpct_memcpy(&num, &num_tmpl, sizeof(Entity_t));      
   4584 59            [ 4]  294 	ld	e, c
   4585 50            [ 4]  295 	ld	d, b
   4586 C5            [11]  296 	push	bc
   4587 21 10 00      [10]  297 	ld	hl, #0x0010
   458A E5            [11]  298 	push	hl
   458B 21 BE 44      [10]  299 	ld	hl, #_num_tmpl
   458E E5            [11]  300 	push	hl
   458F D5            [11]  301 	push	de
   4590 CD 29 4A      [17]  302 	call	_cpct_memcpy
   4593 C1            [10]  303 	pop	bc
                            304 ;src/man/game.c:136: num.sprite += d * SPR_NUMEROS_00_H * SPR_NUMEROS_00_W;
   4594 FD 21 08 00   [14]  305 	ld	iy, #0x0008
   4598 FD 09         [15]  306 	add	iy, bc
   459A FD 5E 00      [19]  307 	ld	e, 0 (iy)
   459D FD 56 01      [19]  308 	ld	d, 1 (iy)
   45A0 D5            [11]  309 	push	de
   45A1 DD 5E ED      [19]  310 	ld	e,-19 (ix)
   45A4 16 00         [ 7]  311 	ld	d,#0x00
   45A6 6B            [ 4]  312 	ld	l, e
   45A7 62            [ 4]  313 	ld	h, d
   45A8 29            [11]  314 	add	hl, hl
   45A9 19            [11]  315 	add	hl, de
   45AA 29            [11]  316 	add	hl, hl
   45AB 29            [11]  317 	add	hl, hl
   45AC 29            [11]  318 	add	hl, hl
   45AD D1            [10]  319 	pop	de
   45AE 19            [11]  320 	add	hl, de
   45AF FD 75 00      [19]  321 	ld	0 (iy), l
   45B2 FD 74 01      [19]  322 	ld	1 (iy), h
                            323 ;src/man/game.c:137: num.x += d * (SPR_NUMEROS_00_W+2);
   45B5 C5            [11]  324 	push	bc
   45B6 FD E1         [14]  325 	pop	iy
   45B8 FD 23         [10]  326 	inc	iy
   45BA FD 56 00      [19]  327 	ld	d, 0 (iy)
   45BD DD 6E ED      [19]  328 	ld	l, -19 (ix)
   45C0 5D            [ 4]  329 	ld	e, l
   45C1 29            [11]  330 	add	hl, hl
   45C2 29            [11]  331 	add	hl, hl
   45C3 19            [11]  332 	add	hl, de
   45C4 7A            [ 4]  333 	ld	a, d
   45C5 85            [ 4]  334 	add	a, l
   45C6 FD 77 00      [19]  335 	ld	0 (iy), a
                            336 ;src/man/game.c:138: manGameCreateFromTemplate(&num);
   45C9 DD 5E FE      [19]  337 	ld	e,-2 (ix)
   45CC DD 56 FF      [19]  338 	ld	d,-1 (ix)
   45CF C5            [11]  339 	push	bc
   45D0 D5            [11]  340 	push	de
   45D1 CD CE 44      [17]  341 	call	_manGameCreateFromTemplate
   45D4 F1            [10]  342 	pop	af
   45D5 C1            [10]  343 	pop	bc
                            344 ;src/man/game.c:140: } while (d);
   45D6 DD 7E ED      [19]  345 	ld	a, -19 (ix)
   45D9 B7            [ 4]  346 	or	a, a
   45DA 20 A5         [12]  347 	jr	NZ,00104$
   45DC DD F9         [10]  348 	ld	sp, ix
   45DE DD E1         [14]  349 	pop	ix
   45E0 C9            [10]  350 	ret
                            351 ;src/man/game.c:145: void manGamePlay()
                            352 ;	---------------------------------
                            353 ; Function manGamePlay
                            354 ; ---------------------------------
   45E1                     355 _manGamePlay::
                            356 ;src/man/game.c:147: while (1) {
   45E1                     357 00102$:
                            358 ;src/man/game.c:148: sysAIUpdate();
   45E1 CD 95 46      [17]  359 	call	_sysAIUpdate
                            360 ;src/man/game.c:149: sysPhysicsUpdate();
   45E4 CD D2 47      [17]  361 	call	_sysPhysicsUpdate
                            362 ;src/man/game.c:150: sysAnimationUpdate();
   45E7 CD 22 47      [17]  363 	call	_sysAnimationUpdate
                            364 ;src/man/game.c:151: sysRenderUpdate();
   45EA CD 98 48      [17]  365 	call	_sysRenderUpdate
                            366 ;src/man/game.c:152: manEntityUpdate();
   45ED CD 3F 44      [17]  367 	call	_manEntityUpdate
   45F0 18 EF         [12]  368 	jr	00102$
                            369 	.area _CODE
                            370 	.area _INITIALIZER
                            371 	.area _CABS (ABS)
