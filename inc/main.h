/**
  ******************************************************************************
  * @file    SysTick/main.h 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    19-September-2011
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************  
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include <System.h>

static __IO uint32_t TimingDelay;
static void DelayMS(__IO uint32_t nTime);
static void DelayMS(__IO uint32_t nTime)
{ 
  int i;
  /*TimingDelay = nTime;
  while(TimingDelay != 0);*/
  /*while(nTime-- > 0)
  {
    for(i = 0; i < 1638/2; i++) asm volatile ("nop");
  }*/
  volatile uint32_t end=SysTickCounter+nTime;
  while(SysTickCounter!=end) asm volatile ("nop");
}
static void DelayMSMIN(__IO uint32_t nTime)
{ 
  while(nTime-- > 0)
  {
    for(int i = 0; i < 10; i++) asm volatile ("nop");
  }
}

#define Wait_Clock for(int i = 0; i < 200; i++) asm("nop");

/*{
  volatile uint32_t end=SysTickCounter+nTime;
  while(SysTickCounter!=end) asm volatile ("nop");;
}*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void TimingDelay_Decrement(void);

#endif /* __MAIN_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
