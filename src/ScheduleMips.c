#include "../include/Schedule.h"
#include "../include/Config.h"
#include <proc/p32mx460f512l.h>
#include <sys/attribs.h>
#include "../include/Types.h"
#include "../include/MIPS32_M4K.h"
   
#define PERIPHERAL_CLOCK_HZ 	80000000ul
#define TICK_RATE_HZ			1000u
#define TIME_PRESCALE			8
#define PRESCALE_SELECT_BITS 	1     

#define THREAD_MAX_CYCLES       0xFFF00000
   
#ifndef MIN_STACK_ISR
	#define MIN_STACK_ISR 256u
#endif



volatile unsigned int SystemStackFlag = 1;
unsigned int StackISR[MIN_STACK_ISR]__attribute__((aligned(8)));
unsigned int* SystemStackTop = &(StackISR[MIN_STACK_ISR-1]);
unsigned int CurrentThreadStackAddress = 0;

void* ThreadStackInit(unsigned int* ThreadStackTop, void(Function)(void*), void* parameters);
void StartFirstThread(void);
static void ThreadError(void);
extern Boolean ThreadIncrementTicks(void);

void __ISR(_TIMER_1_VECTOR, IPL1AUTO) Timer1ISR(void);
void __ISR(_CORE_SOFTWARE_0_VECTOR, IPL1AUTO) CoreSoftwareISR(void);
void __ISR(_CORE_TIMER_VECTOR, IPL1AUTO) CoreTimerISR(void);


void* ThreadStackInit(unsigned int* ThreadStackTop, ThreadFuntion function, void* parameters)
{
    unsigned int temp;
    
    asm volatile("mfc0 %0,$12,0":"=r"(temp));
	*ThreadStackTop = temp;                         //Coprocessor 0, Status Register
	ThreadStackTop--;       
	*ThreadStackTop = (unsigned int)function;       //Coprocessor 0, EPC Register
	ThreadStackTop--;
    *ThreadStackTop = (unsigned int)ThreadError;    //Funcion return $ra Register 
    ThreadStackTop -= 15;
    *ThreadStackTop = (unsigned int)parameters;
    ThreadStackTop -= 15;
    
    return ThreadStackTop;
}

void StartScheduling(void)
{
	extern void* RunningThread;
    const unsigned int Comparator = ((PERIPHERAL_CLOCK_HZ /TIME_PRESCALE)/TICK_RATE_HZ) - 1;
    
    __builtin_disable_interrupts();
    
    IPC0bits.CS0IP = KERNEL_INTERRUPT_PRIORITY;
    IPC0bits.CS0IS = 0;
    IFS0bits.CS0IF = 0;
    IEC0bits.CS0IE = 1;
    
    _CP0_SET_COMPARE(THREAD_MAX_CYCLES);
    IPC0bits.CTIP = KERNEL_INTERRUPT_PRIORITY;
    IPC0bits.CTIS = 0;
    IFS0bits.CTIF = 0;
    IEC0bits.CTIE = 0;
    
    T1CON = 0x0000;
	T1CONbits.TCKPS = PRESCALE_SELECT_BITS;
	PR1 = Comparator;
	IPC1bits.T1IP = KERNEL_INTERRUPT_PRIORITY;
	IFS0bits.T1IF = 0;
	IEC0bits.T1IE = 1;
	T1CONbits.TON = 1;
    
	CurrentThreadStackAddress = *((unsigned int*)RunningThread);
    StartFirstThread();
}

void EndSheduling(void)
{

}

void TimerTicksConfig(void)
{
	
	
}

static void ThreadError(void)
{
    DisableInterrupts();
    while(1);
}

void TicksIncrement(void)
{
    unsigned int SaveStausRegister;
   
    __builtin_disable_interrupts();
   
    SaveStausRegister = _CP0_GET_STATUS()|0x0000001;
    _CP0_SET_STATUS((SaveStausRegister&(~IPL_BITS))|0x00000C00);
    ThreadIncrementTicks();
            
    _CP0_SET_STATUS(SaveStausRegister);
    
    IFS0CLR = _IFS0_T1IF_MASK;
}