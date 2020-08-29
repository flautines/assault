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
   46A3                      49 _sysAnimationUpdateEntity::
   46A3 DD E5         [15]   50 	push	ix
   46A5 DD 21 00 00   [14]   51 	ld	ix,#0
   46A9 DD 39         [15]   52 	add	ix,sp
   46AB 21 FA FF      [10]   53 	ld	hl, #-6
   46AE 39            [11]   54 	add	hl, sp
   46AF F9            [ 6]   55 	ld	sp, hl
                             56 ;src/sys/animation.c:6: if ( --(e->anim_counter) == 0 ) {
   46B0 DD 4E 04      [19]   57 	ld	c,4 (ix)
   46B3 DD 46 05      [19]   58 	ld	b,5 (ix)
   46B6 21 0E 00      [10]   59 	ld	hl, #0x000e
   46B9 09            [11]   60 	add	hl,bc
   46BA DD 75 FE      [19]   61 	ld	-2 (ix), l
   46BD DD 74 FF      [19]   62 	ld	-1 (ix), h
   46C0 5E            [ 7]   63 	ld	e, (hl)
   46C1 1D            [ 4]   64 	dec	e
   46C2 DD 6E FE      [19]   65 	ld	l,-2 (ix)
   46C5 DD 66 FF      [19]   66 	ld	h,-1 (ix)
   46C8 73            [ 7]   67 	ld	(hl), e
   46C9 7B            [ 4]   68 	ld	a, e
   46CA B7            [ 4]   69 	or	a, a
   46CB 20 50         [12]   70 	jr	NZ,00105$
                             71 ;src/sys/animation.c:7: ++e->anim;
   46CD 21 0C 00      [10]   72 	ld	hl, #0x000c
   46D0 09            [11]   73 	add	hl,bc
   46D1 E3            [19]   74 	ex	(sp), hl
   46D2 E1            [10]   75 	pop	hl
   46D3 E5            [11]   76 	push	hl
   46D4 5E            [ 7]   77 	ld	e, (hl)
   46D5 23            [ 6]   78 	inc	hl
   46D6 56            [ 7]   79 	ld	d, (hl)
   46D7 13            [ 6]   80 	inc	de
   46D8 13            [ 6]   81 	inc	de
   46D9 13            [ 6]   82 	inc	de
   46DA E1            [10]   83 	pop	hl
   46DB E5            [11]   84 	push	hl
   46DC 73            [ 7]   85 	ld	(hl), e
   46DD 23            [ 6]   86 	inc	hl
   46DE 72            [ 7]   87 	ld	(hl), d
                             88 ;src/sys/animation.c:9: if ( e->anim->time == 0) {
   46DF E1            [10]   89 	pop	hl
   46E0 E5            [11]   90 	push	hl
   46E1 7E            [ 7]   91 	ld	a, (hl)
   46E2 DD 77 FC      [19]   92 	ld	-4 (ix), a
   46E5 23            [ 6]   93 	inc	hl
   46E6 7E            [ 7]   94 	ld	a, (hl)
   46E7 DD 77 FD      [19]   95 	ld	-3 (ix), a
   46EA 1A            [ 7]   96 	ld	a, (de)
   46EB B7            [ 4]   97 	or	a, a
   46EC 20 0D         [12]   98 	jr	NZ,00102$
                             99 ;src/sys/animation.c:10: e->anim = e->anim->val.next;
   46EE D1            [10]  100 	pop	de
   46EF E1            [10]  101 	pop	hl
   46F0 E5            [11]  102 	push	hl
   46F1 D5            [11]  103 	push	de
   46F2 23            [ 6]  104 	inc	hl
   46F3 5E            [ 7]  105 	ld	e, (hl)
   46F4 23            [ 6]  106 	inc	hl
   46F5 56            [ 7]  107 	ld	d, (hl)
   46F6 E1            [10]  108 	pop	hl
   46F7 E5            [11]  109 	push	hl
   46F8 73            [ 7]  110 	ld	(hl), e
   46F9 23            [ 6]  111 	inc	hl
   46FA 72            [ 7]  112 	ld	(hl), d
   46FB                     113 00102$:
                            114 ;src/sys/animation.c:13: e->sprite = e->anim->val.sprite;
   46FB 21 08 00      [10]  115 	ld	hl, #0x0008
   46FE 09            [11]  116 	add	hl,bc
   46FF 4D            [ 4]  117 	ld	c, l
   4700 44            [ 4]  118 	ld	b, h
   4701 E1            [10]  119 	pop	hl
   4702 E5            [11]  120 	push	hl
   4703 5E            [ 7]  121 	ld	e, (hl)
   4704 23            [ 6]  122 	inc	hl
   4705 66            [ 7]  123 	ld	h, (hl)
   4706 6B            [ 4]  124 	ld	l, e
   4707 23            [ 6]  125 	inc	hl
   4708 5E            [ 7]  126 	ld	e, (hl)
   4709 23            [ 6]  127 	inc	hl
   470A 56            [ 7]  128 	ld	d, (hl)
   470B 7B            [ 4]  129 	ld	a, e
   470C 02            [ 7]  130 	ld	(bc), a
   470D 03            [ 6]  131 	inc	bc
   470E 7A            [ 4]  132 	ld	a, d
   470F 02            [ 7]  133 	ld	(bc), a
                            134 ;src/sys/animation.c:14: e->anim_counter = e->anim->time;        
   4710 E1            [10]  135 	pop	hl
   4711 E5            [11]  136 	push	hl
   4712 4E            [ 7]  137 	ld	c, (hl)
   4713 23            [ 6]  138 	inc	hl
   4714 46            [ 7]  139 	ld	b, (hl)
   4715 0A            [ 7]  140 	ld	a, (bc)
   4716 DD 6E FE      [19]  141 	ld	l,-2 (ix)
   4719 DD 66 FF      [19]  142 	ld	h,-1 (ix)
   471C 77            [ 7]  143 	ld	(hl), a
   471D                     144 00105$:
   471D DD F9         [10]  145 	ld	sp, ix
   471F DD E1         [14]  146 	pop	ix
   4721 C9            [10]  147 	ret
                            148 ;src/sys/animation.c:19: void sysAnimationUpdate()
                            149 ;	---------------------------------
                            150 ; Function sysAnimationUpdate
                            151 ; ---------------------------------
   4722                     152 _sysAnimationUpdate::
                            153 ;src/sys/animation.c:21: manEntityForAllMatching (sysAnimationUpdateEntity, E_TYPE_ANIM);
   4722 3E 10         [ 7]  154 	ld	a, #0x10
   4724 F5            [11]  155 	push	af
   4725 33            [ 6]  156 	inc	sp
   4726 21 A3 46      [10]  157 	ld	hl, #_sysAnimationUpdateEntity
   4729 E5            [11]  158 	push	hl
   472A CD CB 43      [17]  159 	call	_manEntityForAllMatching
   472D F1            [10]  160 	pop	af
   472E 33            [ 6]  161 	inc	sp
   472F C9            [10]  162 	ret
                            163 	.area _CODE
                            164 	.area _INITIALIZER
                            165 	.area _CABS (ABS)
