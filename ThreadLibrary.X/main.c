/* 
 * File:   main.c
 * Author: Deived William
 *
 * Created on 25 de Abril de 2018, 19:38
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/Thread.h"
#include <p32xxxx.h>
#include "../Include/MIPS32_M4K.h"

#define _SUPPRESS_PLIB_WARNING 
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#define _PCACHE

#include <plib.h>

#pragma config FPLLIDIV = DIV_1
#pragma config FPLLMUL = MUL_20
#pragma config UPLLIDIV = DIV_1
#pragma config UPLLEN = OFF
#pragma config FPLLODIV = DIV_1
#pragma config FNOSC = PRIPLL
#pragma config FSOSCEN = ON
#pragma config IESO = OFF
#pragma config POSCMOD = XT
#pragma config OSCIOFNC = OFF
#pragma config FPBDIV = DIV_1
#pragma config FCKSM = CSDCMD
#pragma config WDTPS = PS1
#pragma config FWDTEN = OFF
#pragma config DEBUG = OFF
#pragma config ICESEL = ICS_PGx1
#pragma config PWP = OFF
#pragma config BWP = OFF
#pragma config CP = OFF

#define SYS_FREQ 80000000UL

#define LED_STATUS PORTAbits.RA7

void Thread1(void* parameters)
{
    unsigned int i;
    
    while(1)
    {     
        for(i = 0; i < 5000000ul; i++)
            asm("nop");
        PORTAINV = 0x0080;
    }
}

void Thread2(void* parameters)
{
    unsigned int i;
    
    while(1)
    {     
        for(i = 0; i < 5000000ul; i++)
            asm("nop");
        
        PORTAINV = 64;
    }
}

int main(int argc, char** argv) 
{
    Thread thr1;
    Thread thr2;
    
    SYSTEMConfigPerformance(SYS_FREQ);
    INTEnableSystemMultiVectoredInt();
    
    TRISAbits.TRISA7 = 0;
    PORTAbits.RA7 = 0;
    TRISAbits.TRISA6 = 0;
    PORTAbits.RA6 = 0;
   
  //  SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
   // SYSTEMConfigWaitStatesAndPB(SYS_FREQ);
   // mBMXDisableDRMWaitState();
   // KSeg0Cacheable();
    ThreadLibInit();
    
    ThreadCreate("thr1",NULL,Thread1,&thr1);
    ThreadCreate("thr2",NULL,Thread2,&thr2);
    
   
    
    StartScheduling();
    
    
    return (EXIT_SUCCESS);
}

