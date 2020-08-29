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
   4B2A                      32 _m_entities::
   4B2A                      33 	.ds 192
   4BEA                      34 _m_invalid::
   4BEA                      35 	.ds 1
   4BEB                      36 _m_next_free::
   4BEB                      37 	.ds 2
   4BED                      38 _m_entities_end::
   4BED                      39 	.ds 2
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
   437B                      68 _manEntityInit::
                             69 ;src/man/entity.c:11: m_next_free = m_entities; 
   437B 01 2A 4B      [10]   70 	ld	bc, #_m_entities+0
   437E ED 43 EB 4B   [20]   71 	ld	(_m_next_free), bc
                             72 ;src/man/entity.c:12: m_invalid = E_TYPE_INVALID;
   4382 21 EA 4B      [10]   73 	ld	hl,#_m_invalid + 0
   4385 36 00         [10]   74 	ld	(hl), #0x00
                             75 ;src/man/entity.c:13: m_entities_end = m_entities + MAX_ENTITIES;
   4387 21 C0 00      [10]   76 	ld	hl, #0x00c0
   438A 09            [11]   77 	add	hl, bc
   438B 22 ED 4B      [16]   78 	ld	(_m_entities_end), hl
                             79 ;src/man/entity.c:14: cpct_memset(m_next_free, 0, sizeof(m_entities));
   438E 21 C0 00      [10]   80 	ld	hl, #0x00c0
   4391 E5            [11]   81 	push	hl
   4392 AF            [ 4]   82 	xor	a, a
   4393 F5            [11]   83 	push	af
   4394 33            [ 6]   84 	inc	sp
   4395 21 2A 4B      [10]   85 	ld	hl, #_m_entities
   4398 E5            [11]   86 	push	hl
   4399 CD 31 4A      [17]   87 	call	_cpct_memset
   439C C9            [10]   88 	ret
                             89 ;src/man/entity.c:17: Entity_t *manEntityCreate() {
                             90 ;	---------------------------------
                             91 ; Function manEntityCreate
                             92 ; ---------------------------------
   439D                      93 _manEntityCreate::
                             94 ;src/man/entity.c:18: Entity_t *next = m_next_free;
   439D ED 4B EB 4B   [20]   95 	ld	bc, (_m_next_free)
                             96 ;src/man/entity.c:19: m_next_free = next + 1;
   43A1 21 10 00      [10]   97 	ld	hl, #0x0010
   43A4 09            [11]   98 	add	hl,bc
   43A5 22 EB 4B      [16]   99 	ld	(_m_next_free), hl
                            100 ;src/man/entity.c:20: next->type = E_TYPE_DEFAULT;
   43A8 3E 7F         [ 7]  101 	ld	a, #0x7f
   43AA 02            [ 7]  102 	ld	(bc), a
                            103 ;src/man/entity.c:21: return next;
   43AB 69            [ 4]  104 	ld	l, c
   43AC 60            [ 4]  105 	ld	h, b
   43AD C9            [10]  106 	ret
                            107 ;src/man/entity.c:24: void manEntityForAll(UpdateEntityFn_t fnUpdateEntity) {
                            108 ;	---------------------------------
                            109 ; Function manEntityForAll
                            110 ; ---------------------------------
   43AE                     111 _manEntityForAll::
                            112 ;src/man/entity.c:25: Entity_t *e = m_entities;
   43AE 01 2A 4B      [10]  113 	ld	bc, #_m_entities+0
                            114 ;src/man/entity.c:26: while (e->type != E_TYPE_INVALID) {
   43B1                     115 00101$:
   43B1 0A            [ 7]  116 	ld	a, (bc)
   43B2 B7            [ 4]  117 	or	a, a
   43B3 C8            [11]  118 	ret	Z
                            119 ;src/man/entity.c:27: fnUpdateEntity(e++);
   43B4 59            [ 4]  120 	ld	e, c
   43B5 50            [ 4]  121 	ld	d, b
   43B6 21 10 00      [10]  122 	ld	hl, #0x0010
   43B9 09            [11]  123 	add	hl,bc
   43BA E5            [11]  124 	push	hl
   43BB D5            [11]  125 	push	de
   43BC 21 06 00      [10]  126 	ld	hl, #6
   43BF 39            [11]  127 	add	hl, sp
   43C0 7E            [ 7]  128 	ld	a, (hl)
   43C1 23            [ 6]  129 	inc	hl
   43C2 66            [ 7]  130 	ld	h, (hl)
   43C3 6F            [ 4]  131 	ld	l, a
   43C4 CD F6 49      [17]  132 	call	___sdcc_call_hl
   43C7 F1            [10]  133 	pop	af
   43C8 C1            [10]  134 	pop	bc
   43C9 18 E6         [12]  135 	jr	00101$
                            136 ;src/man/entity.c:31: void manEntityForAllMatching(
                            137 ;	---------------------------------
                            138 ; Function manEntityForAllMatching
                            139 ; ---------------------------------
   43CB                     140 _manEntityForAllMatching::
                            141 ;src/man/entity.c:35: Entity_t *e = m_entities;  
   43CB 01 2A 4B      [10]  142 	ld	bc, #_m_entities+0
                            143 ;src/man/entity.c:36: while (e->type != E_TYPE_INVALID) {
   43CE                     144 00103$:
   43CE 0A            [ 7]  145 	ld	a, (bc)
   43CF B7            [ 4]  146 	or	a, a
   43D0 C8            [11]  147 	ret	Z
                            148 ;src/man/entity.c:37: if ((e->type & signature) == signature)
   43D1 FD 21 04 00   [14]  149 	ld	iy, #4
   43D5 FD 39         [15]  150 	add	iy, sp
   43D7 FD A6 00      [19]  151 	and	a, 0 (iy)
   43DA 5F            [ 4]  152 	ld	e, a
   43DB FD 7E 00      [19]  153 	ld	a, 0 (iy)
   43DE 93            [ 4]  154 	sub	a, e
   43DF 20 0F         [12]  155 	jr	NZ,00102$
                            156 ;src/man/entity.c:38: fnUpdateEntity(e);
   43E1 C5            [11]  157 	push	bc
   43E2 C5            [11]  158 	push	bc
   43E3 21 06 00      [10]  159 	ld	hl, #6
   43E6 39            [11]  160 	add	hl, sp
   43E7 7E            [ 7]  161 	ld	a, (hl)
   43E8 23            [ 6]  162 	inc	hl
   43E9 66            [ 7]  163 	ld	h, (hl)
   43EA 6F            [ 4]  164 	ld	l, a
   43EB CD F6 49      [17]  165 	call	___sdcc_call_hl
   43EE F1            [10]  166 	pop	af
   43EF C1            [10]  167 	pop	bc
   43F0                     168 00102$:
                            169 ;src/man/entity.c:39: e++;
   43F0 21 10 00      [10]  170 	ld	hl, #0x0010
   43F3 09            [11]  171 	add	hl,bc
   43F4 4D            [ 4]  172 	ld	c, l
   43F5 44            [ 4]  173 	ld	b, h
   43F6 18 D6         [12]  174 	jr	00103$
                            175 ;src/man/entity.c:44: void manEntityDestroy(Entity_t *e) {
                            176 ;	---------------------------------
                            177 ; Function manEntityDestroy
                            178 ; ---------------------------------
   43F8                     179 _manEntityDestroy::
   43F8 DD E5         [15]  180 	push	ix
   43FA DD 21 00 00   [14]  181 	ld	ix,#0
   43FE DD 39         [15]  182 	add	ix,sp
                            183 ;src/man/entity.c:45: Entity_t *dead_e = e;
   4400 DD 4E 04      [19]  184 	ld	c,4 (ix)
   4403 DD 46 05      [19]  185 	ld	b,5 (ix)
                            186 ;src/man/entity.c:46: --m_next_free;
   4406 21 EB 4B      [10]  187 	ld	hl, #_m_next_free
   4409 7E            [ 7]  188 	ld	a, (hl)
   440A C6 F0         [ 7]  189 	add	a, #0xf0
   440C 77            [ 7]  190 	ld	(hl), a
   440D 23            [ 6]  191 	inc	hl
   440E 7E            [ 7]  192 	ld	a, (hl)
   440F CE FF         [ 7]  193 	adc	a, #0xff
   4411 77            [ 7]  194 	ld	(hl), a
                            195 ;src/man/entity.c:48: if (dead_e != m_next_free)
   4412 FD 21 EB 4B   [14]  196 	ld	iy, #_m_next_free
   4416 FD 7E 00      [19]  197 	ld	a, 0 (iy)
   4419 91            [ 4]  198 	sub	a, c
   441A 20 06         [12]  199 	jr	NZ,00109$
   441C FD 7E 01      [19]  200 	ld	a, 1 (iy)
   441F 90            [ 4]  201 	sub	a, b
   4420 28 0C         [12]  202 	jr	Z,00102$
   4422                     203 00109$:
                            204 ;src/man/entity.c:49: cpct_memcpy(dead_e, m_next_free, sizeof(Entity_t));
   4422 2A EB 4B      [16]  205 	ld	hl, (_m_next_free)
   4425 11 10 00      [10]  206 	ld	de, #0x0010
   4428 D5            [11]  207 	push	de
   4429 E5            [11]  208 	push	hl
   442A C5            [11]  209 	push	bc
   442B CD 29 4A      [17]  210 	call	_cpct_memcpy
   442E                     211 00102$:
                            212 ;src/man/entity.c:51: m_next_free->type = E_TYPE_INVALID;
   442E 2A EB 4B      [16]  213 	ld	hl, (_m_next_free)
   4431 36 00         [10]  214 	ld	(hl), #0x00
   4433 DD E1         [14]  215 	pop	ix
   4435 C9            [10]  216 	ret
                            217 ;src/man/entity.c:54: void manEntityDelete(Entity_t *e)
                            218 ;	---------------------------------
                            219 ; Function manEntityDelete
                            220 ; ---------------------------------
   4436                     221 _manEntityDelete::
                            222 ;src/man/entity.c:56: e->type |= E_TYPE_DEAD;
   4436 D1            [10]  223 	pop	de
   4437 C1            [10]  224 	pop	bc
   4438 C5            [11]  225 	push	bc
   4439 D5            [11]  226 	push	de
   443A 0A            [ 7]  227 	ld	a, (bc)
   443B CB FF         [ 8]  228 	set	7, a
   443D 02            [ 7]  229 	ld	(bc), a
   443E C9            [10]  230 	ret
                            231 ;src/man/entity.c:59: void manEntityUpdate()
                            232 ;	---------------------------------
                            233 ; Function manEntityUpdate
                            234 ; ---------------------------------
   443F                     235 _manEntityUpdate::
                            236 ;src/man/entity.c:61: Entity_t *e = m_entities;
   443F 21 2A 4B      [10]  237 	ld	hl, #_m_entities+0
                            238 ;src/man/entity.c:62: while (e->type != E_TYPE_INVALID) {
   4442                     239 00104$:
   4442 7E            [ 7]  240 	ld	a, (hl)
   4443 B7            [ 4]  241 	or	a, a
   4444 C8            [11]  242 	ret	Z
                            243 ;src/man/entity.c:63: if (e->type & E_TYPE_DEAD) {
   4445 07            [ 4]  244 	rlca
   4446 30 09         [12]  245 	jr	NC,00102$
                            246 ;src/man/entity.c:64: manEntityDestroy(e);
   4448 E5            [11]  247 	push	hl
   4449 E5            [11]  248 	push	hl
   444A CD F8 43      [17]  249 	call	_manEntityDestroy
   444D F1            [10]  250 	pop	af
   444E E1            [10]  251 	pop	hl
   444F 18 F1         [12]  252 	jr	00104$
   4451                     253 00102$:
                            254 ;src/man/entity.c:67: ++e;
   4451 01 10 00      [10]  255 	ld	bc, #0x0010
   4454 09            [11]  256 	add	hl, bc
   4455 18 EB         [12]  257 	jr	00104$
                            258 ;src/man/entity.c:72: u8 manEntityAvailable()
                            259 ;	---------------------------------
                            260 ; Function manEntityAvailable
                            261 ; ---------------------------------
   4457                     262 _manEntityAvailable::
                            263 ;src/man/entity.c:74: return (m_next_free < m_entities_end);
   4457 21 ED 4B      [10]  264 	ld	hl, #_m_entities_end
   445A FD 21 EB 4B   [14]  265 	ld	iy, #_m_next_free
   445E FD 7E 00      [19]  266 	ld	a, 0 (iy)
   4461 96            [ 7]  267 	sub	a, (hl)
   4462 FD 7E 01      [19]  268 	ld	a, 1 (iy)
   4465 23            [ 6]  269 	inc	hl
   4466 9E            [ 7]  270 	sbc	a, (hl)
   4467 3E 00         [ 7]  271 	ld	a, #0x00
   4469 17            [ 4]  272 	rla
   446A 6F            [ 4]  273 	ld	l, a
   446B C9            [10]  274 	ret
                            275 	.area _CODE
                            276 	.area _INITIALIZER
                            277 	.area _CABS (ABS)
