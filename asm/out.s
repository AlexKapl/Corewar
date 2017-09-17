.comment "en fait C forker !" #| 0
.name "Jumper !" #| 1
 #| 2
gobepc:	st r1,:buff #| 3
	st r6,-4 #| 4
	ld :buff,r1 #| 5
debut:	ld %0,r7 #| 6
	zjmp %:suite #| 7
 #| 8
goboucle0:	live %66 #| 9
		ldi %-5,r3,r1 #| 10
		sti r1,%-173,r3 #| 11
		add r3,r4,r3 #| 12
		xor r5,r3,r6 #| 13
		zjmp %:finboucle0 #| 14
		ld %0,r7 #| 15
		zjmp %:goboucle0 #| 16
finboucle0:	xor r3,r3,r3 #| 17
		zjmp %-207 #| 18
 #| 19
buff:	st r1,r1	 #| 20
		 #| 21
suite:	sti r1,%:livel,%1 #| 22
livel:	live %66 #| 23
	sti r2,%:debut,%-60 #| 24
	ld %4,r4 #| 25
	st r2,512 #| 26
go:	ld %48,r5 #| 27
	sti r1,%:goboucle0,%1 #| 28
	sti r1,%:goboucle1,%1 #| 29
	sti r1,%:live0,%1 #| 30
	sti r1,%:live1,%1 #| 31
	sti r1,%:live2,%1 #| 32
	sti r1,%:live3,%1 #| 33
	sti r1,%:live4,%1 #| 34
live0:	live %66 #| 35
live1:	live %66 #| 36
live2:	live %66 #| 37
live3:	live %66 #| 38
live4:	live %66 #| 39
	zjmp %:live0 #| 40
	xor r3,r3,r3 #| 41
	sti r1,%:livex,%1 #| 42
livex:	live %66 #| 43
	fork %:live0 #| 44
	sti r1,%:boucle,%1 #| 45
	sti r1,%:boucle,%9 #| 46
	sti r1,%:boucle,%17 #| 47
	sti r1,%:boucle,%25 #| 48
	 #| 49
boucle:	live %66 #| 50
	fork %:goboucle0 #| 51
	live %66 #| 52
	fork %:boucle #| 53
	live %66 #| 54
	fork %:goboucle1 #| 55
	live %66 #| 56
	zjmp %:goboucle0 #| 57
goboucle1:	live %66 #| 58
		ldi %-5,r3,r1 #| 59
		sti r1,%17,r3 #| 60
		add r3,r4,r3 #| 61
		xor r5,r3,r6 #| 62
		zjmp %:finboucle1 #| 63
		ld %0,r7 #| 64
		zjmp %:goboucle1 #| 65
finboucle1:	xor r3,r3,r3 #| 66
		zjmp %1 #| 67
