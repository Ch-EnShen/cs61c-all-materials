	beq s0 s0 start #0
bad-loop: 
	addi sp sp -1 #1
	beq x0 x0 bad-loop #2

start:
	addi s1 s1 10#3
	blt s0 s1 label1#4
	beq x0 x0 bad-loop#5

label2: 
	addi s1 s1 -20#6
	bltu s0 s1 end#7
    beq x0 x0 bad-loop#8

label1: 
	addi s0 s0 20#9
	blt s1 s0 label2#10
    beq x0 x0 bad-loop#11

end:
	add a0 x0 x0#12

#0,3,4,9,10,6,7,12