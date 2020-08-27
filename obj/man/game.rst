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
                             13 	.globl _sysAIUpdate
                             14 	.globl _sysRenderInit
                             15 	.globl _sysRenderUpdate
                             16 	.globl _sysPhysicsUpdate
                             17 	.globl _manEntityUpdate
                             18 	.globl _manEntityCreate
                             19 	.globl _manEntityInit
                             20 	.globl _cpct_waitVSYNC
                             21 	.globl _cpct_waitHalts
                             22 	.globl _cpct_memcpy
                             23 	.globl _num_tmpl
                             24 	.globl _jugador_tmpl
                             25 	.globl _nave_marcador_tmpl
                             26 	.globl _nave_nodriza_tmpl
                             27 	.globl _manGameInit
                             28 	.globl _manGamePlay
                             29 ;--------------------------------------------------------
                             30 ; special function registers
                             31 ;--------------------------------------------------------
                             32 ;--------------------------------------------------------
                             33 ; ram data
                             34 ;--------------------------------------------------------
                             35 	.area _DATA
                             36 ;--------------------------------------------------------
                             37 ; ram data
                             38 ;--------------------------------------------------------
                             39 	.area _INITIALIZED
                             40 ;--------------------------------------------------------
                             41 ; absolute external ram data
                             42 ;--------------------------------------------------------
                             43 	.area _DABS (ABS)
                             44 ;--------------------------------------------------------
                             45 ; global & static initialisations
                             46 ;--------------------------------------------------------
                             47 	.area _HOME
                             48 	.area _GSINIT
                             49 	.area _GSFINAL
                             50 	.area _GSINIT
                             51 ;--------------------------------------------------------
                             52 ; Home
                             53 ;--------------------------------------------------------
                             54 	.area _HOME
                             55 	.area _HOME
                             56 ;--------------------------------------------------------
                             57 ; code
                             58 ;--------------------------------------------------------
                             59 	.area _CODE
                             60 ;src/man/game.c:44: void wait(u8 n)
                             61 ;	---------------------------------
                             62 ; Function wait
                             63 ; ---------------------------------
   4377                      64 _wait::
                             65 ;src/man/game.c:46: do {
   4377 21 02 00      [10]   66 	ld	hl, #2+0
   437A 39            [11]   67 	add	hl, sp
   437B 4E            [ 7]   68 	ld	c, (hl)
   437C                      69 00101$:
                             70 ;src/man/game.c:47: cpct_waitHalts(n);
   437C C5            [11]   71 	push	bc
   437D 69            [ 4]   72 	ld	l, c
   437E CD 4C 47      [17]   73 	call	_cpct_waitHalts
   4381 CD 60 47      [17]   74 	call	_cpct_waitVSYNC
   4384 C1            [10]   75 	pop	bc
                             76 ;src/man/game.c:49: } while (--n);
   4385 0D            [ 4]   77 	dec c
   4386 20 F4         [12]   78 	jr	NZ,00101$
   4388 C9            [10]   79 	ret
   4389                      80 _nave_nodriza_tmpl:
   4389 0B                   81 	.db #0x0b	; 11
   438A 26                   82 	.db #0x26	; 38
   438B 12                   83 	.db #0x12	; 18
   438C 12                   84 	.db #0x12	; 18
   438D 10                   85 	.db #0x10	; 16
   438E FF                   86 	.db #0xff	; -1
   438F 00                   87 	.db #0x00	;  0
   4390 50 41                88 	.dw _spr_nave_nodriza
   4392                      89 _nave_marcador_tmpl:
   4392 01                   90 	.db #0x01	; 1
   4393 00                   91 	.db #0x00	; 0
   4394 C0                   92 	.db #0xc0	; 192
   4395 06                   93 	.db #0x06	; 6
   4396 08                   94 	.db #0x08	; 8
   4397 00                   95 	.db #0x00	;  0
   4398 00                   96 	.db #0x00	;  0
   4399 20 41                97 	.dw _spr_nave_jugador_1
   439B                      98 _jugador_tmpl:
   439B 07                   99 	.db #0x07	; 7
   439C 26                  100 	.db #0x26	; 38
   439D B0                  101 	.db #0xb0	; 176
   439E 06                  102 	.db #0x06	; 6
   439F 08                  103 	.db #0x08	; 8
   43A0 00                  104 	.db #0x00	;  0
   43A1 00                  105 	.db #0x00	;  0
   43A2 F0 40               106 	.dw _spr_nave_jugador_0
   43A4                     107 _num_tmpl:
   43A4 01                  108 	.db #0x01	; 1
   43A5 18                  109 	.db #0x18	; 24
   43A6 00                  110 	.db #0x00	; 0
   43A7 03                  111 	.db #0x03	; 3
   43A8 08                  112 	.db #0x08	; 8
   43A9 00                  113 	.db #0x00	;  0
   43AA 00                  114 	.db #0x00	;  0
   43AB 00 40               115 	.dw _spr_numeros_00
                            116 ;src/man/game.c:52: Entity_t *manGameCreateFromTemplate(const Entity_t *tmpl)
                            117 ;	---------------------------------
                            118 ; Function manGameCreateFromTemplate
                            119 ; ---------------------------------
   43AD                     120 _manGameCreateFromTemplate::
   43AD DD E5         [15]  121 	push	ix
   43AF DD 21 00 00   [14]  122 	ld	ix,#0
   43B3 DD 39         [15]  123 	add	ix,sp
                            124 ;src/man/game.c:54: Entity_t *e = manEntityCreate();
   43B5 CD A8 42      [17]  125 	call	_manEntityCreate
                            126 ;src/man/game.c:55: cpct_memcpy (e, tmpl, sizeof (Entity_t));
   43B8 DD 4E 04      [19]  127 	ld	c,4 (ix)
   43BB DD 46 05      [19]  128 	ld	b,5 (ix)
   43BE E5            [11]  129 	push	hl
   43BF FD E1         [14]  130 	pop	iy
   43C1 E5            [11]  131 	push	hl
   43C2 11 09 00      [10]  132 	ld	de, #0x0009
   43C5 D5            [11]  133 	push	de
   43C6 C5            [11]  134 	push	bc
   43C7 FD E5         [15]  135 	push	iy
   43C9 CD 84 47      [17]  136 	call	_cpct_memcpy
   43CC E1            [10]  137 	pop	hl
                            138 ;src/man/game.c:56: return e;    
   43CD DD E1         [14]  139 	pop	ix
   43CF C9            [10]  140 	ret
                            141 ;src/man/game.c:59: void manGameInit()
                            142 ;	---------------------------------
                            143 ; Function manGameInit
                            144 ; ---------------------------------
   43D0                     145 _manGameInit::
   43D0 DD E5         [15]  146 	push	ix
   43D2 DD 21 00 00   [14]  147 	ld	ix,#0
   43D6 DD 39         [15]  148 	add	ix,sp
   43D8 21 F4 FF      [10]  149 	ld	hl, #-12
   43DB 39            [11]  150 	add	hl, sp
   43DC F9            [ 6]  151 	ld	sp, hl
                            152 ;src/man/game.c:61: manEntityInit();
   43DD CD 86 42      [17]  153 	call	_manEntityInit
                            154 ;src/man/game.c:62: sysRenderInit();
   43E0 CD 3B 45      [17]  155 	call	_sysRenderInit
                            156 ;src/man/game.c:64: manGameCreateFromTemplate (&nave_nodriza_tmpl);
   43E3 21 89 43      [10]  157 	ld	hl, #_nave_nodriza_tmpl
   43E6 E5            [11]  158 	push	hl
   43E7 CD AD 43      [17]  159 	call	_manGameCreateFromTemplate
   43EA F1            [10]  160 	pop	af
                            161 ;src/man/game.c:69: do {
   43EB 0E 1E         [ 7]  162 	ld	c, #0x1e
   43ED                     163 00101$:
                            164 ;src/man/game.c:70: Entity_t *e = 
   43ED C5            [11]  165 	push	bc
   43EE 21 92 43      [10]  166 	ld	hl, #_nave_marcador_tmpl
   43F1 E5            [11]  167 	push	hl
   43F2 CD AD 43      [17]  168 	call	_manGameCreateFromTemplate
   43F5 F1            [10]  169 	pop	af
   43F6 C1            [10]  170 	pop	bc
                            171 ;src/man/game.c:72: x -= 10;
   43F7 79            [ 4]  172 	ld	a, c
   43F8 C6 F6         [ 7]  173 	add	a, #0xf6
   43FA 4F            [ 4]  174 	ld	c, a
                            175 ;src/man/game.c:73: e->x = x;
   43FB 23            [ 6]  176 	inc	hl
   43FC 71            [ 7]  177 	ld	(hl), c
                            178 ;src/man/game.c:74: } while (x);
   43FD 79            [ 4]  179 	ld	a, c
   43FE B7            [ 4]  180 	or	a, a
   43FF 20 EC         [12]  181 	jr	NZ,00101$
                            182 ;src/man/game.c:77: manGameCreateFromTemplate(&jugador_tmpl);
   4401 21 9B 43      [10]  183 	ld	hl, #_jugador_tmpl
   4404 E5            [11]  184 	push	hl
   4405 CD AD 43      [17]  185 	call	_manGameCreateFromTemplate
   4408 F1            [10]  186 	pop	af
                            187 ;src/man/game.c:83: do {
   4409 21 01 00      [10]  188 	ld	hl, #0x0001
   440C 39            [11]  189 	add	hl, sp
   440D 4D            [ 4]  190 	ld	c, l
   440E 44            [ 4]  191 	ld	b, h
   440F DD 71 FE      [19]  192 	ld	-2 (ix), c
   4412 DD 70 FF      [19]  193 	ld	-1 (ix), b
   4415 DD 36 F4 06   [19]  194 	ld	-12 (ix), #0x06
   4419                     195 00104$:
                            196 ;src/man/game.c:84: --d;        
   4419 DD 35 F4      [23]  197 	dec	-12 (ix)
                            198 ;src/man/game.c:85: cpct_memcpy(&num, &num_tmpl, sizeof(Entity_t));      
   441C 59            [ 4]  199 	ld	e, c
   441D 50            [ 4]  200 	ld	d, b
   441E C5            [11]  201 	push	bc
   441F 21 09 00      [10]  202 	ld	hl, #0x0009
   4422 E5            [11]  203 	push	hl
   4423 21 A4 43      [10]  204 	ld	hl, #_num_tmpl
   4426 E5            [11]  205 	push	hl
   4427 D5            [11]  206 	push	de
   4428 CD 84 47      [17]  207 	call	_cpct_memcpy
   442B C1            [10]  208 	pop	bc
                            209 ;src/man/game.c:86: num.sprite += d * SPR_NUMEROS_00_H * SPR_NUMEROS_00_W;
   442C FD 21 07 00   [14]  210 	ld	iy, #0x0007
   4430 FD 09         [15]  211 	add	iy, bc
   4432 FD 5E 00      [19]  212 	ld	e, 0 (iy)
   4435 FD 56 01      [19]  213 	ld	d, 1 (iy)
   4438 D5            [11]  214 	push	de
   4439 DD 5E F4      [19]  215 	ld	e,-12 (ix)
   443C 16 00         [ 7]  216 	ld	d,#0x00
   443E 6B            [ 4]  217 	ld	l, e
   443F 62            [ 4]  218 	ld	h, d
   4440 29            [11]  219 	add	hl, hl
   4441 19            [11]  220 	add	hl, de
   4442 29            [11]  221 	add	hl, hl
   4443 29            [11]  222 	add	hl, hl
   4444 29            [11]  223 	add	hl, hl
   4445 D1            [10]  224 	pop	de
   4446 19            [11]  225 	add	hl, de
   4447 FD 75 00      [19]  226 	ld	0 (iy), l
   444A FD 74 01      [19]  227 	ld	1 (iy), h
                            228 ;src/man/game.c:87: num.x += d * (SPR_NUMEROS_00_W+2);
   444D C5            [11]  229 	push	bc
   444E FD E1         [14]  230 	pop	iy
   4450 FD 23         [10]  231 	inc	iy
   4452 FD 56 00      [19]  232 	ld	d, 0 (iy)
   4455 DD 6E F4      [19]  233 	ld	l, -12 (ix)
   4458 5D            [ 4]  234 	ld	e, l
   4459 29            [11]  235 	add	hl, hl
   445A 29            [11]  236 	add	hl, hl
   445B 19            [11]  237 	add	hl, de
   445C 7A            [ 4]  238 	ld	a, d
   445D 85            [ 4]  239 	add	a, l
   445E FD 77 00      [19]  240 	ld	0 (iy), a
                            241 ;src/man/game.c:88: manGameCreateFromTemplate(&num);
   4461 DD 5E FE      [19]  242 	ld	e,-2 (ix)
   4464 DD 56 FF      [19]  243 	ld	d,-1 (ix)
   4467 C5            [11]  244 	push	bc
   4468 D5            [11]  245 	push	de
   4469 CD AD 43      [17]  246 	call	_manGameCreateFromTemplate
   446C F1            [10]  247 	pop	af
   446D C1            [10]  248 	pop	bc
                            249 ;src/man/game.c:90: } while (d);
   446E DD 7E F4      [19]  250 	ld	a, -12 (ix)
   4471 B7            [ 4]  251 	or	a, a
   4472 20 A5         [12]  252 	jr	NZ,00104$
   4474 DD F9         [10]  253 	ld	sp, ix
   4476 DD E1         [14]  254 	pop	ix
   4478 C9            [10]  255 	ret
                            256 ;src/man/game.c:96: void manGamePlay()
                            257 ;	---------------------------------
                            258 ; Function manGamePlay
                            259 ; ---------------------------------
   4479                     260 _manGamePlay::
                            261 ;src/man/game.c:98: while (1) {
   4479                     262 00102$:
                            263 ;src/man/game.c:99: sysAIUpdate();
   4479 CD BF 44      [17]  264 	call	_sysAIUpdate
                            265 ;src/man/game.c:100: sysPhysicsUpdate();   
   447C CD 2D 45      [17]  266 	call	_sysPhysicsUpdate
                            267 ;src/man/game.c:101: sysRenderUpdate();
   447F CD F3 45      [17]  268 	call	_sysRenderUpdate
                            269 ;src/man/game.c:102: manEntityUpdate();
   4482 CD 4A 43      [17]  270 	call	_manEntityUpdate
   4485 18 F2         [12]  271 	jr	00102$
                            272 	.area _CODE
                            273 	.area _INITIALIZER
                            274 	.area _CABS (ABS)
