                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 3.6.8 #9946 (Linux)
                              4 ;--------------------------------------------------------
                              5 	.module animation
                              6 	.optsdcc -mz80
                              7 	
                              8 ;--------------------------------------------------------
                              9 ; Public variables in this module
                             10 ;--------------------------------------------------------
                             11 	.globl _sysAnimationUpdate
                             12 	.globl _sysAnimationUpdateEntity
                             13 	.globl _manEntityForAllMatching
                             14 ;--------------------------------------------------------
                             15 ; special function registers
                             16 ;--------------------------------------------------------
                             17 ;--------------------------------------------------------
                             18 ; ram data
                             19 ;--------------------------------------------------------
                             20 	.area _DATA
                             21 ;--------------------------------------------------------
                             22 ; ram data
                             23 ;--------------------------------------------------------
                             24 	.area _INITIALIZED
                             25 ;--------------------------------------------------------
                             26 ; absolute external ram data
                             27 ;--------------------------------------------------------
                             28 	.area _DABS (ABS)
                             29 ;--------------------------------------------------------
                             30 ; global & static initialisations
                             31 ;--------------------------------------------------------
                             32 	.area _HOME
                             33 	.area _GSINIT
                             34 	.area _GSFINAL
                             35 	.area _GSINIT
                             36 ;--------------------------------------------------------
                             37 ; Home
                             38 ;--------------------------------------------------------
                             39 	.area _HOME
                             40 	.area _HOME
                             41 ;--------------------------------------------------------
                             42 ; code
                             43 ;--------------------------------------------------------
                             44 	.area _CODE
                             45 ;src/sys/animation.c:3: void sysAnimationUpdateEntity(Entity_t *e)
                             46 ;	---------------------------------
                             47 ; Function sysAnimationUpdateEntity
                             48 ; ---------------------------------
   463F                      49 _sysAnimationUpdateEntity::
   463F DD E5         [15]   50 	push	ix
   4641 DD 21 00 00   [14]   51 	ld	ix,#0
   4645 DD 39         [15]   52 	add	ix,sp
   4647 21 FA FF      [10]   53 	ld	hl, #-6
   464A 39            [11]   54 	add	hl, sp
   464B F9            [ 6]   55 	ld	sp, hl
                             56 ;src/sys/animation.c:6: if ( --(e->anim_counter) == 0 ) {
   464C DD 4E 04      [19]   57 	ld	c,4 (ix)
   464F DD 46 05      [19]   58 	ld	b,5 (ix)
   4652 21 0D 00      [10]   59 	ld	hl, #0x000d
   4655 09            [11]   60 	add	hl,bc
   4656 DD 75 FE      [19]   61 	ld	-2 (ix), l
   4659 DD 74 FF      [19]   62 	ld	-1 (ix), h
   465C 5E            [ 7]   63 	ld	e, (hl)
   465D 1D            [ 4]   64 	dec	e
   465E DD 6E FE      [19]   65 	ld	l,-2 (ix)
   4661 DD 66 FF      [19]   66 	ld	h,-1 (ix)
   4664 73            [ 7]   67 	ld	(hl), e
   4665 7B            [ 4]   68 	ld	a, e
   4666 B7            [ 4]   69 	or	a, a
   4667 20 50         [12]   70 	jr	NZ,00105$
                             71 ;src/sys/animation.c:7: ++e->anim;
   4669 21 0B 00      [10]   72 	ld	hl, #0x000b
   466C 09            [11]   73 	add	hl,bc
   466D E3            [19]   74 	ex	(sp), hl
   466E E1            [10]   75 	pop	hl
   466F E5            [11]   76 	push	hl
   4670 5E            [ 7]   77 	ld	e, (hl)
   4671 23            [ 6]   78 	inc	hl
   4672 56            [ 7]   79 	ld	d, (hl)
   4673 13            [ 6]   80 	inc	de
   4674 13            [ 6]   81 	inc	de
   4675 13            [ 6]   82 	inc	de
   4676 E1            [10]   83 	pop	hl
   4677 E5            [11]   84 	push	hl
   4678 73            [ 7]   85 	ld	(hl), e
   4679 23            [ 6]   86 	inc	hl
   467A 72            [ 7]   87 	ld	(hl), d
                             88 ;src/sys/animation.c:9: if ( e->anim->time == 0) {
   467B E1            [10]   89 	pop	hl
   467C E5            [11]   90 	push	hl
   467D 7E            [ 7]   91 	ld	a, (hl)
   467E DD 77 FC      [19]   92 	ld	-4 (ix), a
   4681 23            [ 6]   93 	inc	hl
   4682 7E            [ 7]   94 	ld	a, (hl)
   4683 DD 77 FD      [19]   95 	ld	-3 (ix), a
   4686 1A            [ 7]   96 	ld	a, (de)
   4687 B7            [ 4]   97 	or	a, a
   4688 20 0D         [12]   98 	jr	NZ,00102$
                             99 ;src/sys/animation.c:10: e->anim = e->anim->val.next;
   468A D1            [10]  100 	pop	de
   468B E1            [10]  101 	pop	hl
   468C E5            [11]  102 	push	hl
   468D D5            [11]  103 	push	de
   468E 23            [ 6]  104 	inc	hl
   468F 5E            [ 7]  105 	ld	e, (hl)
   4690 23            [ 6]  106 	inc	hl
   4691 56            [ 7]  107 	ld	d, (hl)
   4692 E1            [10]  108 	pop	hl
   4693 E5            [11]  109 	push	hl
   4694 73            [ 7]  110 	ld	(hl), e
   4695 23            [ 6]  111 	inc	hl
   4696 72            [ 7]  112 	ld	(hl), d
   4697                     113 00102$:
                            114 ;src/sys/animation.c:13: e->sprite = e->anim->val.sprite;
   4697 21 07 00      [10]  115 	ld	hl, #0x0007
   469A 09            [11]  116 	add	hl,bc
   469B 4D            [ 4]  117 	ld	c, l
   469C 44            [ 4]  118 	ld	b, h
   469D E1            [10]  119 	pop	hl
   469E E5            [11]  120 	push	hl
   469F 5E            [ 7]  121 	ld	e, (hl)
   46A0 23            [ 6]  122 	inc	hl
   46A1 66            [ 7]  123 	ld	h, (hl)
   46A2 6B            [ 4]  124 	ld	l, e
   46A3 23            [ 6]  125 	inc	hl
   46A4 5E            [ 7]  126 	ld	e, (hl)
   46A5 23            [ 6]  127 	inc	hl
   46A6 56            [ 7]  128 	ld	d, (hl)
   46A7 7B            [ 4]  129 	ld	a, e
   46A8 02            [ 7]  130 	ld	(bc), a
   46A9 03            [ 6]  131 	inc	bc
   46AA 7A            [ 4]  132 	ld	a, d
   46AB 02            [ 7]  133 	ld	(bc), a
                            134 ;src/sys/animation.c:14: e->anim_counter = e->anim->time;        
   46AC E1            [10]  135 	pop	hl
   46AD E5            [11]  136 	push	hl
   46AE 4E            [ 7]  137 	ld	c, (hl)
   46AF 23            [ 6]  138 	inc	hl
   46B0 46            [ 7]  139 	ld	b, (hl)
   46B1 0A            [ 7]  140 	ld	a, (bc)
   46B2 DD 6E FE      [19]  141 	ld	l,-2 (ix)
   46B5 DD 66 FF      [19]  142 	ld	h,-1 (ix)
   46B8 77            [ 7]  143 	ld	(hl), a
   46B9                     144 00105$:
   46B9 DD F9         [10]  145 	ld	sp, ix
   46BB DD E1         [14]  146 	pop	ix
   46BD C9            [10]  147 	ret
                            148 ;src/sys/animation.c:19: void sysAnimationUpdate()
                            149 ;	---------------------------------
                            150 ; Function sysAnimationUpdate
                            151 ; ---------------------------------
   46BE                     152 _sysAnimationUpdate::
                            153 ;src/sys/animation.c:21: manEntityForAllMatching (sysAnimationUpdateEntity, E_TYPE_ANIM);
   46BE 3E 10         [ 7]  154 	ld	a, #0x10
   46C0 F5            [11]  155 	push	af
   46C1 33            [ 6]  156 	inc	sp
   46C2 21 3F 46      [10]  157 	ld	hl, #_sysAnimationUpdateEntity
   46C5 E5            [11]  158 	push	hl
   46C6 CD A7 43      [17]  159 	call	_manEntityForAllMatching
   46C9 F1            [10]  160 	pop	af
   46CA 33            [ 6]  161 	inc	sp
   46CB C9            [10]  162 	ret
                            163 	.area _CODE
                            164 	.area _INITIALIZER
                            165 	.area _CABS (ABS)
