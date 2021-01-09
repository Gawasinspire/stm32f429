#include "stm32f4xx.h"

#define GREEN_MODE   (1U<<0)
#define BLUE_MODE  (1U<<14)
#define RED_MODE (1U<<28)
   
#define GREEN_BIT   (1U<<0)
#define BLUE_BIT  (1U<<7)
#define RED_BIT (1U<<14)


#define GPIOB_CLOCK  (1<<1)

int main()
{
  RCC->AHB1ENR |=GPIOB_CLOCK;
  GPIOB->MODER |= GREEN_MODE|BLUE_MODE|RED_MODE;

  while (1)
  {
    GPIOB->ODR |=RED_BIT|BLUE_BIT|GREEN_BIT;
  }
  
}