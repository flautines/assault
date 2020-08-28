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
   473A                      60 _sysRenderInit::
                             61 ;src/sys/render.c:9: cpct_disableFirmware();
   473A CD 99 49      [17]   62 	call	_cpct_disableFirmware
                             63 ;src/sys/render.c:10: cpct_setVideoMode(0);
   473D 2E 00         [ 7]   64 	ld	l, #0x00
   473F CD 51 49      [17]   65 	call	_cpct_setVideoMode
                             66 ;src/sys/render.c:11: cpct_setBorder(HW_BLACK);
   4742 21 10 14      [10]   67 	ld	hl, #0x1410
   4745 E5            [11]   68 	push	hl
   4746 CD 90 48      [17]   69 	call	_cpct_setPALColour
                             70 ;src/sys/render.c:12: cpct_setPalette(main_palette, 16);
   4749 21 10 00      [10]   71 	ld	hl, #0x0010
   474C E5            [11]   72 	push	hl
   474D 21 38 43      [10]   73 	ld	hl, #_main_palette
   4750 E5            [11]   74 	push	hl
   4751 CD 03 48      [17]   75 	call	_cpct_setPalette
                             76 ;src/sys/render.c:15: CPCT_VMEM_START,
   4754 21 00 B9      [10]   77 	ld	hl, #0xb900
   4757 E5            [11]   78 	push	hl
   4758 26 C0         [ 7]   79 	ld	h, #0xc0
   475A E5            [11]   80 	push	hl
   475B CD 54 4A      [17]   81 	call	_cpct_getScreenPtr
   475E E5            [11]   82 	push	hl
   475F CD B8 47      [17]   83 	call	_sysRenderLine
   4762 F1            [10]   84 	pop	af
   4763 C9            [10]   85 	ret
                             86 ;src/sys/render.c:19: void sysRenderUpdateEntity(Entity_t *e) {
                             87 ;	---------------------------------
                             88 ; Function sysRenderUpdateEntity
                             89 ; ---------------------------------
   4764                      90 _sysRenderUpdateEntity::
   4764 DD E5         [15]   91 	push	ix
   4766 DD 21 00 00   [14]   92 	ld	ix,#0
   476A DD 39         [15]   93 	add	ix,sp
   476C F5            [11]   94 	push	af
                             95 ;src/sys/render.c:20: Entity_t *render_e  = e;
   476D DD 4E 04      [19]   96 	ld	c,4 (ix)
   4770 DD 46 05      [19]   97 	ld	b,5 (ix)
                             98 ;src/sys/render.c:22: if (!(render_e->type & E_TYPE_DEAD)) {
   4773 0A            [ 7]   99 	ld	a, (bc)
   4774 07            [ 4]  100 	rlca
   4775 38 3C         [12]  101 	jr	C,00103$
                            102 ;src/sys/render.c:23: u8 *pvmem = 
   4777 69            [ 4]  103 	ld	l, c
   4778 60            [ 4]  104 	ld	h, b
   4779 23            [ 6]  105 	inc	hl
   477A 23            [ 6]  106 	inc	hl
   477B 56            [ 7]  107 	ld	d, (hl)
   477C 69            [ 4]  108 	ld	l, c
   477D 60            [ 4]  109 	ld	h, b
   477E 23            [ 6]  110 	inc	hl
   477F 7E            [ 7]  111 	ld	a, (hl)
   4780 C5            [11]  112 	push	bc
   4781 5F            [ 4]  113 	ld	e, a
   4782 D5            [11]  114 	push	de
   4783 21 00 C0      [10]  115 	ld	hl, #0xc000
   4786 E5            [11]  116 	push	hl
   4787 CD 54 4A      [17]  117 	call	_cpct_getScreenPtr
   478A EB            [ 4]  118 	ex	de,hl
   478B C1            [10]  119 	pop	bc
                            120 ;src/sys/render.c:31: render_e->h);
   478C C5            [11]  121 	push	bc
   478D FD E1         [14]  122 	pop	iy
   478F FD 7E 04      [19]  123 	ld	a, 4 (iy)
   4792 DD 77 FE      [19]  124 	ld	-2 (ix), a
                            125 ;src/sys/render.c:30: render_e->w, 
   4795 C5            [11]  126 	push	bc
   4796 FD E1         [14]  127 	pop	iy
   4798 FD 7E 03      [19]  128 	ld	a, 3 (iy)
   479B DD 77 FF      [19]  129 	ld	-1 (ix), a
                            130 ;src/sys/render.c:29: pvmem, 
                            131 ;src/sys/render.c:28: render_e->sprite, 
   479E 69            [ 4]  132 	ld	l, c
   479F 60            [ 4]  133 	ld	h, b
   47A0 01 07 00      [10]  134 	ld	bc, #0x0007
   47A3 09            [11]  135 	add	hl, bc
   47A4 4E            [ 7]  136 	ld	c, (hl)
   47A5 23            [ 6]  137 	inc	hl
   47A6 46            [ 7]  138 	ld	b, (hl)
   47A7 DD 66 FE      [19]  139 	ld	h, -2 (ix)
   47AA DD 6E FF      [19]  140 	ld	l, -1 (ix)
   47AD E5            [11]  141 	push	hl
   47AE D5            [11]  142 	push	de
   47AF C5            [11]  143 	push	bc
   47B0 CD 9C 48      [17]  144 	call	_cpct_drawSprite
   47B3                     145 00103$:
   47B3 DD F9         [10]  146 	ld	sp, ix
   47B5 DD E1         [14]  147 	pop	ix
   47B7 C9            [10]  148 	ret
                            149 ;src/sys/render.c:35: void sysRenderLine(u8 *pvmem) {
                            150 ;	---------------------------------
                            151 ; Function sysRenderLine
                            152 ; ---------------------------------
   47B8                     153 _sysRenderLine::
                            154 ;src/sys/render.c:36: cpct_drawSolidBox (pvmem, cpct_px2byteM0(10,10), 64, 3);
   47B8 21 0A 0A      [10]  155 	ld	hl, #0x0a0a
   47BB E5            [11]  156 	push	hl
   47BC CD 67 49      [17]  157 	call	_cpct_px2byteM0
   47BF 26 00         [ 7]  158 	ld	h, #0x00
   47C1 D1            [10]  159 	pop	de
   47C2 C1            [10]  160 	pop	bc
   47C3 C5            [11]  161 	push	bc
   47C4 D5            [11]  162 	push	de
   47C5 11 40 03      [10]  163 	ld	de, #0x0340
   47C8 D5            [11]  164 	push	de
   47C9 E5            [11]  165 	push	hl
   47CA C5            [11]  166 	push	bc
   47CB CD A9 49      [17]  167 	call	_cpct_drawSolidBox
                            168 ;src/sys/render.c:37: pvmem += 64;
   47CE 21 02 00      [10]  169 	ld	hl, #2
   47D1 39            [11]  170 	add	hl, sp
   47D2 7E            [ 7]  171 	ld	a, (hl)
   47D3 C6 40         [ 7]  172 	add	a, #0x40
   47D5 77            [ 7]  173 	ld	(hl), a
   47D6 23            [ 6]  174 	inc	hl
   47D7 7E            [ 7]  175 	ld	a, (hl)
   47D8 CE 00         [ 7]  176 	adc	a, #0x00
   47DA 77            [ 7]  177 	ld	(hl), a
                            178 ;src/sys/render.c:38: cpct_drawSolidBox (pvmem, cpct_px2byteM0(10,10), 16, 3);
   47DB 21 0A 0A      [10]  179 	ld	hl, #0x0a0a
   47DE E5            [11]  180 	push	hl
   47DF CD 67 49      [17]  181 	call	_cpct_px2byteM0
   47E2 26 00         [ 7]  182 	ld	h, #0x00
   47E4 D1            [10]  183 	pop	de
   47E5 C1            [10]  184 	pop	bc
   47E6 C5            [11]  185 	push	bc
   47E7 D5            [11]  186 	push	de
   47E8 11 10 03      [10]  187 	ld	de, #0x0310
   47EB D5            [11]  188 	push	de
   47EC E5            [11]  189 	push	hl
   47ED C5            [11]  190 	push	bc
   47EE CD A9 49      [17]  191 	call	_cpct_drawSolidBox
   47F1 C9            [10]  192 	ret
                            193 ;src/sys/render.c:41: void sysRenderUpdate() {  
                            194 ;	---------------------------------
                            195 ; Function sysRenderUpdate
                            196 ; ---------------------------------
   47F2                     197 _sysRenderUpdate::
                            198 ;src/sys/render.c:42: cpct_waitVSYNC();  
   47F2 CD 5F 49      [17]  199 	call	_cpct_waitVSYNC
                            200 ;src/sys/render.c:44: sysRenderUpdateEntity, 
   47F5 3E 01         [ 7]  201 	ld	a, #0x01
   47F7 F5            [11]  202 	push	af
   47F8 33            [ 6]  203 	inc	sp
   47F9 21 64 47      [10]  204 	ld	hl, #_sysRenderUpdateEntity
   47FC E5            [11]  205 	push	hl
   47FD CD A7 43      [17]  206 	call	_manEntityForAllMatching
   4800 F1            [10]  207 	pop	af
   4801 33            [ 6]  208 	inc	sp
   4802 C9            [10]  209 	ret
                            210 	.area _CODE
                            211 	.area _INITIALIZER
                            212 	.area _CABS (ABS)
