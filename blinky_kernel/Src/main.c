#include "stm32f4xx.h"

#define GREEN_MODE   (1U<<0)
#define BLUE_MODE  (1U<<14)
#define RED_MODE (1U<<28)
   
#define GREEN_BIT   (1U<<0)
#define BLUE_BIT  (1U<<7)
#define BLUE_BIT_RESET (0U<<7)
#define RED_BIT (1U<<14)


#define GPIOB_CLOCK  (1<<1)
//this piece of code changes without anyother code
volatile uint32_t tick;
volatile uint32_t _tick;

void GPIO_Init(void);
void Delays(uint32_t seconds);
void BlueOn(void);
void BlueOff(void);
void GreenOn(void);
void GreenOff(void);

uint32_t green_stack[40];
uint32_t blue_stack[40];

uint32_t *sp_green = &green_stack[40];
uint32_t *sp_blue = &blue_stack[40];
//simple thread examples
int blue_main()
{
  while (1)
  {  
    BlueOn();
    Delays(1);
    BlueOff();
    Delays(1);
 }  
}


int green_main()
{
  while (1)
  {
    GreenOn();
    Delays(1);
    GreenOff();
    Delays(1);
  }
   
}
int main()
{ 
  GPIO_Init();  
  //stack frame for green thread
      *(--sp_green) = (1U << 24);   /*xpsr*/
      *(--sp_green) = (uint32_t)&green_main; /*pc*/
      *(--sp_green) = 0x0000000DU;   /*LR */
      *(--sp_green) = 0x0000000EU;   /*R12*/
      *(--sp_green) = 0x0000000AU;   /*R3 */
      *(--sp_green) = 0x0000000EU;   /*R2 */
      *(--sp_green) = 0x0000000AU;   /*R1 */
      *(--sp_green) = 0x0000000DU;   /*R0 */
  
  //stack frame for blue thread
      *(--sp_blue) = (1U << 24);   /*xpsr*/
      *(--sp_blue) = (uint32_t)&blue_main; /*pc*/
      *(--sp_blue) = 0x0000000BU;   /*LR */
      *(--sp_blue) = 0x0000000EU;   /*R12*/
      *(--sp_blue) = 0x0000000EU;   /*R3 */
      *(--sp_blue) = 0x0000000EU;   /*R2 */
      *(--sp_blue) = 0x0000000EU;   /*R1 */
      *(--sp_blue) = 0x0000000FU;   /*R0 */
  
  while (1)
  {
  }
  
}

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


void GreenOff(void)
{
  GPIOB->ODR &=~GREEN_BIT;
}

