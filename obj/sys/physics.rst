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
                             16 	.globl _sysPhysicsUpDown
                             17 	.globl _sysPhysicsUpdate
                             18 ;--------------------------------------------------------
                             19 ; special function registers
                             20 ;--------------------------------------------------------
                             21 ;--------------------------------------------------------
                             22 ; ram data
                             23 ;--------------------------------------------------------
                             24 	.area _DATA
                             25 ;--------------------------------------------------------
                             26 ; ram data
                             27 ;--------------------------------------------------------
                             28 	.area _INITIALIZED
                             29 ;--------------------------------------------------------
                             30 ; absolute external ram data
                             31 ;--------------------------------------------------------
                             32 	.area _DABS (ABS)
                             33 ;--------------------------------------------------------
                             34 ; global & static initialisations
                             35 ;--------------------------------------------------------
                             36 	.area _HOME
                             37 	.area _GSINIT
                             38 	.area _GSFINAL
                             39 	.area _GSINIT
                             40 ;--------------------------------------------------------
                             41 ; Home
                             42 ;--------------------------------------------------------
                             43 	.area _HOME
                             44 	.area _HOME
                             45 ;--------------------------------------------------------
                             46 ; code
                             47 ;--------------------------------------------------------
                             48 	.area _CODE
                             49 ;src/sys/physics.c:6: void sysPhysicsCheckKeyboard(Entity_t *e)
                             50 ;	---------------------------------
                             51 ; Function sysPhysicsCheckKeyboard
                             52 ; ---------------------------------
   4730                      53 _sysPhysicsCheckKeyboard::
                             54 ;src/sys/physics.c:8: cpct_scanKeyboard_f();
   4730 CD CC 48      [17]   55 	call	_cpct_scanKeyboard_f
                             56 ;src/sys/physics.c:9: e->vx = 0;
   4733 D1            [10]   57 	pop	de
   4734 C1            [10]   58 	pop	bc
   4735 C5            [11]   59 	push	bc
   4736 D5            [11]   60 	push	de
   4737 21 05 00      [10]   61 	ld	hl, #0x0005
   473A 09            [11]   62 	add	hl, bc
   473B 36 00         [10]   63 	ld	(hl), #0x00
                             64 ;src/sys/physics.c:10: if      (cpct_isKeyPressed(Key_O)) e->vx = -1;
   473D E5            [11]   65 	push	hl
   473E 21 04 04      [10]   66 	ld	hl, #0x0404
   4741 CD C0 48      [17]   67 	call	_cpct_isKeyPressed
   4744 7D            [ 4]   68 	ld	a, l
   4745 E1            [10]   69 	pop	hl
   4746 B7            [ 4]   70 	or	a, a
   4747 28 03         [12]   71 	jr	Z,00104$
   4749 36 FF         [10]   72 	ld	(hl), #0xff
   474B C9            [10]   73 	ret
   474C                      74 00104$:
                             75 ;src/sys/physics.c:11: else if (cpct_isKeyPressed(Key_P)) e->vx = +1;
   474C E5            [11]   76 	push	hl
   474D 21 03 08      [10]   77 	ld	hl, #0x0803
   4750 CD C0 48      [17]   78 	call	_cpct_isKeyPressed
   4753 7D            [ 4]   79 	ld	a, l
   4754 E1            [10]   80 	pop	hl
   4755 B7            [ 4]   81 	or	a, a
   4756 C8            [11]   82 	ret	Z
   4757 36 01         [10]   83 	ld	(hl), #0x01
   4759 C9            [10]   84 	ret
                             85 ;src/sys/physics.c:14: void sysPhysicsUpdateEntity(Entity_t *e) {
                             86 ;	---------------------------------
                             87 ; Function sysPhysicsUpdateEntity
                             88 ; ---------------------------------
   475A                      89 _sysPhysicsUpdateEntity::
   475A DD E5         [15]   90 	push	ix
   475C DD 21 00 00   [14]   91 	ld	ix,#0
   4760 DD 39         [15]   92 	add	ix,sp
   4762 F5            [11]   93 	push	af
   4763 3B            [ 6]   94 	dec	sp
                             95 ;src/sys/physics.c:15: u8 current_frame = e->current_frame;
   4764 DD 4E 04      [19]   96 	ld	c,4 (ix)
   4767 DD 46 05      [19]   97 	ld	b,5 (ix)
   476A 21 0F 00      [10]   98 	ld	hl, #0x000f
   476D 09            [11]   99 	add	hl,bc
   476E E3            [19]  100 	ex	(sp), hl
   476F E1            [10]  101 	pop	hl
   4770 E5            [11]  102 	push	hl
   4771 7E            [ 7]  103 	ld	a, (hl)
   4772 DD 77 FF      [19]  104 	ld	-1 (ix), a
                            105 ;src/sys/physics.c:16: u8 move_counter = e->move_counter;
   4775 C5            [11]  106 	push	bc
   4776 FD E1         [14]  107 	pop	iy
   4778 FD 5E 07      [19]  108 	ld	e, 7 (iy)
                            109 ;src/sys/physics.c:17: if (e->type & E_TYPE_INPUT)
   477B 0A            [ 7]  110 	ld	a, (bc)
   477C CB 57         [ 8]  111 	bit	2, a
   477E 28 09         [12]  112 	jr	Z,00102$
                            113 ;src/sys/physics.c:18: sysPhysicsCheckKeyboard(e);
   4780 C5            [11]  114 	push	bc
   4781 D5            [11]  115 	push	de
   4782 C5            [11]  116 	push	bc
   4783 CD 30 47      [17]  117 	call	_sysPhysicsCheckKeyboard
   4786 F1            [10]  118 	pop	af
   4787 D1            [10]  119 	pop	de
   4788 C1            [10]  120 	pop	bc
   4789                     121 00102$:
                            122 ;src/sys/physics.c:20: if ( (current_frame & move_counter) == 0 )
   4789 DD 7E FF      [19]  123 	ld	a, -1 (ix)
   478C A3            [ 4]  124 	and	a,e
   478D 20 1B         [12]  125 	jr	NZ,00104$
                            126 ;src/sys/physics.c:22: i8 vx= e->vx;
   478F 69            [ 4]  127 	ld	l, c
   4790 60            [ 4]  128 	ld	h, b
   4791 11 05 00      [10]  129 	ld	de, #0x0005
   4794 19            [11]  130 	add	hl, de
   4795 56            [ 7]  131 	ld	d, (hl)
                            132 ;src/sys/physics.c:23: e->x += vx;  
   4796 69            [ 4]  133 	ld	l, c
   4797 60            [ 4]  134 	ld	h, b
   4798 23            [ 6]  135 	inc	hl
   4799 7E            [ 7]  136 	ld	a, (hl)
   479A 82            [ 4]  137 	add	a, d
   479B 77            [ 7]  138 	ld	(hl), a
                            139 ;src/sys/physics.c:24: e->y += e->vy;
   479C 59            [ 4]  140 	ld	e, c
   479D 50            [ 4]  141 	ld	d, b
   479E 13            [ 6]  142 	inc	de
   479F 13            [ 6]  143 	inc	de
   47A0 1A            [ 7]  144 	ld	a, (de)
   47A1 69            [ 4]  145 	ld	l, c
   47A2 60            [ 4]  146 	ld	h, b
   47A3 01 06 00      [10]  147 	ld	bc, #0x0006
   47A6 09            [11]  148 	add	hl, bc
   47A7 4E            [ 7]  149 	ld	c, (hl)
   47A8 81            [ 4]  150 	add	a, c
   47A9 12            [ 7]  151 	ld	(de), a
   47AA                     152 00104$:
                            153 ;src/sys/physics.c:26: ++current_frame;
   47AA DD 4E FF      [19]  154 	ld	c, -1 (ix)
   47AD 0C            [ 4]  155 	inc	c
                            156 ;src/sys/physics.c:27: e->current_frame = current_frame;
   47AE E1            [10]  157 	pop	hl
   47AF E5            [11]  158 	push	hl
   47B0 71            [ 7]  159 	ld	(hl), c
   47B1 DD F9         [10]  160 	ld	sp, ix
   47B3 DD E1         [14]  161 	pop	ix
   47B5 C9            [10]  162 	ret
                            163 ;src/sys/physics.c:30: void sysPhysicsUpDown(Entity_t *e, u8 up)
                            164 ;	---------------------------------
                            165 ; Function sysPhysicsUpDown
                            166 ; ---------------------------------
   47B6                     167 _sysPhysicsUpDown::
                            168 ;src/sys/physics.c:32: e->vy = up ? -1 : 1;
   47B6 D1            [10]  169 	pop	de
   47B7 C1            [10]  170 	pop	bc
   47B8 C5            [11]  171 	push	bc
   47B9 D5            [11]  172 	push	de
   47BA 21 06 00      [10]  173 	ld	hl, #0x0006
   47BD 09            [11]  174 	add	hl, bc
   47BE FD 21 04 00   [14]  175 	ld	iy, #4
   47C2 FD 39         [15]  176 	add	iy, sp
   47C4 FD 7E 00      [19]  177 	ld	a, 0 (iy)
   47C7 B7            [ 4]  178 	or	a, a
   47C8 28 04         [12]  179 	jr	Z,00103$
   47CA 0E FF         [ 7]  180 	ld	c, #0xff
   47CC 18 02         [12]  181 	jr	00104$
   47CE                     182 00103$:
   47CE 0E 01         [ 7]  183 	ld	c, #0x01
   47D0                     184 00104$:
   47D0 71            [ 7]  185 	ld	(hl), c
   47D1 C9            [10]  186 	ret
                            187 ;src/sys/physics.c:35: void sysPhysicsUpdate() 
                            188 ;	---------------------------------
                            189 ; Function sysPhysicsUpdate
                            190 ; ---------------------------------
   47D2                     191 _sysPhysicsUpdate::
                            192 ;src/sys/physics.c:38: sysPhysicsUpdateEntity, 
   47D2 3E 02         [ 7]  193 	ld	a, #0x02
   47D4 F5            [11]  194 	push	af
   47D5 33            [ 6]  195 	inc	sp
   47D6 21 5A 47      [10]  196 	ld	hl, #_sysPhysicsUpdateEntity
   47D9 E5            [11]  197 	push	hl
   47DA CD CB 43      [17]  198 	call	_manEntityForAllMatching
   47DD F1            [10]  199 	pop	af
   47DE 33            [ 6]  200 	inc	sp
   47DF C9            [10]  201 	ret
                            202 	.area _CODE
                            203 	.area _INITIALIZER
                            204 	.area _CABS (ABS)
