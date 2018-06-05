
    .extern SystemStackFlag
    .extern SystemStackTop
    .extern CurrentThreadStackAddress
    
    
    .macro SaveContext
    
    mfc0 $k0,$13
    mfc0 $k1,$14
    
    srl $k0,$k0,0xA
    
    /*Space for context size*/
    
    addiu $sp,$sp,-128
    
    /*Save $s5 and $s6 for be used like auxiliare registers*/
    
    sw $s6,44($sp)
    sw $s5,40($sp)
    
    /*Save EPC Coprocessor 0 Register*/
    sw $k1,124($sp)
    
    mfc0 $k1,$12
    
    /*Save Status Coprocessor 0 Register*/
    sw $k1,128($sp)
    
    ins $k1,$k0,10,6
    ins $k1,$zero,1,4
    
    /*Set $s5 como frame pointer*/
    
    add $s5,$zero,$sp
    
    mtc0 $k1,$12
    
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
    
    /*Save general purpose registers*/
    
    sw $ra,120($sp)
    sw $fp,116($sp)
    sw $t9,112($sp)
    sw $t8,108($sp)
    sw $t7,104($sp)
    sw $t6,100($sp)
    sw $t5,96($sp)
    sw $t4,92($sp)
    sw $t3,88($sp)
    sw $t2,84($sp)
    sw $t1,80($sp)
    sw $t0,76($sp)
    sw $a3,72($sp)
    sw $a2,68($sp)
    sw $a1,64($sp)
    sw $a0,60($sp)
    sw $v1,56($sp)
    sw $v0,52($sp)
    sw $at,16($sp)
    
    /*Save Multiply and Divide registers*/
    
    mfhi $s6
    sw $s6,12($sp)
    mflo $s6
    sw $s6,8($sp)
    
    la $s6,SystemStackFlag
    lw $s6,($s6)
    addiu $s6,$s6,-1
    bne $s6,$zero, 1f
    nop
    
    la $s6,CurrentThreadStackAddress
    lw $s6,($s6)
    
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
    lw $a3,70($s5)
    lw $t0,74($s5)
    lw $t1,78($s5)
    lw $t2,82($s5)
    lw $t3,86($s5)
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
    addiu $sp,$sp,128
    
    mtc0 $k0,$12
    mtc0 $k1,$14
    
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
    