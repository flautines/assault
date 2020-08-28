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
                             15 	.globl _sysRenderInit
                             16 	.globl _sysRenderUpdate
                             17 	.globl _sysPhysicsUpdate
                             18 	.globl _manEntityUpdate
                             19 	.globl _manEntityCreate
                             20 	.globl _manEntityInit
                             21 	.globl _cpct_waitVSYNC
                             22 	.globl _cpct_waitHalts
                             23 	.globl _cpct_memcpy
                             24 	.globl _enemy_on_lane
                             25 	.globl _num_tmpl
                             26 	.globl _jugador_tmpl
                             27 	.globl _nave_vidas_tmpl
                             28 	.globl _enemy01_tmpl
                             29 	.globl _nave_nodriza_tmpl
                             30 	.globl _manGameCreateEnemy
                             31 	.globl _manGameInit
                             32 	.globl _manGamePlay
                             33 ;--------------------------------------------------------
                             34 ; special function registers
                             35 ;--------------------------------------------------------
                             36 ;--------------------------------------------------------
                             37 ; ram data
                             38 ;--------------------------------------------------------
                             39 	.area _DATA
   4B31                      40 _enemy_on_lane::
   4B31                      41 	.ds 1
                             42 ;--------------------------------------------------------
                             43 ; ram data
                             44 ;--------------------------------------------------------
                             45 	.area _INITIALIZED
                             46 ;--------------------------------------------------------
                             47 ; absolute external ram data
                             48 ;--------------------------------------------------------
                             49 	.area _DABS (ABS)
                             50 ;--------------------------------------------------------
                             51 ; global & static initialisations
                             52 ;--------------------------------------------------------
                             53 	.area _HOME
                             54 	.area _GSINIT
                             55 	.area _GSFINAL
                             56 	.area _GSINIT
                             57 ;--------------------------------------------------------
                             58 ; Home
                             59 ;--------------------------------------------------------
                             60 	.area _HOME
                             61 	.area _HOME
                             62 ;--------------------------------------------------------
                             63 ; code
                             64 ;--------------------------------------------------------
                             65 	.area _CODE
                             66 ;src/man/game.c:70: void wait(u8 n)
                             67 ;	---------------------------------
                             68 ; Function wait
                             69 ; ---------------------------------
   4448                      70 _wait::
                             71 ;src/man/game.c:72: do {
   4448 21 02 00      [10]   72 	ld	hl, #2+0
   444B 39            [11]   73 	add	hl, sp
   444C 4E            [ 7]   74 	ld	c, (hl)
   444D                      75 00101$:
                             76 ;src/man/game.c:73: cpct_waitHalts(n);
   444D C5            [11]   77 	push	bc
   444E 69            [ 4]   78 	ld	l, c
   444F CD 4B 49      [17]   79 	call	_cpct_waitHalts
   4452 CD 5F 49      [17]   80 	call	_cpct_waitVSYNC
   4455 C1            [10]   81 	pop	bc
                             82 ;src/man/game.c:75: } while (--n);
   4456 0D            [ 4]   83 	dec c
   4457 20 F4         [12]   84 	jr	NZ,00101$
   4459 C9            [10]   85 	ret
   445A                      86 _nave_nodriza_tmpl:
   445A 0B                   87 	.db #0x0b	; 11
   445B 26                   88 	.db #0x26	; 38
   445C 12                   89 	.db #0x12	; 18
   445D 12                   90 	.db #0x12	; 18
   445E 10                   91 	.db #0x10	; 16
   445F FF                   92 	.db #0xff	; -1
   4460 00                   93 	.db #0x00	;  0
   4461 18 42                94 	.dw _spr_nave_nodriza
   4463 F9 45                95 	.dw _sysAIBehaviorMotherShip
   4465 00 00                96 	.dw #0x0000
   4467 00                   97 	.db #0x00	; 0
   4468                      98 _enemy01_tmpl:
   4468 1B                   99 	.db #0x1b	; 27
   4469 00                  100 	.db #0x00	; 0
   446A 30                  101 	.db #0x30	; 48	'0'
   446B 0A                  102 	.db #0x0a	; 10
   446C 0A                  103 	.db #0x0a	; 10
   446D FF                  104 	.db #0xff	; -1
   446E 00                  105 	.db #0x00	;  0
   446F 00 40               106 	.dw _spr_enemigo_01_0
   4471 C1 45               107 	.dw _sysAIBehaviorLeftRight
   4473 4E 43               108 	.dw _animEnemy01
   4475 0C                  109 	.db #0x0c	; 12
   4476                     110 _nave_vidas_tmpl:
   4476 01                  111 	.db #0x01	; 1
   4477 00                  112 	.db #0x00	; 0
   4478 C0                  113 	.db #0xc0	; 192
   4479 06                  114 	.db #0x06	; 6
   447A 08                  115 	.db #0x08	; 8
   447B 00                  116 	.db #0x00	;  0
   447C 00                  117 	.db #0x00	;  0
   447D E8 41               118 	.dw _spr_nave_jugador_1
   447F 00 00               119 	.dw #0x0000
   4481 00 00               120 	.dw #0x0000
   4483 00                  121 	.db #0x00	; 0
   4484                     122 _jugador_tmpl:
   4484 07                  123 	.db #0x07	; 7
   4485 26                  124 	.db #0x26	; 38
   4486 B0                  125 	.db #0xb0	; 176
   4487 06                  126 	.db #0x06	; 6
   4488 08                  127 	.db #0x08	; 8
   4489 00                  128 	.db #0x00	;  0
   448A 00                  129 	.db #0x00	;  0
   448B B8 41               130 	.dw _spr_nave_jugador_0
   448D 00 00               131 	.dw #0x0000
   448F 00 00               132 	.dw #0x0000
   4491 00                  133 	.db #0x00	; 0
   4492                     134 _num_tmpl:
   4492 01                  135 	.db #0x01	; 1
   4493 18                  136 	.db #0x18	; 24
   4494 00                  137 	.db #0x00	; 0
   4495 03                  138 	.db #0x03	; 3
   4496 08                  139 	.db #0x08	; 8
   4497 00                  140 	.db #0x00	;  0
   4498 00                  141 	.db #0x00	;  0
   4499 C8 40               142 	.dw _spr_numeros_00
   449B 00 00               143 	.dw #0x0000
   449D 00 00               144 	.dw #0x0000
   449F 00                  145 	.db #0x00	; 0
                            146 ;src/man/game.c:78: Entity_t *manGameCreateFromTemplate(const Entity_t *tmpl)
                            147 ;	---------------------------------
                            148 ; Function manGameCreateFromTemplate
                            149 ; ---------------------------------
   44A0                     150 _manGameCreateFromTemplate::
   44A0 DD E5         [15]  151 	push	ix
   44A2 DD 21 00 00   [14]  152 	ld	ix,#0
   44A6 DD 39         [15]  153 	add	ix,sp
                            154 ;src/man/game.c:80: Entity_t *e = manEntityCreate();
   44A8 CD 79 43      [17]  155 	call	_manEntityCreate
                            156 ;src/man/game.c:81: cpct_memcpy (e, tmpl, sizeof (Entity_t));
   44AB DD 4E 04      [19]  157 	ld	c,4 (ix)
   44AE DD 46 05      [19]  158 	ld	b,5 (ix)
   44B1 E5            [11]  159 	push	hl
   44B2 FD E1         [14]  160 	pop	iy
   44B4 E5            [11]  161 	push	hl
   44B5 11 0E 00      [10]  162 	ld	de, #0x000e
   44B8 D5            [11]  163 	push	de
   44B9 C5            [11]  164 	push	bc
   44BA FD E5         [15]  165 	push	iy
   44BC CD 83 49      [17]  166 	call	_cpct_memcpy
   44BF E1            [10]  167 	pop	hl
                            168 ;src/man/game.c:82: return e;    
   44C0 DD E1         [14]  169 	pop	ix
   44C2 C9            [10]  170 	ret
                            171 ;src/man/game.c:85: void manGameCreateEnemy(Entity_t *e)
                            172 ;	---------------------------------
                            173 ; Function manGameCreateEnemy
                            174 ; ---------------------------------
   44C3                     175 _manGameCreateEnemy::
   44C3 DD E5         [15]  176 	push	ix
   44C5 DD 21 00 00   [14]  177 	ld	ix,#0
   44C9 DD 39         [15]  178 	add	ix,sp
                            179 ;src/man/game.c:87: if (enemy_on_lane) return;
   44CB 3A 31 4B      [13]  180 	ld	a,(#_enemy_on_lane + 0)
   44CE B7            [ 4]  181 	or	a, a
   44CF 20 2E         [12]  182 	jr	NZ,00103$
                            183 ;src/man/game.c:91: Entity_t *minion = manGameCreateFromTemplate (&enemy01_tmpl);
   44D1 21 68 44      [10]  184 	ld	hl, #_enemy01_tmpl
   44D4 E5            [11]  185 	push	hl
   44D5 CD A0 44      [17]  186 	call	_manGameCreateFromTemplate
   44D8 F1            [10]  187 	pop	af
   44D9 4D            [ 4]  188 	ld	c, l
   44DA 44            [ 4]  189 	ld	b, h
                            190 ;src/man/game.c:92: minion->x = e->x+4;
   44DB 59            [ 4]  191 	ld	e, c
   44DC 50            [ 4]  192 	ld	d, b
   44DD 13            [ 6]  193 	inc	de
   44DE E5            [11]  194 	push	hl
   44DF DD 6E 04      [19]  195 	ld	l, 4 (ix)
   44E2 DD 66 05      [19]  196 	ld	h, 5 (ix)
   44E5 E5            [11]  197 	push	hl
   44E6 FD E1         [14]  198 	pop	iy
   44E8 E1            [10]  199 	pop	hl
   44E9 FD E5         [15]  200 	push	iy
   44EB E1            [10]  201 	pop	hl
   44EC 23            [ 6]  202 	inc	hl
   44ED 7E            [ 7]  203 	ld	a, (hl)
   44EE C6 04         [ 7]  204 	add	a, #0x04
   44F0 12            [ 7]  205 	ld	(de), a
                            206 ;src/man/game.c:93: minion->vx = e->vx;
   44F1 03            [ 6]  207 	inc	bc
   44F2 03            [ 6]  208 	inc	bc
   44F3 03            [ 6]  209 	inc	bc
   44F4 03            [ 6]  210 	inc	bc
   44F5 03            [ 6]  211 	inc	bc
   44F6 FD 7E 05      [19]  212 	ld	a, 5 (iy)
   44F9 02            [ 7]  213 	ld	(bc), a
                            214 ;src/man/game.c:97: enemy_on_lane = 1;
   44FA 21 31 4B      [10]  215 	ld	hl,#_enemy_on_lane + 0
   44FD 36 01         [10]  216 	ld	(hl), #0x01
   44FF                     217 00103$:
   44FF DD E1         [14]  218 	pop	ix
   4501 C9            [10]  219 	ret
                            220 ;src/man/game.c:100: void manGameInit()
                            221 ;	---------------------------------
                            222 ; Function manGameInit
                            223 ; ---------------------------------
   4502                     224 _manGameInit::
   4502 DD E5         [15]  225 	push	ix
   4504 DD 21 00 00   [14]  226 	ld	ix,#0
   4508 DD 39         [15]  227 	add	ix,sp
   450A 21 EF FF      [10]  228 	ld	hl, #-17
   450D 39            [11]  229 	add	hl, sp
   450E F9            [ 6]  230 	ld	sp, hl
                            231 ;src/man/game.c:102: manEntityInit();
   450F CD 57 43      [17]  232 	call	_manEntityInit
                            233 ;src/man/game.c:103: sysRenderInit();
   4512 CD 3A 47      [17]  234 	call	_sysRenderInit
                            235 ;src/man/game.c:106: manGameCreateFromTemplate (&nave_nodriza_tmpl);
   4515 21 5A 44      [10]  236 	ld	hl, #_nave_nodriza_tmpl
   4518 E5            [11]  237 	push	hl
   4519 CD A0 44      [17]  238 	call	_manGameCreateFromTemplate
   451C F1            [10]  239 	pop	af
                            240 ;src/man/game.c:108: enemy_on_lane = 0;
   451D 21 31 4B      [10]  241 	ld	hl,#_enemy_on_lane + 0
   4520 36 00         [10]  242 	ld	(hl), #0x00
                            243 ;src/man/game.c:113: do {
   4522 0E 1E         [ 7]  244 	ld	c, #0x1e
   4524                     245 00101$:
                            246 ;src/man/game.c:114: Entity_t *e = 
   4524 C5            [11]  247 	push	bc
   4525 21 76 44      [10]  248 	ld	hl, #_nave_vidas_tmpl
   4528 E5            [11]  249 	push	hl
   4529 CD A0 44      [17]  250 	call	_manGameCreateFromTemplate
   452C F1            [10]  251 	pop	af
   452D C1            [10]  252 	pop	bc
                            253 ;src/man/game.c:116: x -= 10;
   452E 79            [ 4]  254 	ld	a, c
   452F C6 F6         [ 7]  255 	add	a, #0xf6
   4531 4F            [ 4]  256 	ld	c, a
                            257 ;src/man/game.c:117: e->x = x;
   4532 23            [ 6]  258 	inc	hl
   4533 71            [ 7]  259 	ld	(hl), c
                            260 ;src/man/game.c:118: } while (x);
   4534 79            [ 4]  261 	ld	a, c
   4535 B7            [ 4]  262 	or	a, a
   4536 20 EC         [12]  263 	jr	NZ,00101$
                            264 ;src/man/game.c:121: manGameCreateFromTemplate(&jugador_tmpl);
   4538 21 84 44      [10]  265 	ld	hl, #_jugador_tmpl
   453B E5            [11]  266 	push	hl
   453C CD A0 44      [17]  267 	call	_manGameCreateFromTemplate
   453F F1            [10]  268 	pop	af
                            269 ;src/man/game.c:127: do {
   4540 21 01 00      [10]  270 	ld	hl, #0x0001
   4543 39            [11]  271 	add	hl, sp
   4544 4D            [ 4]  272 	ld	c, l
   4545 44            [ 4]  273 	ld	b, h
   4546 DD 71 FE      [19]  274 	ld	-2 (ix), c
   4549 DD 70 FF      [19]  275 	ld	-1 (ix), b
   454C DD 36 EF 06   [19]  276 	ld	-17 (ix), #0x06
   4550                     277 00104$:
                            278 ;src/man/game.c:128: --d;        
   4550 DD 35 EF      [23]  279 	dec	-17 (ix)
                            280 ;src/man/game.c:129: cpct_memcpy(&num, &num_tmpl, sizeof(Entity_t));      
   4553 59            [ 4]  281 	ld	e, c
   4554 50            [ 4]  282 	ld	d, b
   4555 C5            [11]  283 	push	bc
   4556 21 0E 00      [10]  284 	ld	hl, #0x000e
   4559 E5            [11]  285 	push	hl
   455A 21 92 44      [10]  286 	ld	hl, #_num_tmpl
   455D E5            [11]  287 	push	hl
   455E D5            [11]  288 	push	de
   455F CD 83 49      [17]  289 	call	_cpct_memcpy
   4562 C1            [10]  290 	pop	bc
                            291 ;src/man/game.c:130: num.sprite += d * SPR_NUMEROS_00_H * SPR_NUMEROS_00_W;
   4563 FD 21 07 00   [14]  292 	ld	iy, #0x0007
   4567 FD 09         [15]  293 	add	iy, bc
   4569 FD 5E 00      [19]  294 	ld	e, 0 (iy)
   456C FD 56 01      [19]  295 	ld	d, 1 (iy)
   456F D5            [11]  296 	push	de
   4570 DD 5E EF      [19]  297 	ld	e,-17 (ix)
   4573 16 00         [ 7]  298 	ld	d,#0x00
   4575 6B            [ 4]  299 	ld	l, e
   4576 62            [ 4]  300 	ld	h, d
   4577 29            [11]  301 	add	hl, hl
   4578 19            [11]  302 	add	hl, de
   4579 29            [11]  303 	add	hl, hl
   457A 29            [11]  304 	add	hl, hl
   457B 29            [11]  305 	add	hl, hl
   457C D1            [10]  306 	pop	de
   457D 19            [11]  307 	add	hl, de
   457E FD 75 00      [19]  308 	ld	0 (iy), l
   4581 FD 74 01      [19]  309 	ld	1 (iy), h
                            310 ;src/man/game.c:131: num.x += d * (SPR_NUMEROS_00_W+2);
   4584 C5            [11]  311 	push	bc
   4585 FD E1         [14]  312 	pop	iy
   4587 FD 23         [10]  313 	inc	iy
   4589 FD 56 00      [19]  314 	ld	d, 0 (iy)
   458C DD 6E EF      [19]  315 	ld	l, -17 (ix)
   458F 5D            [ 4]  316 	ld	e, l
   4590 29            [11]  317 	add	hl, hl
   4591 29            [11]  318 	add	hl, hl
   4592 19            [11]  319 	add	hl, de
   4593 7A            [ 4]  320 	ld	a, d
   4594 85            [ 4]  321 	add	a, l
   4595 FD 77 00      [19]  322 	ld	0 (iy), a
                            323 ;src/man/game.c:132: manGameCreateFromTemplate(&num);
   4598 DD 5E FE      [19]  324 	ld	e,-2 (ix)
   459B DD 56 FF      [19]  325 	ld	d,-1 (ix)
   459E C5            [11]  326 	push	bc
   459F D5            [11]  327 	push	de
   45A0 CD A0 44      [17]  328 	call	_manGameCreateFromTemplate
   45A3 F1            [10]  329 	pop	af
   45A4 C1            [10]  330 	pop	bc
                            331 ;src/man/game.c:134: } while (d);
   45A5 DD 7E EF      [19]  332 	ld	a, -17 (ix)
   45A8 B7            [ 4]  333 	or	a, a
   45A9 20 A5         [12]  334 	jr	NZ,00104$
   45AB DD F9         [10]  335 	ld	sp, ix
   45AD DD E1         [14]  336 	pop	ix
   45AF C9            [10]  337 	ret
                            338 ;src/man/game.c:139: void manGamePlay()
                            339 ;	---------------------------------
                            340 ; Function manGamePlay
                            341 ; ---------------------------------
   45B0                     342 _manGamePlay::
                            343 ;src/man/game.c:141: while (1) {
   45B0                     344 00102$:
                            345 ;src/man/game.c:142: sysAIUpdate();
   45B0 CD 31 46      [17]  346 	call	_sysAIUpdate
                            347 ;src/man/game.c:143: sysPhysicsUpdate();
   45B3 CD 2C 47      [17]  348 	call	_sysPhysicsUpdate
                            349 ;src/man/game.c:144: sysAnimationUpdate();
   45B6 CD BE 46      [17]  350 	call	_sysAnimationUpdate
                            351 ;src/man/game.c:145: sysRenderUpdate();
   45B9 CD F2 47      [17]  352 	call	_sysRenderUpdate
                            353 ;src/man/game.c:146: manEntityUpdate();
   45BC CD 1B 44      [17]  354 	call	_manEntityUpdate
   45BF 18 EF         [12]  355 	jr	00102$
                            356 	.area _CODE
                            357 	.area _INITIALIZER
                            358 	.area _CABS (ABS)
