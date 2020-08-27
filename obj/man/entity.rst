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
   4885                      32 _m_entities::
   4885                      33 	.ds 108
   48F1                      34 _m_invalid::
   48F1                      35 	.ds 1
   48F2                      36 _m_next_free::
   48F2                      37 	.ds 2
   48F4                      38 _m_entities_end::
   48F4                      39 	.ds 2
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
   4286                      68 _manEntityInit::
                             69 ;src/man/entity.c:11: m_next_free = m_entities; 
   4286 01 85 48      [10]   70 	ld	bc, #_m_entities+0
   4289 ED 43 F2 48   [20]   71 	ld	(_m_next_free), bc
                             72 ;src/man/entity.c:12: m_invalid = E_TYPE_INVALID;
   428D 21 F1 48      [10]   73 	ld	hl,#_m_invalid + 0
   4290 36 00         [10]   74 	ld	(hl), #0x00
                             75 ;src/man/entity.c:13: m_entities_end = m_entities + MAX_ENTITIES;
   4292 21 6C 00      [10]   76 	ld	hl, #0x006c
   4295 09            [11]   77 	add	hl, bc
   4296 22 F4 48      [16]   78 	ld	(_m_entities_end), hl
                             79 ;src/man/entity.c:14: cpct_memset(m_next_free, 0, sizeof(m_entities));
   4299 21 6C 00      [10]   80 	ld	hl, #0x006c
   429C E5            [11]   81 	push	hl
   429D AF            [ 4]   82 	xor	a, a
   429E F5            [11]   83 	push	af
   429F 33            [ 6]   84 	inc	sp
   42A0 21 85 48      [10]   85 	ld	hl, #_m_entities
   42A3 E5            [11]   86 	push	hl
   42A4 CD 8C 47      [17]   87 	call	_cpct_memset
   42A7 C9            [10]   88 	ret
                             89 ;src/man/entity.c:17: Entity_t *manEntityCreate() {
                             90 ;	---------------------------------
                             91 ; Function manEntityCreate
                             92 ; ---------------------------------
   42A8                      93 _manEntityCreate::
                             94 ;src/man/entity.c:18: Entity_t *next = m_next_free;
   42A8 ED 4B F2 48   [20]   95 	ld	bc, (_m_next_free)
                             96 ;src/man/entity.c:19: m_next_free = next + 1;
   42AC 21 09 00      [10]   97 	ld	hl, #0x0009
   42AF 09            [11]   98 	add	hl,bc
   42B0 22 F2 48      [16]   99 	ld	(_m_next_free), hl
                            100 ;src/man/entity.c:20: next->type = E_TYPE_DEFAULT;
   42B3 3E 7F         [ 7]  101 	ld	a, #0x7f
   42B5 02            [ 7]  102 	ld	(bc), a
                            103 ;src/man/entity.c:21: return next;
   42B6 69            [ 4]  104 	ld	l, c
   42B7 60            [ 4]  105 	ld	h, b
   42B8 C9            [10]  106 	ret
                            107 ;src/man/entity.c:24: void manEntityForAll(void (*pfunUpdateEntity)(Entity_t *)) {
                            108 ;	---------------------------------
                            109 ; Function manEntityForAll
                            110 ; ---------------------------------
   42B9                     111 _manEntityForAll::
                            112 ;src/man/entity.c:25: Entity_t *e = m_entities;
   42B9 01 85 48      [10]  113 	ld	bc, #_m_entities+0
                            114 ;src/man/entity.c:26: while (e->type != E_TYPE_INVALID) {
   42BC                     115 00101$:
   42BC 0A            [ 7]  116 	ld	a, (bc)
   42BD B7            [ 4]  117 	or	a, a
   42BE C8            [11]  118 	ret	Z
                            119 ;src/man/entity.c:27: pfunUpdateEntity(e++);
   42BF 59            [ 4]  120 	ld	e, c
   42C0 50            [ 4]  121 	ld	d, b
   42C1 21 09 00      [10]  122 	ld	hl, #0x0009
   42C4 09            [11]  123 	add	hl,bc
   42C5 E5            [11]  124 	push	hl
   42C6 D5            [11]  125 	push	de
   42C7 21 06 00      [10]  126 	ld	hl, #6
   42CA 39            [11]  127 	add	hl, sp
   42CB 7E            [ 7]  128 	ld	a, (hl)
   42CC 23            [ 6]  129 	inc	hl
   42CD 66            [ 7]  130 	ld	h, (hl)
   42CE 6F            [ 4]  131 	ld	l, a
   42CF CD 51 47      [17]  132 	call	___sdcc_call_hl
   42D2 F1            [10]  133 	pop	af
   42D3 C1            [10]  134 	pop	bc
   42D4 18 E6         [12]  135 	jr	00101$
                            136 ;src/man/entity.c:31: void manEntityForAllMatching(
                            137 ;	---------------------------------
                            138 ; Function manEntityForAllMatching
                            139 ; ---------------------------------
   42D6                     140 _manEntityForAllMatching::
                            141 ;src/man/entity.c:35: Entity_t *e = m_entities;  
   42D6 01 85 48      [10]  142 	ld	bc, #_m_entities+0
                            143 ;src/man/entity.c:36: while (e->type != E_TYPE_INVALID) {
   42D9                     144 00103$:
   42D9 0A            [ 7]  145 	ld	a, (bc)
   42DA B7            [ 4]  146 	or	a, a
   42DB C8            [11]  147 	ret	Z
                            148 ;src/man/entity.c:37: if ((e->type & signature) == signature)
   42DC FD 21 04 00   [14]  149 	ld	iy, #4
   42E0 FD 39         [15]  150 	add	iy, sp
   42E2 FD A6 00      [19]  151 	and	a, 0 (iy)
   42E5 5F            [ 4]  152 	ld	e, a
   42E6 FD 7E 00      [19]  153 	ld	a, 0 (iy)
   42E9 93            [ 4]  154 	sub	a, e
   42EA 20 0F         [12]  155 	jr	NZ,00102$
                            156 ;src/man/entity.c:38: pfunUpdateEntity(e);
   42EC C5            [11]  157 	push	bc
   42ED C5            [11]  158 	push	bc
   42EE 21 06 00      [10]  159 	ld	hl, #6
   42F1 39            [11]  160 	add	hl, sp
   42F2 7E            [ 7]  161 	ld	a, (hl)
   42F3 23            [ 6]  162 	inc	hl
   42F4 66            [ 7]  163 	ld	h, (hl)
   42F5 6F            [ 4]  164 	ld	l, a
   42F6 CD 51 47      [17]  165 	call	___sdcc_call_hl
   42F9 F1            [10]  166 	pop	af
   42FA C1            [10]  167 	pop	bc
   42FB                     168 00102$:
                            169 ;src/man/entity.c:39: e++;
   42FB 21 09 00      [10]  170 	ld	hl, #0x0009
   42FE 09            [11]  171 	add	hl,bc
   42FF 4D            [ 4]  172 	ld	c, l
   4300 44            [ 4]  173 	ld	b, h
   4301 18 D6         [12]  174 	jr	00103$
                            175 ;src/man/entity.c:44: void manEntityDestroy(Entity_t *e) {
                            176 ;	---------------------------------
                            177 ; Function manEntityDestroy
                            178 ; ---------------------------------
   4303                     179 _manEntityDestroy::
   4303 DD E5         [15]  180 	push	ix
   4305 DD 21 00 00   [14]  181 	ld	ix,#0
   4309 DD 39         [15]  182 	add	ix,sp
                            183 ;src/man/entity.c:45: Entity_t *dead_e = e;
   430B DD 4E 04      [19]  184 	ld	c,4 (ix)
   430E DD 46 05      [19]  185 	ld	b,5 (ix)
                            186 ;src/man/entity.c:46: --m_next_free;
   4311 21 F2 48      [10]  187 	ld	hl, #_m_next_free
   4314 7E            [ 7]  188 	ld	a, (hl)
   4315 C6 F7         [ 7]  189 	add	a, #0xf7
   4317 77            [ 7]  190 	ld	(hl), a
   4318 23            [ 6]  191 	inc	hl
   4319 7E            [ 7]  192 	ld	a, (hl)
   431A CE FF         [ 7]  193 	adc	a, #0xff
   431C 77            [ 7]  194 	ld	(hl), a
                            195 ;src/man/entity.c:48: if (dead_e != m_next_free)
   431D FD 21 F2 48   [14]  196 	ld	iy, #_m_next_free
   4321 FD 7E 00      [19]  197 	ld	a, 0 (iy)
   4324 91            [ 4]  198 	sub	a, c
   4325 20 06         [12]  199 	jr	NZ,00109$
   4327 FD 7E 01      [19]  200 	ld	a, 1 (iy)
   432A 90            [ 4]  201 	sub	a, b
   432B 28 0C         [12]  202 	jr	Z,00102$
   432D                     203 00109$:
                            204 ;src/man/entity.c:49: cpct_memcpy(dead_e, m_next_free, sizeof(Entity_t));
   432D 2A F2 48      [16]  205 	ld	hl, (_m_next_free)
   4330 11 09 00      [10]  206 	ld	de, #0x0009
   4333 D5            [11]  207 	push	de
   4334 E5            [11]  208 	push	hl
   4335 C5            [11]  209 	push	bc
   4336 CD 84 47      [17]  210 	call	_cpct_memcpy
   4339                     211 00102$:
                            212 ;src/man/entity.c:51: m_next_free->type = E_TYPE_INVALID;
   4339 2A F2 48      [16]  213 	ld	hl, (_m_next_free)
   433C 36 00         [10]  214 	ld	(hl), #0x00
   433E DD E1         [14]  215 	pop	ix
   4340 C9            [10]  216 	ret
                            217 ;src/man/entity.c:54: void manEntityDelete(Entity_t *e)
                            218 ;	---------------------------------
                            219 ; Function manEntityDelete
                            220 ; ---------------------------------
   4341                     221 _manEntityDelete::
                            222 ;src/man/entity.c:56: e->type |= E_TYPE_DEAD;
   4341 D1            [10]  223 	pop	de
   4342 C1            [10]  224 	pop	bc
   4343 C5            [11]  225 	push	bc
   4344 D5            [11]  226 	push	de
   4345 0A            [ 7]  227 	ld	a, (bc)
   4346 CB FF         [ 8]  228 	set	7, a
   4348 02            [ 7]  229 	ld	(bc), a
   4349 C9            [10]  230 	ret
                            231 ;src/man/entity.c:59: void manEntityUpdate()
                            232 ;	---------------------------------
                            233 ; Function manEntityUpdate
                            234 ; ---------------------------------
   434A                     235 _manEntityUpdate::
                            236 ;src/man/entity.c:61: Entity_t *e = m_entities;
   434A 21 85 48      [10]  237 	ld	hl, #_m_entities+0
                            238 ;src/man/entity.c:62: while (e->type != E_TYPE_INVALID) {
   434D                     239 00104$:
   434D 7E            [ 7]  240 	ld	a, (hl)
   434E B7            [ 4]  241 	or	a, a
   434F C8            [11]  242 	ret	Z
                            243 ;src/man/entity.c:63: if (e->type & E_TYPE_DEAD) {
   4350 07            [ 4]  244 	rlca
   4351 30 09         [12]  245 	jr	NC,00102$
                            246 ;src/man/entity.c:64: manEntityDestroy(e);
   4353 E5            [11]  247 	push	hl
   4354 E5            [11]  248 	push	hl
   4355 CD 03 43      [17]  249 	call	_manEntityDestroy
   4358 F1            [10]  250 	pop	af
   4359 E1            [10]  251 	pop	hl
   435A 18 F1         [12]  252 	jr	00104$
   435C                     253 00102$:
                            254 ;src/man/entity.c:67: ++e;
   435C 01 09 00      [10]  255 	ld	bc, #0x0009
   435F 09            [11]  256 	add	hl, bc
   4360 18 EB         [12]  257 	jr	00104$
                            258 ;src/man/entity.c:72: u8 manEntityAvailable()
                            259 ;	---------------------------------
                            260 ; Function manEntityAvailable
                            261 ; ---------------------------------
   4362                     262 _manEntityAvailable::
                            263 ;src/man/entity.c:74: return (m_next_free < m_entities_end);
   4362 21 F4 48      [10]  264 	ld	hl, #_m_entities_end
   4365 FD 21 F2 48   [14]  265 	ld	iy, #_m_next_free
   4369 FD 7E 00      [19]  266 	ld	a, 0 (iy)
   436C 96            [ 7]  267 	sub	a, (hl)
   436D FD 7E 01      [19]  268 	ld	a, 1 (iy)
   4370 23            [ 6]  269 	inc	hl
   4371 9E            [ 7]  270 	sbc	a, (hl)
   4372 3E 00         [ 7]  271 	ld	a, #0x00
   4374 17            [ 4]  272 	rla
   4375 6F            [ 4]  273 	ld	l, a
   4376 C9            [10]  274 	ret
                            275 	.area _CODE
                            276 	.area _INITIALIZER
                            277 	.area _CABS (ABS)
