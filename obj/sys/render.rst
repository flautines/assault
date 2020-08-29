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
   47E0                      60 _sysRenderInit::
                             61 ;src/sys/render.c:9: cpct_disableFirmware();
   47E0 CD 3F 4A      [17]   62 	call	_cpct_disableFirmware
                             63 ;src/sys/render.c:10: cpct_setVideoMode(0);
   47E3 2E 00         [ 7]   64 	ld	l, #0x00
   47E5 CD F7 49      [17]   65 	call	_cpct_setVideoMode
                             66 ;src/sys/render.c:11: cpct_setBorder(HW_BLACK);
   47E8 21 10 14      [10]   67 	ld	hl, #0x1410
   47EB E5            [11]   68 	push	hl
   47EC CD 36 49      [17]   69 	call	_cpct_setPALColour
                             70 ;src/sys/render.c:12: cpct_setPalette(main_palette, 16);
   47EF 21 10 00      [10]   71 	ld	hl, #0x0010
   47F2 E5            [11]   72 	push	hl
   47F3 21 5C 43      [10]   73 	ld	hl, #_main_palette
   47F6 E5            [11]   74 	push	hl
   47F7 CD A9 48      [17]   75 	call	_cpct_setPalette
                             76 ;src/sys/render.c:15: CPCT_VMEM_START,
   47FA 21 00 B9      [10]   77 	ld	hl, #0xb900
   47FD E5            [11]   78 	push	hl
   47FE 26 C0         [ 7]   79 	ld	h, #0xc0
   4800 E5            [11]   80 	push	hl
   4801 CD FA 4A      [17]   81 	call	_cpct_getScreenPtr
   4804 E5            [11]   82 	push	hl
   4805 CD 5E 48      [17]   83 	call	_sysRenderLine
   4808 F1            [10]   84 	pop	af
   4809 C9            [10]   85 	ret
                             86 ;src/sys/render.c:19: void sysRenderUpdateEntity(Entity_t *e) {
                             87 ;	---------------------------------
                             88 ; Function sysRenderUpdateEntity
                             89 ; ---------------------------------
   480A                      90 _sysRenderUpdateEntity::
   480A DD E5         [15]   91 	push	ix
   480C DD 21 00 00   [14]   92 	ld	ix,#0
   4810 DD 39         [15]   93 	add	ix,sp
   4812 F5            [11]   94 	push	af
                             95 ;src/sys/render.c:20: Entity_t *render_e  = e;
   4813 DD 4E 04      [19]   96 	ld	c,4 (ix)
   4816 DD 46 05      [19]   97 	ld	b,5 (ix)
                             98 ;src/sys/render.c:22: if (!(render_e->type & E_TYPE_DEAD)) {
   4819 0A            [ 7]   99 	ld	a, (bc)
   481A 07            [ 4]  100 	rlca
   481B 38 3C         [12]  101 	jr	C,00103$
                            102 ;src/sys/render.c:23: u8 *pvmem = 
   481D 69            [ 4]  103 	ld	l, c
   481E 60            [ 4]  104 	ld	h, b
   481F 23            [ 6]  105 	inc	hl
   4820 23            [ 6]  106 	inc	hl
   4821 56            [ 7]  107 	ld	d, (hl)
   4822 69            [ 4]  108 	ld	l, c
   4823 60            [ 4]  109 	ld	h, b
   4824 23            [ 6]  110 	inc	hl
   4825 7E            [ 7]  111 	ld	a, (hl)
   4826 C5            [11]  112 	push	bc
   4827 5F            [ 4]  113 	ld	e, a
   4828 D5            [11]  114 	push	de
   4829 21 00 C0      [10]  115 	ld	hl, #0xc000
   482C E5            [11]  116 	push	hl
   482D CD FA 4A      [17]  117 	call	_cpct_getScreenPtr
   4830 EB            [ 4]  118 	ex	de,hl
   4831 C1            [10]  119 	pop	bc
                            120 ;src/sys/render.c:31: render_e->h);
   4832 C5            [11]  121 	push	bc
   4833 FD E1         [14]  122 	pop	iy
   4835 FD 7E 04      [19]  123 	ld	a, 4 (iy)
   4838 DD 77 FF      [19]  124 	ld	-1 (ix), a
                            125 ;src/sys/render.c:30: render_e->w, 
   483B C5            [11]  126 	push	bc
   483C FD E1         [14]  127 	pop	iy
   483E FD 7E 03      [19]  128 	ld	a, 3 (iy)
   4841 DD 77 FE      [19]  129 	ld	-2 (ix), a
                            130 ;src/sys/render.c:29: pvmem, 
                            131 ;src/sys/render.c:28: render_e->sprite, 
   4844 69            [ 4]  132 	ld	l, c
   4845 60            [ 4]  133 	ld	h, b
   4846 01 08 00      [10]  134 	ld	bc, #0x0008
   4849 09            [11]  135 	add	hl, bc
   484A 4E            [ 7]  136 	ld	c, (hl)
   484B 23            [ 6]  137 	inc	hl
   484C 46            [ 7]  138 	ld	b, (hl)
   484D DD 66 FF      [19]  139 	ld	h, -1 (ix)
   4850 DD 6E FE      [19]  140 	ld	l, -2 (ix)
   4853 E5            [11]  141 	push	hl
   4854 D5            [11]  142 	push	de
   4855 C5            [11]  143 	push	bc
   4856 CD 42 49      [17]  144 	call	_cpct_drawSprite
   4859                     145 00103$:
   4859 DD F9         [10]  146 	ld	sp, ix
   485B DD E1         [14]  147 	pop	ix
   485D C9            [10]  148 	ret
                            149 ;src/sys/render.c:35: void sysRenderLine(u8 *pvmem) {
                            150 ;	---------------------------------
                            151 ; Function sysRenderLine
                            152 ; ---------------------------------
   485E                     153 _sysRenderLine::
                            154 ;src/sys/render.c:36: cpct_drawSolidBox (pvmem, cpct_px2byteM0(10,10), 64, 3);
   485E 21 0A 0A      [10]  155 	ld	hl, #0x0a0a
   4861 E5            [11]  156 	push	hl
   4862 CD 0D 4A      [17]  157 	call	_cpct_px2byteM0
   4865 26 00         [ 7]  158 	ld	h, #0x00
   4867 D1            [10]  159 	pop	de
   4868 C1            [10]  160 	pop	bc
   4869 C5            [11]  161 	push	bc
   486A D5            [11]  162 	push	de
   486B 11 40 03      [10]  163 	ld	de, #0x0340
   486E D5            [11]  164 	push	de
   486F E5            [11]  165 	push	hl
   4870 C5            [11]  166 	push	bc
   4871 CD 4F 4A      [17]  167 	call	_cpct_drawSolidBox
                            168 ;src/sys/render.c:37: pvmem += 64;
   4874 21 02 00      [10]  169 	ld	hl, #2
   4877 39            [11]  170 	add	hl, sp
   4878 7E            [ 7]  171 	ld	a, (hl)
   4879 C6 40         [ 7]  172 	add	a, #0x40
   487B 77            [ 7]  173 	ld	(hl), a
   487C 23            [ 6]  174 	inc	hl
   487D 7E            [ 7]  175 	ld	a, (hl)
   487E CE 00         [ 7]  176 	adc	a, #0x00
   4880 77            [ 7]  177 	ld	(hl), a
                            178 ;src/sys/render.c:38: cpct_drawSolidBox (pvmem, cpct_px2byteM0(10,10), 16, 3);
   4881 21 0A 0A      [10]  179 	ld	hl, #0x0a0a
   4884 E5            [11]  180 	push	hl
   4885 CD 0D 4A      [17]  181 	call	_cpct_px2byteM0
   4888 26 00         [ 7]  182 	ld	h, #0x00
   488A D1            [10]  183 	pop	de
   488B C1            [10]  184 	pop	bc
   488C C5            [11]  185 	push	bc
   488D D5            [11]  186 	push	de
   488E 11 10 03      [10]  187 	ld	de, #0x0310
   4891 D5            [11]  188 	push	de
   4892 E5            [11]  189 	push	hl
   4893 C5            [11]  190 	push	bc
   4894 CD 4F 4A      [17]  191 	call	_cpct_drawSolidBox
   4897 C9            [10]  192 	ret
                            193 ;src/sys/render.c:41: void sysRenderUpdate() {  
                            194 ;	---------------------------------
                            195 ; Function sysRenderUpdate
                            196 ; ---------------------------------
   4898                     197 _sysRenderUpdate::
                            198 ;src/sys/render.c:42: cpct_waitVSYNC();  
   4898 CD 05 4A      [17]  199 	call	_cpct_waitVSYNC
                            200 ;src/sys/render.c:44: sysRenderUpdateEntity, 
   489B 3E 01         [ 7]  201 	ld	a, #0x01
   489D F5            [11]  202 	push	af
   489E 33            [ 6]  203 	inc	sp
   489F 21 0A 48      [10]  204 	ld	hl, #_sysRenderUpdateEntity
   48A2 E5            [11]  205 	push	hl
   48A3 CD CB 43      [17]  206 	call	_manEntityForAllMatching
   48A6 F1            [10]  207 	pop	af
   48A7 33            [ 6]  208 	inc	sp
   48A8 C9            [10]  209 	ret
                            210 	.area _CODE
                            211 	.area _INITIALIZER
                            212 	.area _CABS (ABS)
