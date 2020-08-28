                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 3.6.8 #9946 (Linux)
                              4 ;--------------------------------------------------------
                              5 	.module physics
                              6 	.optsdcc -mz80
                              7 	
                              8 ;--------------------------------------------------------
                              9 ; Public variables in this module
                             10 ;--------------------------------------------------------
                             11 	.globl _sysPhysicsUpdateEntity
                             12 	.globl _sysPhysicsCheckKeyboard
                             13 	.globl _manEntityForAllMatching
                             14 	.globl _cpct_isKeyPressed
                             15 	.globl _cpct_scanKeyboard_f
                             16 	.globl _sysPhysicsUpdate
                             17 ;--------------------------------------------------------
                             18 ; special function registers
                             19 ;--------------------------------------------------------
                             20 ;--------------------------------------------------------
                             21 ; ram data
                             22 ;--------------------------------------------------------
                             23 	.area _DATA
                             24 ;--------------------------------------------------------
                             25 ; ram data
                             26 ;--------------------------------------------------------
                             27 	.area _INITIALIZED
                             28 ;--------------------------------------------------------
                             29 ; absolute external ram data
                             30 ;--------------------------------------------------------
                             31 	.area _DABS (ABS)
                             32 ;--------------------------------------------------------
                             33 ; global & static initialisations
                             34 ;--------------------------------------------------------
                             35 	.area _HOME
                             36 	.area _GSINIT
                             37 	.area _GSFINAL
                             38 	.area _GSINIT
                             39 ;--------------------------------------------------------
                             40 ; Home
                             41 ;--------------------------------------------------------
                             42 	.area _HOME
                             43 	.area _HOME
                             44 ;--------------------------------------------------------
                             45 ; code
                             46 ;--------------------------------------------------------
                             47 	.area _CODE
                             48 ;src/sys/physics.c:6: void sysPhysicsCheckKeyboard(Entity_t *e)
                             49 ;	---------------------------------
                             50 ; Function sysPhysicsCheckKeyboard
                             51 ; ---------------------------------
   46CC                      52 _sysPhysicsCheckKeyboard::
                             53 ;src/sys/physics.c:8: cpct_scanKeyboard_f();
   46CC CD 26 48      [17]   54 	call	_cpct_scanKeyboard_f
                             55 ;src/sys/physics.c:9: e->vx = 0;
   46CF D1            [10]   56 	pop	de
   46D0 C1            [10]   57 	pop	bc
   46D1 C5            [11]   58 	push	bc
   46D2 D5            [11]   59 	push	de
   46D3 21 05 00      [10]   60 	ld	hl, #0x0005
   46D6 09            [11]   61 	add	hl, bc
   46D7 36 00         [10]   62 	ld	(hl), #0x00
                             63 ;src/sys/physics.c:10: if      (cpct_isKeyPressed(Key_O)) e->vx = -1;
   46D9 E5            [11]   64 	push	hl
   46DA 21 04 04      [10]   65 	ld	hl, #0x0404
   46DD CD 1A 48      [17]   66 	call	_cpct_isKeyPressed
   46E0 7D            [ 4]   67 	ld	a, l
   46E1 E1            [10]   68 	pop	hl
   46E2 B7            [ 4]   69 	or	a, a
   46E3 28 03         [12]   70 	jr	Z,00104$
   46E5 36 FF         [10]   71 	ld	(hl), #0xff
   46E7 C9            [10]   72 	ret
   46E8                      73 00104$:
                             74 ;src/sys/physics.c:11: else if (cpct_isKeyPressed(Key_P)) e->vx = +1;
   46E8 E5            [11]   75 	push	hl
   46E9 21 03 08      [10]   76 	ld	hl, #0x0803
   46EC CD 1A 48      [17]   77 	call	_cpct_isKeyPressed
   46EF 7D            [ 4]   78 	ld	a, l
   46F0 E1            [10]   79 	pop	hl
   46F1 B7            [ 4]   80 	or	a, a
   46F2 C8            [11]   81 	ret	Z
   46F3 36 01         [10]   82 	ld	(hl), #0x01
   46F5 C9            [10]   83 	ret
                             84 ;src/sys/physics.c:14: void sysPhysicsUpdateEntity(Entity_t *e) {
                             85 ;	---------------------------------
                             86 ; Function sysPhysicsUpdateEntity
                             87 ; ---------------------------------
   46F6                      88 _sysPhysicsUpdateEntity::
   46F6 DD E5         [15]   89 	push	ix
   46F8 DD 21 00 00   [14]   90 	ld	ix,#0
   46FC DD 39         [15]   91 	add	ix,sp
                             92 ;src/sys/physics.c:16: if (e->type & E_TYPE_INPUT)
   46FE DD 5E 04      [19]   93 	ld	e,4 (ix)
   4701 DD 56 05      [19]   94 	ld	d,5 (ix)
   4704 1A            [ 7]   95 	ld	a, (de)
   4705 CB 57         [ 8]   96 	bit	2, a
   4707 28 07         [12]   97 	jr	Z,00102$
                             98 ;src/sys/physics.c:17: sysPhysicsCheckKeyboard(e);
   4709 D5            [11]   99 	push	de
   470A D5            [11]  100 	push	de
   470B CD CC 46      [17]  101 	call	_sysPhysicsCheckKeyboard
   470E F1            [10]  102 	pop	af
   470F D1            [10]  103 	pop	de
   4710                     104 00102$:
                            105 ;src/sys/physics.c:19: i8 vx= e->vx;
   4710 D5            [11]  106 	push	de
   4711 FD E1         [14]  107 	pop	iy
   4713 FD 4E 05      [19]  108 	ld	c, 5 (iy)
                            109 ;src/sys/physics.c:20: e->x += vx;  
   4716 6B            [ 4]  110 	ld	l, e
   4717 62            [ 4]  111 	ld	h, d
   4718 23            [ 6]  112 	inc	hl
   4719 7E            [ 7]  113 	ld	a, (hl)
   471A 81            [ 4]  114 	add	a, c
   471B 77            [ 7]  115 	ld	(hl), a
                            116 ;src/sys/physics.c:21: e->y += e->vy;
   471C 4B            [ 4]  117 	ld	c, e
   471D 42            [ 4]  118 	ld	b, d
   471E 03            [ 6]  119 	inc	bc
   471F 03            [ 6]  120 	inc	bc
   4720 0A            [ 7]  121 	ld	a, (bc)
   4721 EB            [ 4]  122 	ex	de,hl
   4722 11 06 00      [10]  123 	ld	de, #0x0006
   4725 19            [11]  124 	add	hl, de
   4726 5E            [ 7]  125 	ld	e, (hl)
   4727 83            [ 4]  126 	add	a, e
   4728 02            [ 7]  127 	ld	(bc), a
   4729 DD E1         [14]  128 	pop	ix
   472B C9            [10]  129 	ret
                            130 ;src/sys/physics.c:25: void sysPhysicsUpdate() 
                            131 ;	---------------------------------
                            132 ; Function sysPhysicsUpdate
                            133 ; ---------------------------------
   472C                     134 _sysPhysicsUpdate::
                            135 ;src/sys/physics.c:28: sysPhysicsUpdateEntity, 
   472C 3E 02         [ 7]  136 	ld	a, #0x02
   472E F5            [11]  137 	push	af
   472F 33            [ 6]  138 	inc	sp
   4730 21 F6 46      [10]  139 	ld	hl, #_sysPhysicsUpdateEntity
   4733 E5            [11]  140 	push	hl
   4734 CD A7 43      [17]  141 	call	_manEntityForAllMatching
   4737 F1            [10]  142 	pop	af
   4738 33            [ 6]  143 	inc	sp
   4739 C9            [10]  144 	ret
                            145 	.area _CODE
                            146 	.area _INITIALIZER
                            147 	.area _CABS (ABS)
