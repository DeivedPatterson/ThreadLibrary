#define SIZE_CONTEXT 128
    
    .set nomips16
    .set noreorder 
    
    .extern startedSystem
    .extern SystemStackTop
    .extern CurrentThreadAddress
    
    .global TimerTicksInterrupt
    .global SoftwareInterrupt
    .global StartFirstThread
    
    .set noreorder
    .set noat
    .ent TimerTicksInterrupt
    
    
    .macro SaveContext
    
    mfc0 $k0,Cause
    mfc0 $k1,EPC
    sw $s6,44($sp)
    srl $k0,$k0,0xA
    
    addiu $sp,$sp,-SIZE_CONTEXT
    sw $k1,124($sp)
    mfc0 $k1,Status
    sw $k1,128($sp)
    
    ins $k1,$k0,10,6
    ins $k1,$zero,1,4
    
    mtc0 $k1,Status
    
    la $k0, startedSystem
    lw $s6,($k0)
    
    bne $s6,$zero, bypass
    nop
    
    la $sp,SystemStackTop
    lw $sp,($sp)

bypass:
    
    addiu $s6,$s6,1
    sw $s6,0($k0)
    
    sw $ra,120($sp)

    .endm

    
    

    .macro RestoreContext
    
    
    
    

    .endm
    
TimerTicksInterrupt:
    
    add $t0,$t1,$zero
    
    
.end TimerTicksInterrupt
    
    
    .set noreorder
    .set noat
    .ent StartFirstThread
    
StartFirstThread:
    
    
    add $t0,$t1,$zero
    
.end StartFirstThread
    
    
    .set noreorder
    .set noat
    .ent SoftwareInterrupt
    
SoftwareInterrupt:
    
    
    add $t0,$t1,$zero
    
.end SoftwareInterrupt

