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
                             12 	.globl _manGameCreateEnemy
                             13 	.globl _manEntityForAllMatching
                             14 	.globl _sysAIBehaviorLeftRight
                             15 	.globl _sysAIBehaviorMotherShip
                             16 	.globl _sysAIUpdate
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
                             48 ;src/sys/ai.c:6: void sysAIBehaviorLeftRight(Entity_t *e)
                             49 ;	---------------------------------
                             50 ; Function sysAIBehaviorLeftRight
                             51 ; ---------------------------------
   45C1                      52 _sysAIBehaviorLeftRight::
   45C1 DD E5         [15]   53 	push	ix
   45C3 DD 21 00 00   [14]   54 	ld	ix,#0
   45C7 DD 39         [15]   55 	add	ix,sp
                             56 ;src/sys/ai.c:8: const u8 rbound = 80 - e->w;
   45C9 DD 4E 04      [19]   57 	ld	c,4 (ix)
   45CC DD 46 05      [19]   58 	ld	b,5 (ix)
   45CF 69            [ 4]   59 	ld	l, c
   45D0 60            [ 4]   60 	ld	h, b
   45D1 23            [ 6]   61 	inc	hl
   45D2 23            [ 6]   62 	inc	hl
   45D3 23            [ 6]   63 	inc	hl
   45D4 5E            [ 7]   64 	ld	e, (hl)
   45D5 3E 50         [ 7]   65 	ld	a, #0x50
   45D7 93            [ 4]   66 	sub	a, e
   45D8 5F            [ 4]   67 	ld	e, a
                             68 ;src/sys/ai.c:9: if (e->x == 0)      e->vx =  1;
   45D9 C5            [11]   69 	push	bc
   45DA FD E1         [14]   70 	pop	iy
   45DC FD 23         [10]   71 	inc	iy
   45DE FD 6E 00      [19]   72 	ld	l, 0 (iy)
   45E1 03            [ 6]   73 	inc	bc
   45E2 03            [ 6]   74 	inc	bc
   45E3 03            [ 6]   75 	inc	bc
   45E4 03            [ 6]   76 	inc	bc
   45E5 03            [ 6]   77 	inc	bc
   45E6 7D            [ 4]   78 	ld	a, l
   45E7 B7            [ 4]   79 	or	a, a
   45E8 20 03         [12]   80 	jr	NZ,00102$
   45EA 3E 01         [ 7]   81 	ld	a, #0x01
   45EC 02            [ 7]   82 	ld	(bc), a
   45ED                      83 00102$:
                             84 ;src/sys/ai.c:10: if (e->x == rbound) e->vx = -1;
   45ED FD 7E 00      [19]   85 	ld	a, 0 (iy)
   45F0 93            [ 4]   86 	sub	a, e
   45F1 20 03         [12]   87 	jr	NZ,00105$
   45F3 3E FF         [ 7]   88 	ld	a, #0xff
   45F5 02            [ 7]   89 	ld	(bc), a
   45F6                      90 00105$:
   45F6 DD E1         [14]   91 	pop	ix
   45F8 C9            [10]   92 	ret
                             93 ;src/sys/ai.c:12: void sysAIBehaviorMotherShip(Entity_t *e)
                             94 ;	---------------------------------
                             95 ; Function sysAIBehaviorMotherShip
                             96 ; ---------------------------------
   45F9                      97 _sysAIBehaviorMotherShip::
                             98 ;src/sys/ai.c:14: if (e->x == 20) {
   45F9 D1            [10]   99 	pop	de
   45FA C1            [10]  100 	pop	bc
   45FB C5            [11]  101 	push	bc
   45FC D5            [11]  102 	push	de
   45FD 69            [ 4]  103 	ld	l, c
   45FE 60            [ 4]  104 	ld	h, b
   45FF 23            [ 6]  105 	inc	hl
   4600 7E            [ 7]  106 	ld	a, (hl)
   4601 D6 14         [ 7]  107 	sub	a, #0x14
   4603 20 07         [12]  108 	jr	NZ,00102$
                            109 ;src/sys/ai.c:15: manGameCreateEnemy (e);
   4605 C5            [11]  110 	push	bc
   4606 C5            [11]  111 	push	bc
   4607 CD C3 44      [17]  112 	call	_manGameCreateEnemy
   460A F1            [10]  113 	pop	af
   460B C1            [10]  114 	pop	bc
   460C                     115 00102$:
                            116 ;src/sys/ai.c:18: sysAIBehaviorLeftRight(e);
   460C C5            [11]  117 	push	bc
   460D CD C1 45      [17]  118 	call	_sysAIBehaviorLeftRight
   4610 F1            [10]  119 	pop	af
   4611 C9            [10]  120 	ret
                            121 ;src/sys/ai.c:22: void sysAIUpdateEntity(Entity_t *e)
                            122 ;	---------------------------------
                            123 ; Function sysAIUpdateEntity
                            124 ; ---------------------------------
   4612                     125 _sysAIUpdateEntity::
   4612 DD E5         [15]  126 	push	ix
   4614 DD 21 00 00   [14]  127 	ld	ix,#0
   4618 DD 39         [15]  128 	add	ix,sp
                            129 ;src/sys/ai.c:24: e->ai_behavior(e);
   461A DD 4E 04      [19]  130 	ld	c,4 (ix)
   461D DD 46 05      [19]  131 	ld	b,5 (ix)
   4620 C5            [11]  132 	push	bc
   4621 FD E1         [14]  133 	pop	iy
   4623 FD 6E 09      [19]  134 	ld	l, 9 (iy)
   4626 FD 66 0A      [19]  135 	ld	h, 10 (iy)
   4629 C5            [11]  136 	push	bc
   462A CD 50 49      [17]  137 	call	___sdcc_call_hl
   462D F1            [10]  138 	pop	af
   462E DD E1         [14]  139 	pop	ix
   4630 C9            [10]  140 	ret
                            141 ;src/sys/ai.c:27: void sysAIUpdate()
                            142 ;	---------------------------------
                            143 ; Function sysAIUpdate
                            144 ; ---------------------------------
   4631                     145 _sysAIUpdate::
                            146 ;src/sys/ai.c:30: sysAIUpdateEntity, 
   4631 3E 0A         [ 7]  147 	ld	a, #0x0a
   4633 F5            [11]  148 	push	af
   4634 33            [ 6]  149 	inc	sp
   4635 21 12 46      [10]  150 	ld	hl, #_sysAIUpdateEntity
   4638 E5            [11]  151 	push	hl
   4639 CD A7 43      [17]  152 	call	_manEntityForAllMatching
   463C F1            [10]  153 	pop	af
   463D 33            [ 6]  154 	inc	sp
   463E C9            [10]  155 	ret
                            156 	.area _CODE
                            157 	.area _INITIALIZER
                            158 	.area _CABS (ABS)
