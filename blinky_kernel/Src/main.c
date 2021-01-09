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

int main()
{
  GPIO_Init();  
  while (1)
  {
    GPIOB->ODR ^=RED_BIT|BLUE_BIT|GREEN_BIT;
    Delays(1);
    //for(int i=0;i<500000;i++){  }
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
  while((getTick()-temp)<seconds){

  }

}