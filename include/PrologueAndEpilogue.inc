
    .extern SystemStackFlag
    .extern SystemStackTop
    .extern CurrentThreadStackAddress
    .extern SavedThreadStackPointer
    
    
    .macro SaveContext
    
    /*Cause*/
    mfc0 $k0,$13,0
    /*Space for context size*/
    addiu $sp,$sp,-132
    /*Status*/
    mfc0 $k1,$12,0
    
    /*Save $s5 and $s6 for be used like auxiliare registers*/
    
    sw $s6,44($sp)
    sw $s5,40($sp)
    sw $k1,128($sp)
    
    srl $k0,$k0,0xA
    ins $k1,$k0,10,6
    ins $k1,$zero,1,4
    
    /*Set $s5 como frame pointer*/
    add $s5,$zero,$sp
    
    /*Save EPC Coprocessor 0 Register*/
   /* sw $k1,124($sp)*/
       
    la $k0, SystemStackFlag
    lw $s6,($k0)
    
    /*
	if SystemStackFlag equal zero swap for stack system, otherwise
	the system stack is already being used.
    */
    
    bne $s6,$zero, 1f
    nop
    
    la $sp,SystemStackTop
    lw $sp,($sp)

1:
    
    addiu $s6,$s6,1
    sw $s6,0($k0)
    mfc0 $s6,$14,0
    /*Save general purpose registers*/
    
    sw $ra,120($s5)
    sw $fp,116($s5)
    sw $t9,112($s5)
    sw $t8,108($s5)
    sw $t7,104($s5)
    sw $t6,100($s5)
    sw $t5,96($s5)
    sw $t4,92($s5)
    sw $t3,88($s5)
    sw $t2,84($s5)
    sw $t1,80($s5)
    sw $t0,76($s5)
    sw $a3,72($s5)
    sw $a2,68($s5)
    sw $a1,64($s5)
    sw $a0,60($s5)
    sw $v1,56($s5)
    sw $v0,52($s5)
    sw $s6,124($s5)
    sw $at,16($s5)
    
    /*Save Multiply and Divide registers*/
    
    mfhi $s6
    sw $s6,12($s5)
    mflo $s6
    sw $s6,8($s5)
    
    la $s6,SystemStackFlag
    lw $s6,($s6)
    addiu $s6,$s6,-1
    bne $s6,$zero, 1f
    nop
    
    la $s6,CurrentThreadStackAddress
    sw $s5,($s6)
    
1:
    .endm

  
    .macro RestoreContext
    
    la $s6,SystemStackFlag
    lw $s6,($s6)
    addiu $s6,$s6,-1
    bne $s6,$zero, 1f
    nop
    
    la $s6,CurrentThreadStackAddress
    lw $s5,($s6)
 
1:
    lw $s6,8($s5)
    mtlo $s6
    lw $s6,12($s5)
    mthi $s6
    
    lw $at,16($s5)
    lw $s6,44($s5)
    lw $v0,52($s5)
    lw $v1,56($s5)
    lw $a0,60($s5)
    lw $a1,64($s5)
    lw $a2,68($s5)
    lw $a3,72($s5)
    lw $t0,76($s5)
    lw $t1,80($s5)
    lw $t2,84($s5)
    lw $t3,88($s5)
    lw $t4,92($s5)
    lw $t5,96($s5)
    lw $t6,100($s5)
    lw $t7,104($s5)
    lw $t8,108($s5)
    lw $t9,112($s5)
    lw $fp,116($s5)
    lw $ra,120($s5)
    
    di
    ehb
    
    la $k0,SystemStackFlag
    lw $k1,0($k0)
    addiu $k1,$k1,-1
    nop
    sw $k1,0($k0)
    
    /*Status register*/
    lw $k0,128($s5)
    /*EPC register*/
    lw $k1,124($s5)
    
    add $sp,$zero,$s5
    lw $s5,40($sp)
    addiu $sp,$sp,132
    
    mtc0 $k0,$12,0
    mtc0 $k1,$14,0
    
    /*
	Stop instruction execution
	until execution hazards are
	cleared
    */
    
    ehb
    /*Return from exception*/
    eret
    nop
    .endm
    