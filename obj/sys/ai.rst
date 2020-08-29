                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 3.6.8 #9946 (Linux)
                              4 ;--------------------------------------------------------
                              5 	.module ai
                              6 	.optsdcc -mz80
                              7 	
                              8 ;--------------------------------------------------------
                              9 ; Public variables in this module
                             10 ;--------------------------------------------------------
                             11 	.globl _sysAIUpdateEntity
                             12 	.globl _sysPhysicsUpDown
                             13 	.globl _manGameCreateEnemy
                             14 	.globl _manEntityForAllMatching
                             15 	.globl _updown
                             16 	.globl _sysAIBehaviorLeftRight
                             17 	.globl _sysAIBehaviorMotherShip
                             18 	.globl _sysAIInit
                             19 	.globl _sysAIUpdate
                             20 ;--------------------------------------------------------
                             21 ; special function registers
                             22 ;--------------------------------------------------------
                             23 ;--------------------------------------------------------
                             24 ; ram data
                             25 ;--------------------------------------------------------
                             26 	.area _DATA
   4BF0                      27 _updown::
   4BF0                      28 	.ds 1
                             29 ;--------------------------------------------------------
                             30 ; ram data
                             31 ;--------------------------------------------------------
                             32 	.area _INITIALIZED
                             33 ;--------------------------------------------------------
                             34 ; absolute external ram data
                             35 ;--------------------------------------------------------
                             36 	.area _DABS (ABS)
                             37 ;--------------------------------------------------------
                             38 ; global & static initialisations
                             39 ;--------------------------------------------------------
                             40 	.area _HOME
                             41 	.area _GSINIT
                             42 	.area _GSFINAL
                             43 	.area _GSINIT
                             44 ;--------------------------------------------------------
                             45 ; Home
                             46 ;--------------------------------------------------------
                             47 	.area _HOME
                             48 	.area _HOME
                             49 ;--------------------------------------------------------
                             50 ; code
                             51 ;--------------------------------------------------------
                             52 	.area _CODE
                             53 ;src/sys/ai.c:9: void sysAIBehaviorLeftRight(Entity_t *e)
                             54 ;	---------------------------------
                             55 ; Function sysAIBehaviorLeftRight
                             56 ; ---------------------------------
   45F2                      57 _sysAIBehaviorLeftRight::
   45F2 DD E5         [15]   58 	push	ix
   45F4 DD 21 00 00   [14]   59 	ld	ix,#0
   45F8 DD 39         [15]   60 	add	ix,sp
                             61 ;src/sys/ai.c:11: const u8 rbound = 80 - e->w;
   45FA DD 4E 04      [19]   62 	ld	c,4 (ix)
   45FD DD 46 05      [19]   63 	ld	b,5 (ix)
   4600 69            [ 4]   64 	ld	l, c
   4601 60            [ 4]   65 	ld	h, b
   4602 23            [ 6]   66 	inc	hl
   4603 23            [ 6]   67 	inc	hl
   4604 23            [ 6]   68 	inc	hl
   4605 5E            [ 7]   69 	ld	e, (hl)
   4606 3E 50         [ 7]   70 	ld	a, #0x50
   4608 93            [ 4]   71 	sub	a, e
   4609 5F            [ 4]   72 	ld	e, a
                             73 ;src/sys/ai.c:12: if (e->x == 0)      e->vx =  1;
   460A C5            [11]   74 	push	bc
   460B FD E1         [14]   75 	pop	iy
   460D FD 23         [10]   76 	inc	iy
   460F FD 6E 00      [19]   77 	ld	l, 0 (iy)
   4612 03            [ 6]   78 	inc	bc
   4613 03            [ 6]   79 	inc	bc
   4614 03            [ 6]   80 	inc	bc
   4615 03            [ 6]   81 	inc	bc
   4616 03            [ 6]   82 	inc	bc
   4617 7D            [ 4]   83 	ld	a, l
   4618 B7            [ 4]   84 	or	a, a
   4619 20 03         [12]   85 	jr	NZ,00102$
   461B 3E 01         [ 7]   86 	ld	a, #0x01
   461D 02            [ 7]   87 	ld	(bc), a
   461E                      88 00102$:
                             89 ;src/sys/ai.c:13: if (e->x == rbound) e->vx = -1;
   461E FD 7E 00      [19]   90 	ld	a, 0 (iy)
   4621 93            [ 4]   91 	sub	a, e
   4622 20 03         [12]   92 	jr	NZ,00105$
   4624 3E FF         [ 7]   93 	ld	a, #0xff
   4626 02            [ 7]   94 	ld	(bc), a
   4627                      95 00105$:
   4627 DD E1         [14]   96 	pop	ix
   4629 C9            [10]   97 	ret
                             98 ;src/sys/ai.c:15: void sysAIBehaviorMotherShip(Entity_t *e)
                             99 ;	---------------------------------
                            100 ; Function sysAIBehaviorMotherShip
                            101 ; ---------------------------------
   462A                     102 _sysAIBehaviorMotherShip::
                            103 ;src/sys/ai.c:17: if (e->x == 20) {
   462A D1            [10]  104 	pop	de
   462B C1            [10]  105 	pop	bc
   462C C5            [11]  106 	push	bc
   462D D5            [11]  107 	push	de
   462E 69            [ 4]  108 	ld	l, c
   462F 60            [ 4]  109 	ld	h, b
   4630 23            [ 6]  110 	inc	hl
   4631 7E            [ 7]  111 	ld	a, (hl)
   4632 D6 14         [ 7]  112 	sub	a, #0x14
   4634 20 07         [12]  113 	jr	NZ,00102$
                            114 ;src/sys/ai.c:18: manGameCreateEnemy (e);
   4636 C5            [11]  115 	push	bc
   4637 C5            [11]  116 	push	bc
   4638 CD F1 44      [17]  117 	call	_manGameCreateEnemy
   463B F1            [10]  118 	pop	af
   463C C1            [10]  119 	pop	bc
   463D                     120 00102$:
                            121 ;src/sys/ai.c:22: if ( (e->current_frame&15) == 0 ) {
   463D 69            [ 4]  122 	ld	l, c
   463E 60            [ 4]  123 	ld	h, b
   463F 11 0F 00      [10]  124 	ld	de, #0x000f
   4642 19            [11]  125 	add	hl, de
   4643 7E            [ 7]  126 	ld	a, (hl)
   4644 E6 0F         [ 7]  127 	and	a, #0x0f
   4646 20 1E         [12]  128 	jr	NZ,00104$
                            129 ;src/sys/ai.c:23: sysPhysicsUpDown(e, updown);
   4648 3A F0 4B      [13]  130 	ld	a, (_updown)
   464B F5            [11]  131 	push	af
   464C 33            [ 6]  132 	inc	sp
   464D 21 03 00      [10]  133 	ld	hl, #3
   4650 39            [11]  134 	add	hl, sp
   4651 4E            [ 7]  135 	ld	c, (hl)
   4652 23            [ 6]  136 	inc	hl
   4653 46            [ 7]  137 	ld	b, (hl)
   4654 C5            [11]  138 	push	bc
   4655 CD B6 47      [17]  139 	call	_sysPhysicsUpDown
   4658 F1            [10]  140 	pop	af
   4659 33            [ 6]  141 	inc	sp
                            142 ;src/sys/ai.c:24: updown ^= 1;
   465A FD 21 F0 4B   [14]  143 	ld	iy, #_updown
   465E FD 7E 00      [19]  144 	ld	a, 0 (iy)
   4661 EE 01         [ 7]  145 	xor	a, #0x01
   4663 FD 77 00      [19]  146 	ld	0 (iy), a
   4666                     147 00104$:
                            148 ;src/sys/ai.c:26: sysAIBehaviorLeftRight(e);
   4666 C1            [10]  149 	pop	bc
   4667 E1            [10]  150 	pop	hl
   4668 E5            [11]  151 	push	hl
   4669 C5            [11]  152 	push	bc
   466A E5            [11]  153 	push	hl
   466B CD F2 45      [17]  154 	call	_sysAIBehaviorLeftRight
   466E F1            [10]  155 	pop	af
   466F C9            [10]  156 	ret
                            157 ;src/sys/ai.c:31: void sysAIInit()
                            158 ;	---------------------------------
                            159 ; Function sysAIInit
                            160 ; ---------------------------------
   4670                     161 _sysAIInit::
                            162 ;src/sys/ai.c:33: updown = 0;
   4670 21 F0 4B      [10]  163 	ld	hl,#_updown + 0
   4673 36 00         [10]  164 	ld	(hl), #0x00
   4675 C9            [10]  165 	ret
                            166 ;src/sys/ai.c:36: void sysAIUpdateEntity(Entity_t *e)
                            167 ;	---------------------------------
                            168 ; Function sysAIUpdateEntity
                            169 ; ---------------------------------
   4676                     170 _sysAIUpdateEntity::
   4676 DD E5         [15]  171 	push	ix
   4678 DD 21 00 00   [14]  172 	ld	ix,#0
   467C DD 39         [15]  173 	add	ix,sp
                            174 ;src/sys/ai.c:38: e->ai_behavior(e);
   467E DD 4E 04      [19]  175 	ld	c,4 (ix)
   4681 DD 46 05      [19]  176 	ld	b,5 (ix)
   4684 C5            [11]  177 	push	bc
   4685 FD E1         [14]  178 	pop	iy
   4687 FD 6E 0A      [19]  179 	ld	l, 10 (iy)
   468A FD 66 0B      [19]  180 	ld	h, 11 (iy)
   468D C5            [11]  181 	push	bc
   468E CD F6 49      [17]  182 	call	___sdcc_call_hl
   4691 F1            [10]  183 	pop	af
   4692 DD E1         [14]  184 	pop	ix
   4694 C9            [10]  185 	ret
                            186 ;src/sys/ai.c:41: void sysAIUpdate()
                            187 ;	---------------------------------
                            188 ; Function sysAIUpdate
                            189 ; ---------------------------------
   4695                     190 _sysAIUpdate::
                            191 ;src/sys/ai.c:44: sysAIUpdateEntity, 
   4695 3E 0A         [ 7]  192 	ld	a, #0x0a
   4697 F5            [11]  193 	push	af
   4698 33            [ 6]  194 	inc	sp
   4699 21 76 46      [10]  195 	ld	hl, #_sysAIUpdateEntity
   469C E5            [11]  196 	push	hl
   469D CD CB 43      [17]  197 	call	_manEntityForAllMatching
   46A0 F1            [10]  198 	pop	af
   46A1 33            [ 6]  199 	inc	sp
   46A2 C9            [10]  200 	ret
                            201 	.area _CODE
                            202 	.area _INITIALIZER
                            203 	.area _CABS (ABS)
