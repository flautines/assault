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
                             12 	.globl _manEntityForAllMatching
                             13 	.globl _sysAIUpdate
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
                             45 ;src/sys/ai.c:5: void sysAIUpdateEntity(Entity_t *e)
                             46 ;	---------------------------------
                             47 ; Function sysAIUpdateEntity
                             48 ; ---------------------------------
   4487                      49 _sysAIUpdateEntity::
   4487 DD E5         [15]   50 	push	ix
   4489 DD 21 00 00   [14]   51 	ld	ix,#0
   448D DD 39         [15]   52 	add	ix,sp
                             53 ;src/sys/ai.c:7: const u8 rbound = 80 - e->w;
   448F DD 4E 04      [19]   54 	ld	c,4 (ix)
   4492 DD 46 05      [19]   55 	ld	b,5 (ix)
   4495 69            [ 4]   56 	ld	l, c
   4496 60            [ 4]   57 	ld	h, b
   4497 23            [ 6]   58 	inc	hl
   4498 23            [ 6]   59 	inc	hl
   4499 23            [ 6]   60 	inc	hl
   449A 5E            [ 7]   61 	ld	e, (hl)
   449B 3E 50         [ 7]   62 	ld	a, #0x50
   449D 93            [ 4]   63 	sub	a, e
   449E 5F            [ 4]   64 	ld	e, a
                             65 ;src/sys/ai.c:8: if (e->x == 0)      e->vx =  1;
   449F C5            [11]   66 	push	bc
   44A0 FD E1         [14]   67 	pop	iy
   44A2 FD 23         [10]   68 	inc	iy
   44A4 FD 6E 00      [19]   69 	ld	l, 0 (iy)
   44A7 03            [ 6]   70 	inc	bc
   44A8 03            [ 6]   71 	inc	bc
   44A9 03            [ 6]   72 	inc	bc
   44AA 03            [ 6]   73 	inc	bc
   44AB 03            [ 6]   74 	inc	bc
   44AC 7D            [ 4]   75 	ld	a, l
   44AD B7            [ 4]   76 	or	a, a
   44AE 20 03         [12]   77 	jr	NZ,00102$
   44B0 3E 01         [ 7]   78 	ld	a, #0x01
   44B2 02            [ 7]   79 	ld	(bc), a
   44B3                      80 00102$:
                             81 ;src/sys/ai.c:9: if (e->x == rbound) e->vx = -1;
   44B3 FD 7E 00      [19]   82 	ld	a, 0 (iy)
   44B6 93            [ 4]   83 	sub	a, e
   44B7 20 03         [12]   84 	jr	NZ,00105$
   44B9 3E FF         [ 7]   85 	ld	a, #0xff
   44BB 02            [ 7]   86 	ld	(bc), a
   44BC                      87 00105$:
   44BC DD E1         [14]   88 	pop	ix
   44BE C9            [10]   89 	ret
                             90 ;src/sys/ai.c:12: void sysAIUpdate()
                             91 ;	---------------------------------
                             92 ; Function sysAIUpdate
                             93 ; ---------------------------------
   44BF                      94 _sysAIUpdate::
                             95 ;src/sys/ai.c:15: sysAIUpdateEntity, 
   44BF 3E 0A         [ 7]   96 	ld	a, #0x0a
   44C1 F5            [11]   97 	push	af
   44C2 33            [ 6]   98 	inc	sp
   44C3 21 87 44      [10]   99 	ld	hl, #_sysAIUpdateEntity
   44C6 E5            [11]  100 	push	hl
   44C7 CD D6 42      [17]  101 	call	_manEntityForAllMatching
   44CA F1            [10]  102 	pop	af
   44CB 33            [ 6]  103 	inc	sp
   44CC C9            [10]  104 	ret
                            105 	.area _CODE
                            106 	.area _INITIALIZER
                            107 	.area _CABS (ABS)
