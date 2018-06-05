#include <sys/asm.h>
#include <p32xxxx.h>
.include "../Include/PrologueAndEpilogue.inc"
    
    .set nomips16
    .set noreorder 
    
    .extern SystemStackFlag
    .extern SystemStackTop
    .extern CurrentThreadAddress
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
   
    
.end SoftwareInterrupt

