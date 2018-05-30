
    .macro SaveContext
    
    
    
    
    

    .endm

    
    

    .macro RestoreContext
    
    
    
    

    .endm
    
    .set nomips16
    .set noreorder 
    
    .extern startedSystem
    .extern StackTop
    .extern CurrentThreadAddress
    
    .global TimerTicksInterrupt
    .global SoftwareInterrupt
    .global StartFirstThread
    
    .set noreorder
    .set noat
    .ent TimerTicksInterrupt
    
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

