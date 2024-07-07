add s0 x0 x0
addi a0 x0 -1
bne s0 s0 never_reach
addi s0 s0 -1
lui s1 0 #end 
addi s1 s1 36 #end
jr s1
never_reach:
  addi s0, s0, 1
  j end 
end:
  addi a0 a0 1
