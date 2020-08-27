                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 3.6.8 #9946 (Linux)
                              4 ;--------------------------------------------------------
                              5 	.module render
                              6 	.optsdcc -mz80
                              7 	
                              8 ;--------------------------------------------------------
                              9 ; Public variables in this module
                             10 ;--------------------------------------------------------
                             11 	.globl _sysRenderUpdateEntity
                             12 	.globl _manEntityForAllMatching
                             13 	.globl _cpct_getScreenPtr
                             14 	.globl _cpct_setPALColour
                             15 	.globl _cpct_setPalette
                             16 	.globl _cpct_waitVSYNC
                             17 	.globl _cpct_setVideoMode
                             18 	.globl _cpct_drawSprite
                             19 	.globl _cpct_drawSolidBox
                             20 	.globl _cpct_px2byteM0
                             21 	.globl _cpct_disableFirmware
                             22 	.globl _sysRenderInit
                             23 	.globl _sysRenderLine
                             24 	.globl _sysRenderUpdate
                             25 ;--------------------------------------------------------
                             26 ; special function registers
                             27 ;--------------------------------------------------------
                             28 ;--------------------------------------------------------
                             29 ; ram data
                             30 ;--------------------------------------------------------
                             31 	.area _DATA
                             32 ;--------------------------------------------------------
                             33 ; ram data
                             34 ;--------------------------------------------------------
                             35 	.area _INITIALIZED
                             36 ;--------------------------------------------------------
                             37 ; absolute external ram data
                             38 ;--------------------------------------------------------
                             39 	.area _DABS (ABS)
                             40 ;--------------------------------------------------------
                             41 ; global & static initialisations
                             42 ;--------------------------------------------------------
                             43 	.area _HOME
                             44 	.area _GSINIT
                             45 	.area _GSFINAL
                             46 	.area _GSINIT
                             47 ;--------------------------------------------------------
                             48 ; Home
                             49 ;--------------------------------------------------------
                             50 	.area _HOME
                             51 	.area _HOME
                             52 ;--------------------------------------------------------
                             53 ; code
                             54 ;--------------------------------------------------------
                             55 	.area _CODE
                             56 ;src/sys/render.c:8: void sysRenderInit() {
                             57 ;	---------------------------------
                             58 ; Function sysRenderInit
                             59 ; ---------------------------------
   453B                      60 _sysRenderInit::
                             61 ;src/sys/render.c:9: cpct_disableFirmware();
   453B CD 9A 47      [17]   62 	call	_cpct_disableFirmware
                             63 ;src/sys/render.c:10: cpct_setVideoMode(0);
   453E 2E 00         [ 7]   64 	ld	l, #0x00
   4540 CD 52 47      [17]   65 	call	_cpct_setVideoMode
                             66 ;src/sys/render.c:11: cpct_setBorder(HW_BLACK);
   4543 21 10 14      [10]   67 	ld	hl, #0x1410
   4546 E5            [11]   68 	push	hl
   4547 CD 91 46      [17]   69 	call	_cpct_setPALColour
                             70 ;src/sys/render.c:12: cpct_setPalette(main_palette, 16);
   454A 21 10 00      [10]   71 	ld	hl, #0x0010
   454D E5            [11]   72 	push	hl
   454E 21 70 42      [10]   73 	ld	hl, #_main_palette
   4551 E5            [11]   74 	push	hl
   4552 CD 04 46      [17]   75 	call	_cpct_setPalette
                             76 ;src/sys/render.c:15: CPCT_VMEM_START,
   4555 21 00 B9      [10]   77 	ld	hl, #0xb900
   4558 E5            [11]   78 	push	hl
   4559 26 C0         [ 7]   79 	ld	h, #0xc0
   455B E5            [11]   80 	push	hl
   455C CD 55 48      [17]   81 	call	_cpct_getScreenPtr
   455F E5            [11]   82 	push	hl
   4560 CD B9 45      [17]   83 	call	_sysRenderLine
   4563 F1            [10]   84 	pop	af
   4564 C9            [10]   85 	ret
                             86 ;src/sys/render.c:19: void sysRenderUpdateEntity(Entity_t *e) {
                             87 ;	---------------------------------
                             88 ; Function sysRenderUpdateEntity
                             89 ; ---------------------------------
   4565                      90 _sysRenderUpdateEntity::
   4565 DD E5         [15]   91 	push	ix
   4567 DD 21 00 00   [14]   92 	ld	ix,#0
   456B DD 39         [15]   93 	add	ix,sp
   456D F5            [11]   94 	push	af
                             95 ;src/sys/render.c:20: Entity_t *render_e  = e;
   456E DD 4E 04      [19]   96 	ld	c,4 (ix)
   4571 DD 46 05      [19]   97 	ld	b,5 (ix)
                             98 ;src/sys/render.c:22: if (!(render_e->type & E_TYPE_DEAD)) {
   4574 0A            [ 7]   99 	ld	a, (bc)
   4575 07            [ 4]  100 	rlca
   4576 38 3C         [12]  101 	jr	C,00103$
                            102 ;src/sys/render.c:23: u8 *pvmem = 
   4578 69            [ 4]  103 	ld	l, c
   4579 60            [ 4]  104 	ld	h, b
   457A 23            [ 6]  105 	inc	hl
   457B 23            [ 6]  106 	inc	hl
   457C 56            [ 7]  107 	ld	d, (hl)
   457D 69            [ 4]  108 	ld	l, c
   457E 60            [ 4]  109 	ld	h, b
   457F 23            [ 6]  110 	inc	hl
   4580 7E            [ 7]  111 	ld	a, (hl)
   4581 C5            [11]  112 	push	bc
   4582 5F            [ 4]  113 	ld	e, a
   4583 D5            [11]  114 	push	de
   4584 21 00 C0      [10]  115 	ld	hl, #0xc000
   4587 E5            [11]  116 	push	hl
   4588 CD 55 48      [17]  117 	call	_cpct_getScreenPtr
   458B EB            [ 4]  118 	ex	de,hl
   458C C1            [10]  119 	pop	bc
                            120 ;src/sys/render.c:31: render_e->h);
   458D C5            [11]  121 	push	bc
   458E FD E1         [14]  122 	pop	iy
   4590 FD 7E 04      [19]  123 	ld	a, 4 (iy)
   4593 DD 77 FE      [19]  124 	ld	-2 (ix), a
                            125 ;src/sys/render.c:30: render_e->w, 
   4596 C5            [11]  126 	push	bc
   4597 FD E1         [14]  127 	pop	iy
   4599 FD 7E 03      [19]  128 	ld	a, 3 (iy)
   459C DD 77 FF      [19]  129 	ld	-1 (ix), a
                            130 ;src/sys/render.c:29: pvmem, 
                            131 ;src/sys/render.c:28: render_e->sprite, 
   459F 69            [ 4]  132 	ld	l, c
   45A0 60            [ 4]  133 	ld	h, b
   45A1 01 07 00      [10]  134 	ld	bc, #0x0007
   45A4 09            [11]  135 	add	hl, bc
   45A5 4E            [ 7]  136 	ld	c, (hl)
   45A6 23            [ 6]  137 	inc	hl
   45A7 46            [ 7]  138 	ld	b, (hl)
   45A8 DD 66 FE      [19]  139 	ld	h, -2 (ix)
   45AB DD 6E FF      [19]  140 	ld	l, -1 (ix)
   45AE E5            [11]  141 	push	hl
   45AF D5            [11]  142 	push	de
   45B0 C5            [11]  143 	push	bc
   45B1 CD 9D 46      [17]  144 	call	_cpct_drawSprite
   45B4                     145 00103$:
   45B4 DD F9         [10]  146 	ld	sp, ix
   45B6 DD E1         [14]  147 	pop	ix
   45B8 C9            [10]  148 	ret
                            149 ;src/sys/render.c:35: void sysRenderLine(u8 *pvmem) {
                            150 ;	---------------------------------
                            151 ; Function sysRenderLine
                            152 ; ---------------------------------
   45B9                     153 _sysRenderLine::
                            154 ;src/sys/render.c:36: cpct_drawSolidBox (pvmem, cpct_px2byteM0(10,10), 64, 3);
   45B9 21 0A 0A      [10]  155 	ld	hl, #0x0a0a
   45BC E5            [11]  156 	push	hl
   45BD CD 68 47      [17]  157 	call	_cpct_px2byteM0
   45C0 26 00         [ 7]  158 	ld	h, #0x00
   45C2 D1            [10]  159 	pop	de
   45C3 C1            [10]  160 	pop	bc
   45C4 C5            [11]  161 	push	bc
   45C5 D5            [11]  162 	push	de
   45C6 11 40 03      [10]  163 	ld	de, #0x0340
   45C9 D5            [11]  164 	push	de
   45CA E5            [11]  165 	push	hl
   45CB C5            [11]  166 	push	bc
   45CC CD AA 47      [17]  167 	call	_cpct_drawSolidBox
                            168 ;src/sys/render.c:37: pvmem += 64;
   45CF 21 02 00      [10]  169 	ld	hl, #2
   45D2 39            [11]  170 	add	hl, sp
   45D3 7E            [ 7]  171 	ld	a, (hl)
   45D4 C6 40         [ 7]  172 	add	a, #0x40
   45D6 77            [ 7]  173 	ld	(hl), a
   45D7 23            [ 6]  174 	inc	hl
   45D8 7E            [ 7]  175 	ld	a, (hl)
   45D9 CE 00         [ 7]  176 	adc	a, #0x00
   45DB 77            [ 7]  177 	ld	(hl), a
                            178 ;src/sys/render.c:38: cpct_drawSolidBox (pvmem, cpct_px2byteM0(10,10), 16, 3);
   45DC 21 0A 0A      [10]  179 	ld	hl, #0x0a0a
   45DF E5            [11]  180 	push	hl
   45E0 CD 68 47      [17]  181 	call	_cpct_px2byteM0
   45E3 26 00         [ 7]  182 	ld	h, #0x00
   45E5 D1            [10]  183 	pop	de
   45E6 C1            [10]  184 	pop	bc
   45E7 C5            [11]  185 	push	bc
   45E8 D5            [11]  186 	push	de
   45E9 11 10 03      [10]  187 	ld	de, #0x0310
   45EC D5            [11]  188 	push	de
   45ED E5            [11]  189 	push	hl
   45EE C5            [11]  190 	push	bc
   45EF CD AA 47      [17]  191 	call	_cpct_drawSolidBox
   45F2 C9            [10]  192 	ret
                            193 ;src/sys/render.c:41: void sysRenderUpdate() {  
                            194 ;	---------------------------------
                            195 ; Function sysRenderUpdate
                            196 ; ---------------------------------
   45F3                     197 _sysRenderUpdate::
                            198 ;src/sys/render.c:42: cpct_waitVSYNC();  
   45F3 CD 60 47      [17]  199 	call	_cpct_waitVSYNC
                            200 ;src/sys/render.c:44: sysRenderUpdateEntity, 
   45F6 3E 01         [ 7]  201 	ld	a, #0x01
   45F8 F5            [11]  202 	push	af
   45F9 33            [ 6]  203 	inc	sp
   45FA 21 65 45      [10]  204 	ld	hl, #_sysRenderUpdateEntity
   45FD E5            [11]  205 	push	hl
   45FE CD D6 42      [17]  206 	call	_manEntityForAllMatching
   4601 F1            [10]  207 	pop	af
   4602 33            [ 6]  208 	inc	sp
   4603 C9            [10]  209 	ret
                            210 	.area _CODE
                            211 	.area _INITIALIZER
                            212 	.area _CABS (ABS)
