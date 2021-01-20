#include "stm32f4xx.h"
#include <stdio.h>

#define GREEN_MODE   (1U<<0)
#define BLUE_MODE  (1U<<14)
#define RED_MODE (1U<<28)
   
#define GREEN_BIT   (1U<<0)
#define BLUE_BIT  (1U<<7)
#define BLUE_BIT_RESET (0U<<7)
#define RED_BIT (1U<<14)

// uint32_t orange_stack[40];
// uint32_t blue_stack[40];

// uint32_t *sp_orange = &orange_stack[40];
// uint32_t *sp_blue = &blue_stack[40];


#define GPIOB_CLOCK  (1<<1)
//this piece of code changes without anyother code
volatile uint32_t tick;
volatile uint32_t _tick;

// void GPIO_Init(void);
// void Delays(uint32_t seconds);
 void BlueOn(void);
 void BlueOff(void);
// void GreenOn(void);
// void GreenOff(void);
// void SVC_Handler_c(unsigned int * svc_args);

//#define EnablePrivilegedMode() __asm("SVC #0")

int x,y,z;

#define Enable() __asm("SVC #0")
#define Disable()  __asm("SVC #1")

void SVC_Handler_main(unsigned int * svc_args);

int main(void)
{ GPIO_Init();  
  int x,y,z;
	x=3;y=5;
  //z=svc_service_add();
	//printf("3+5=%d\n",z);
	
  //     //xpsr
  //     //pc



  while (1)
  {
    
	Enable();
  Delays(1);
  Disable();
  Delays(1);
    //  BlueOn();
    //  Delays(1);
    //  BlueOff();
    //  Delays(1);
    // GreenOn();
  }
  
}
//#4 0100
//read LR bit 2 and IF then else EQUal block , equal to 1 load msp to r0,
// not equal copy psp to R0
void SVC_Handler(void)
{
  __asm(
    ".global SVC_Handler_Main\n"
    "TST lr, #4\n"
    "ITE EQ\n"
    "MRSEQ r0, MSP\n"
    "MRSNE r0, PSP\n"
    "B SVC_Handler_Main\n"
  ) ;
}
void SVC_Handler_Main( unsigned int *svc_args )
{
  unsigned int svc_number;

  /*
  * Stack contains:
  * r0, r1, r2, r3, r12, r14, the return address and xPSR
  * First argument (r0) is svc_args[0]
  */
  svc_number = ( ( char * )svc_args[ 6 ] )[ -2 ] ;
  switch( svc_number )
  {
    case 0:
		  BlueOn();
      break;
		case 1:
      BlueOff();
    default:

			break;
	}
	return;
}

//  unsigned int svc_number;
//   svc_number = ((char*)svc_args[6])[-2];      //-2 for first byte
//   switch(svc_number)
//   {
//       case 0:
//         svc_args[0]=  svc_args[0] + svc_args[1];    //refer docu.. if 2 parameter is passed. arg0 r0 first passed and so..
//       break;
//       case 1:
//         svc_args[0]=  svc_args[0] - svc_args[1];    
//       break;
//       case 2:
//         svc_args[0]=  svc_args[0] * svc_args[1];    
//       break;
//       case 3:
//         svc_args[0]=  svc_args[0] / svc_args[1];    
//       break;
//       default:
//         break;      


//   }
// }

void GPIO_Init(void)
{
  RCC->AHB1ENR |=GPIOB_CLOCK;
  GPIOB->MODER |= GREEN_MODE|BLUE_MODE|RED_MODE;
  SystemCoreClockUpdate();
  SysTick_Config(SystemCoreClock/100U);
  __enable_irq();
}

//System cortex function
void SysTick_Handler(void)
{
++tick;
}

uint32_t getTick(void)
{
  __disable_irq();
  _tick = tick;  //atomic instructions 3 asm to one asm to avoid race conditions
  __enable_irq();
  return _tick;
}

void Delays(uint32_t seconds)
{
  seconds *=100;
  uint32_t temp = getTick();
  while((getTick()-temp)<seconds){}

}

 void BlueOn(void)
{
  GPIOB->ODR |=BLUE_BIT;
}


 void BlueOff(void)
 {
   GPIOB->ODR &=~BLUE_BIT;
 }

 void GreenOn(void)
 {
   GPIOB->ODR |=GREEN_BIT;
 }


// void GreenOff(void)
// {
//   GPIOB->ODR &=~GREEN_BIT;
// }

