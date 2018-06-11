#include <sys/asm.h>
#include <p32xxxx.h>
.include "../Include/PrologueAndEpilogue.inc"
    
    .set nomips16
    .set noreorder 
    
    .extern SystemStackFlag
    .extern SystemStackTop
    .extern RunningThread
    .extern CurrentThreadStackAddress
    .extern TicksIncrement
    
    .global TimerTicksInterrupt
    .global SoftwareInterrupt
    .global StartFirstThread
    
    .set noreorder
    .set noat
    .ent TimerTicksInterrupt
    
   
    
TimerTicksInterrupt:
    
    SaveContext
    jal TicksIncrement
    nop
    RestoreContext
   
.end TimerTicksInterrupt
    
    
    .set noreorder
    .set noat
    .ent StartFirstThread
    
StartFirstThread:
  
    RestoreContext
    
    
.end StartFirstThread
    
    
    .set noreorder
    .set noat
    .ent SoftwareInterrupt
    
SoftwareInterrupt:
    
    addiu $sp,$sp,-128
    mfc0 $k1,$12,0
    
    /*Frame pointer and auxiliar register*/
    sw $s5,40($sp)
    sw $s6,44($sp)
   
    sw $k1,128($sp)
    
    /*Reenable interrupt kernel prioridade 3*/
    ins $k1,$zero,10,6
    ori $k1,$k1,0x0C00
    ins $k1,$zero,1,4
    
    /*Frame pointer*/
    add $s5,$zero,$sp
    
    /*Swap for system stack*/
    la $sp,SystemStackTop
    lw $sp,($sp)
    
    la $k0,SystemStackFlag
    addiu $s6,$zero,1
    sw $k0,0($k0)
    
    /* move EPC for register $s6*/
    mfc0 $s6,$14
    mfc0 $k1,$12,0
    
    sw $s7,124($s5)
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
    sw $s7,48($s5)
    sw $s4,36($s5)
    sw $s3,32($s5)
    sw $s2,28($s5)
    sw $s1,24($s5)
    sw $s0,20($s5)
    sw $at,16($s5)
    
    mfhi $s7
    sw $s7,12($s5)
    mflo $s7
    sw $s7,8($s5)
    
    /*Save stack in current thread address*/
    la $s7,RunningThread
    lw $s7,($s7)
    sw $s5,($s7)
    
    di
    ehb 
    
    mfc0 $s7,$12,0
    /*Set Max prioridade*/
    ins $s7,$zero,10,6
    /*Set bit IE = 1, renable interrupt*/
    ori $s6,$s7,0x0C01
    mtc0 $s6,$12,0
    ehb
    
    mfc0 $s6,$13,0
    ins $s6,$zero,8,1
    mtc0 $s6,$13,0
    ehb
    
    /*Clear interrupt flag status in IFS0 register*/
    la $s6,IFS0CLR 
    addiu $s4,$zero,2
    sw $s4,($s6)
    
    jal ThreadSwitchContext
    nop
    
    mtc0 $s7,$12,0
    ehb
    
    la $s0,RunningThread
    lw $s0,($s0)
    lw $s5,($s0)
    
    /*Restore context other Thread*/
    
    lw $s0,8($s5)
    mtlo $s0
    lw $s0,12($s5)
    mthi $s0
    lw $at,16($s5)
    lw $s0,20($s5)
    lw $s1,24($s5)
    lw $s2,28($s5)
    lw $s3,32($s5)
    lw $s4,36($s5)
    lw $s6,44($s5)
    lw $s7,48($s5)
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
    sw $zero,0($k0)
    
    lw $s5,40($sp)
    
    /*pop Status*/
    lw $k1,128($sp)
    /*pop EPC*/
    lw $k0,124($sp)
    
    addiu $sp,$sp,128
    
    /*Restore Status register*/
    mtc0 $k1,$12,0
    /*Restore Program Counter*/
    mtc0 $k0,$14
    
    ehb
    eret
    nop
    
    
.end SoftwareInterrupt

