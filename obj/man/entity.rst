                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 3.6.8 #9946 (Linux)
                              4 ;--------------------------------------------------------
                              5 	.module entity
                              6 	.optsdcc -mz80
                              7 	
                              8 ;--------------------------------------------------------
                              9 ; Public variables in this module
                             10 ;--------------------------------------------------------
                             11 	.globl _manEntityDestroy
                             12 	.globl _cpct_memcpy
                             13 	.globl _cpct_memset
                             14 	.globl _m_entities_end
                             15 	.globl _m_next_free
                             16 	.globl _m_invalid
                             17 	.globl _m_entities
                             18 	.globl _manEntityInit
                             19 	.globl _manEntityCreate
                             20 	.globl _manEntityForAll
                             21 	.globl _manEntityForAllMatching
                             22 	.globl _manEntityDelete
                             23 	.globl _manEntityUpdate
                             24 	.globl _manEntityAvailable
                             25 ;--------------------------------------------------------
                             26 ; special function registers
                             27 ;--------------------------------------------------------
                             28 ;--------------------------------------------------------
                             29 ; ram data
                             30 ;--------------------------------------------------------
                             31 	.area _DATA
   4A84                      32 _m_entities::
   4A84                      33 	.ds 168
   4B2C                      34 _m_invalid::
   4B2C                      35 	.ds 1
   4B2D                      36 _m_next_free::
   4B2D                      37 	.ds 2
   4B2F                      38 _m_entities_end::
   4B2F                      39 	.ds 2
                             40 ;--------------------------------------------------------
                             41 ; ram data
                             42 ;--------------------------------------------------------
                             43 	.area _INITIALIZED
                             44 ;--------------------------------------------------------
                             45 ; absolute external ram data
                             46 ;--------------------------------------------------------
                             47 	.area _DABS (ABS)
                             48 ;--------------------------------------------------------
                             49 ; global & static initialisations
                             50 ;--------------------------------------------------------
                             51 	.area _HOME
                             52 	.area _GSINIT
                             53 	.area _GSFINAL
                             54 	.area _GSINIT
                             55 ;--------------------------------------------------------
                             56 ; Home
                             57 ;--------------------------------------------------------
                             58 	.area _HOME
                             59 	.area _HOME
                             60 ;--------------------------------------------------------
                             61 ; code
                             62 ;--------------------------------------------------------
                             63 	.area _CODE
                             64 ;src/man/entity.c:10: void manEntityInit() { 
                             65 ;	---------------------------------
                             66 ; Function manEntityInit
                             67 ; ---------------------------------
   4357                      68 _manEntityInit::
                             69 ;src/man/entity.c:11: m_next_free = m_entities; 
   4357 01 84 4A      [10]   70 	ld	bc, #_m_entities+0
   435A ED 43 2D 4B   [20]   71 	ld	(_m_next_free), bc
                             72 ;src/man/entity.c:12: m_invalid = E_TYPE_INVALID;
   435E 21 2C 4B      [10]   73 	ld	hl,#_m_invalid + 0
   4361 36 00         [10]   74 	ld	(hl), #0x00
                             75 ;src/man/entity.c:13: m_entities_end = m_entities + MAX_ENTITIES;
   4363 21 A8 00      [10]   76 	ld	hl, #0x00a8
   4366 09            [11]   77 	add	hl, bc
   4367 22 2F 4B      [16]   78 	ld	(_m_entities_end), hl
                             79 ;src/man/entity.c:14: cpct_memset(m_next_free, 0, sizeof(m_entities));
   436A 21 A8 00      [10]   80 	ld	hl, #0x00a8
   436D E5            [11]   81 	push	hl
   436E AF            [ 4]   82 	xor	a, a
   436F F5            [11]   83 	push	af
   4370 33            [ 6]   84 	inc	sp
   4371 21 84 4A      [10]   85 	ld	hl, #_m_entities
   4374 E5            [11]   86 	push	hl
   4375 CD 8B 49      [17]   87 	call	_cpct_memset
   4378 C9            [10]   88 	ret
                             89 ;src/man/entity.c:17: Entity_t *manEntityCreate() {
                             90 ;	---------------------------------
                             91 ; Function manEntityCreate
                             92 ; ---------------------------------
   4379                      93 _manEntityCreate::
                             94 ;src/man/entity.c:18: Entity_t *next = m_next_free;
   4379 ED 4B 2D 4B   [20]   95 	ld	bc, (_m_next_free)
                             96 ;src/man/entity.c:19: m_next_free = next + 1;
   437D 21 0E 00      [10]   97 	ld	hl, #0x000e
   4380 09            [11]   98 	add	hl,bc
   4381 22 2D 4B      [16]   99 	ld	(_m_next_free), hl
                            100 ;src/man/entity.c:20: next->type = E_TYPE_DEFAULT;
   4384 3E 7F         [ 7]  101 	ld	a, #0x7f
   4386 02            [ 7]  102 	ld	(bc), a
                            103 ;src/man/entity.c:21: return next;
   4387 69            [ 4]  104 	ld	l, c
   4388 60            [ 4]  105 	ld	h, b
   4389 C9            [10]  106 	ret
                            107 ;src/man/entity.c:24: void manEntityForAll(UpdateEntityFn_t fnUpdateEntity) {
                            108 ;	---------------------------------
                            109 ; Function manEntityForAll
                            110 ; ---------------------------------
   438A                     111 _manEntityForAll::
                            112 ;src/man/entity.c:25: Entity_t *e = m_entities;
   438A 01 84 4A      [10]  113 	ld	bc, #_m_entities+0
                            114 ;src/man/entity.c:26: while (e->type != E_TYPE_INVALID) {
   438D                     115 00101$:
   438D 0A            [ 7]  116 	ld	a, (bc)
   438E B7            [ 4]  117 	or	a, a
   438F C8            [11]  118 	ret	Z
                            119 ;src/man/entity.c:27: fnUpdateEntity(e++);
   4390 59            [ 4]  120 	ld	e, c
   4391 50            [ 4]  121 	ld	d, b
   4392 21 0E 00      [10]  122 	ld	hl, #0x000e
   4395 09            [11]  123 	add	hl,bc
   4396 E5            [11]  124 	push	hl
   4397 D5            [11]  125 	push	de
   4398 21 06 00      [10]  126 	ld	hl, #6
   439B 39            [11]  127 	add	hl, sp
   439C 7E            [ 7]  128 	ld	a, (hl)
   439D 23            [ 6]  129 	inc	hl
   439E 66            [ 7]  130 	ld	h, (hl)
   439F 6F            [ 4]  131 	ld	l, a
   43A0 CD 50 49      [17]  132 	call	___sdcc_call_hl
   43A3 F1            [10]  133 	pop	af
   43A4 C1            [10]  134 	pop	bc
   43A5 18 E6         [12]  135 	jr	00101$
                            136 ;src/man/entity.c:31: void manEntityForAllMatching(
                            137 ;	---------------------------------
                            138 ; Function manEntityForAllMatching
                            139 ; ---------------------------------
   43A7                     140 _manEntityForAllMatching::
                            141 ;src/man/entity.c:35: Entity_t *e = m_entities;  
   43A7 01 84 4A      [10]  142 	ld	bc, #_m_entities+0
                            143 ;src/man/entity.c:36: while (e->type != E_TYPE_INVALID) {
   43AA                     144 00103$:
   43AA 0A            [ 7]  145 	ld	a, (bc)
   43AB B7            [ 4]  146 	or	a, a
   43AC C8            [11]  147 	ret	Z
                            148 ;src/man/entity.c:37: if ((e->type & signature) == signature)
   43AD FD 21 04 00   [14]  149 	ld	iy, #4
   43B1 FD 39         [15]  150 	add	iy, sp
   43B3 FD A6 00      [19]  151 	and	a, 0 (iy)
   43B6 5F            [ 4]  152 	ld	e, a
   43B7 FD 7E 00      [19]  153 	ld	a, 0 (iy)
   43BA 93            [ 4]  154 	sub	a, e
   43BB 20 0F         [12]  155 	jr	NZ,00102$
                            156 ;src/man/entity.c:38: fnUpdateEntity(e);
   43BD C5            [11]  157 	push	bc
   43BE C5            [11]  158 	push	bc
   43BF 21 06 00      [10]  159 	ld	hl, #6
   43C2 39            [11]  160 	add	hl, sp
   43C3 7E            [ 7]  161 	ld	a, (hl)
   43C4 23            [ 6]  162 	inc	hl
   43C5 66            [ 7]  163 	ld	h, (hl)
   43C6 6F            [ 4]  164 	ld	l, a
   43C7 CD 50 49      [17]  165 	call	___sdcc_call_hl
   43CA F1            [10]  166 	pop	af
   43CB C1            [10]  167 	pop	bc
   43CC                     168 00102$:
                            169 ;src/man/entity.c:39: e++;
   43CC 21 0E 00      [10]  170 	ld	hl, #0x000e
   43CF 09            [11]  171 	add	hl,bc
   43D0 4D            [ 4]  172 	ld	c, l
   43D1 44            [ 4]  173 	ld	b, h
   43D2 18 D6         [12]  174 	jr	00103$
                            175 ;src/man/entity.c:44: void manEntityDestroy(Entity_t *e) {
                            176 ;	---------------------------------
                            177 ; Function manEntityDestroy
                            178 ; ---------------------------------
   43D4                     179 _manEntityDestroy::
   43D4 DD E5         [15]  180 	push	ix
   43D6 DD 21 00 00   [14]  181 	ld	ix,#0
   43DA DD 39         [15]  182 	add	ix,sp
                            183 ;src/man/entity.c:45: Entity_t *dead_e = e;
   43DC DD 4E 04      [19]  184 	ld	c,4 (ix)
   43DF DD 46 05      [19]  185 	ld	b,5 (ix)
                            186 ;src/man/entity.c:46: --m_next_free;
   43E2 21 2D 4B      [10]  187 	ld	hl, #_m_next_free
   43E5 7E            [ 7]  188 	ld	a, (hl)
   43E6 C6 F2         [ 7]  189 	add	a, #0xf2
   43E8 77            [ 7]  190 	ld	(hl), a
   43E9 23            [ 6]  191 	inc	hl
   43EA 7E            [ 7]  192 	ld	a, (hl)
   43EB CE FF         [ 7]  193 	adc	a, #0xff
   43ED 77            [ 7]  194 	ld	(hl), a
                            195 ;src/man/entity.c:48: if (dead_e != m_next_free)
   43EE FD 21 2D 4B   [14]  196 	ld	iy, #_m_next_free
   43F2 FD 7E 00      [19]  197 	ld	a, 0 (iy)
   43F5 91            [ 4]  198 	sub	a, c
   43F6 20 06         [12]  199 	jr	NZ,00109$
   43F8 FD 7E 01      [19]  200 	ld	a, 1 (iy)
   43FB 90            [ 4]  201 	sub	a, b
   43FC 28 0C         [12]  202 	jr	Z,00102$
   43FE                     203 00109$:
                            204 ;src/man/entity.c:49: cpct_memcpy(dead_e, m_next_free, sizeof(Entity_t));
   43FE 2A 2D 4B      [16]  205 	ld	hl, (_m_next_free)
   4401 11 0E 00      [10]  206 	ld	de, #0x000e
   4404 D5            [11]  207 	push	de
   4405 E5            [11]  208 	push	hl
   4406 C5            [11]  209 	push	bc
   4407 CD 83 49      [17]  210 	call	_cpct_memcpy
   440A                     211 00102$:
                            212 ;src/man/entity.c:51: m_next_free->type = E_TYPE_INVALID;
   440A 2A 2D 4B      [16]  213 	ld	hl, (_m_next_free)
   440D 36 00         [10]  214 	ld	(hl), #0x00
   440F DD E1         [14]  215 	pop	ix
   4411 C9            [10]  216 	ret
                            217 ;src/man/entity.c:54: void manEntityDelete(Entity_t *e)
                            218 ;	---------------------------------
                            219 ; Function manEntityDelete
                            220 ; ---------------------------------
   4412                     221 _manEntityDelete::
                            222 ;src/man/entity.c:56: e->type |= E_TYPE_DEAD;
   4412 D1            [10]  223 	pop	de
   4413 C1            [10]  224 	pop	bc
   4414 C5            [11]  225 	push	bc
   4415 D5            [11]  226 	push	de
   4416 0A            [ 7]  227 	ld	a, (bc)
   4417 CB FF         [ 8]  228 	set	7, a
   4419 02            [ 7]  229 	ld	(bc), a
   441A C9            [10]  230 	ret
                            231 ;src/man/entity.c:59: void manEntityUpdate()
                            232 ;	---------------------------------
                            233 ; Function manEntityUpdate
                            234 ; ---------------------------------
   441B                     235 _manEntityUpdate::
                            236 ;src/man/entity.c:61: Entity_t *e = m_entities;
   441B 21 84 4A      [10]  237 	ld	hl, #_m_entities+0
                            238 ;src/man/entity.c:62: while (e->type != E_TYPE_INVALID) {
   441E                     239 00104$:
   441E 7E            [ 7]  240 	ld	a, (hl)
   441F B7            [ 4]  241 	or	a, a
   4420 C8            [11]  242 	ret	Z
                            243 ;src/man/entity.c:63: if (e->type & E_TYPE_DEAD) {
   4421 07            [ 4]  244 	rlca
   4422 30 09         [12]  245 	jr	NC,00102$
                            246 ;src/man/entity.c:64: manEntityDestroy(e);
   4424 E5            [11]  247 	push	hl
   4425 E5            [11]  248 	push	hl
   4426 CD D4 43      [17]  249 	call	_manEntityDestroy
   4429 F1            [10]  250 	pop	af
   442A E1            [10]  251 	pop	hl
   442B 18 F1         [12]  252 	jr	00104$
   442D                     253 00102$:
                            254 ;src/man/entity.c:67: ++e;
   442D 01 0E 00      [10]  255 	ld	bc, #0x000e
   4430 09            [11]  256 	add	hl, bc
   4431 18 EB         [12]  257 	jr	00104$
                            258 ;src/man/entity.c:72: u8 manEntityAvailable()
                            259 ;	---------------------------------
                            260 ; Function manEntityAvailable
                            261 ; ---------------------------------
   4433                     262 _manEntityAvailable::
                            263 ;src/man/entity.c:74: return (m_next_free < m_entities_end);
   4433 21 2F 4B      [10]  264 	ld	hl, #_m_entities_end
   4436 FD 21 2D 4B   [14]  265 	ld	iy, #_m_next_free
   443A FD 7E 00      [19]  266 	ld	a, 0 (iy)
   443D 96            [ 7]  267 	sub	a, (hl)
   443E FD 7E 01      [19]  268 	ld	a, 1 (iy)
   4441 23            [ 6]  269 	inc	hl
   4442 9E            [ 7]  270 	sbc	a, (hl)
   4443 3E 00         [ 7]  271 	ld	a, #0x00
   4445 17            [ 4]  272 	rla
   4446 6F            [ 4]  273 	ld	l, a
   4447 C9            [10]  274 	ret
                            275 	.area _CODE
                            276 	.area _INITIALIZER
                            277 	.area _CABS (ABS)
