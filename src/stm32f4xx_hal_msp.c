/**
  ******************************************************************************
  * @file    stm32f4xx_hal_msp_template.c
  * @author  MCD Application Team
  * @version V1.7.1
  * @date    14-April-2017
  * @brief   This file contains the HAL System and Peripheral (PPP) MSP initialization
  *          and de-initialization functions.
  *          It should be copied to the application folder and renamed into 'stm32f4xx_hal_msp.c'.           
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/** @addtogroup STM32F4xx_HAL_Driver
  * @{
  */

/** @defgroup HAL_MSP HAL MSP
  * @brief HAL MSP module.
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup HAL_MSP_Private_Functions HAL MSP Private Functions
  * @{
  */

/**
  * @brief  Initializes the Global MSP.
  * @note   This function is called from HAL_Init() function to perform system
  *         level initialization (GPIOs, clock, DMA, interrupt).
  * @retval None
  */

extern DMA_HandleTypeDef hdma_adc1;

extern DMA_HandleTypeDef hdma_adc2;

extern DMA_HandleTypeDef hdma_adc3;

void HAL_MspInit(void)
{

}

/**
  * @brief  DeInitializes the Global MSP.
  * @note   This functiona is called from HAL_DeInit() function to perform system
  *         level de-initialization (GPIOs, clock, DMA, interrupt).
  * @retval None
  */
void HAL_MspDeInit(void)
{

}

/**
  * @brief  Initializes the PPP MSP.
  * @note   This functiona is called from HAL_PPP_Init() function to perform 
  *         peripheral(PPP) system level initialization (GPIOs, clock, DMA, interrupt)
  * @retval None
  */
void HAL_PPP_MspInit(void)
{

}

/**
  * @brief  DeInitializes the PPP MSP.
  * @note   This functiona is called from HAL_PPP_DeInit() function to perform 
  *         peripheral(PPP) system level de-initialization (GPIOs, clock, DMA, interrupt)
  * @retval None
  */
void HAL_PPP_MspDeInit(void)
{

}


void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
	  //GPIO_InitTypeDef GPIO_InitStruct;
	  if(hadc->Instance==ADC1)
	  {
	  /* USER CODE BEGIN ADC1_MspInit 0 */

	  /* USER CODE END ADC1_MspInit 0 */
	    /* Peripheral clock enable */
	    __HAL_RCC_ADC1_CLK_ENABLE();

	    /* ADC1 DMA Init */
	    /* ADC1 Init */
	    hdma_adc1.Instance = DMA2_Stream0;
	    hdma_adc1.Init.Channel = DMA_CHANNEL_0;
	    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
	    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
	    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
	    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
	    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
	    hdma_adc1.Init.Mode = DMA_CIRCULAR;
	    hdma_adc1.Init.Priority = DMA_PRIORITY_LOW;
	    hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	    if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
	    {
	     // _Error_Handler(__FILE__, __LINE__);
	    }

	    __HAL_LINKDMA(hadc,DMA_Handle,hdma_adc1);

	    /* ADC1 interrupt Init */
	    HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
	    HAL_NVIC_EnableIRQ(ADC_IRQn);
	  /* USER CODE BEGIN ADC1_MspInit 1 */

	  /* USER CODE END ADC1_MspInit 1 */
	  }
  else if(hadc->Instance==ADC2)
  {
    /* Peripheral clock enable */
    __HAL_RCC_ADC2_CLK_ENABLE();

    /* ADC2 DMA Init */
    /* ADC2 Init */
    hdma_adc2.Instance = DMA2_Stream2;
    hdma_adc2.Init.Channel = DMA_CHANNEL_1;
    hdma_adc2.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc2.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc2.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc2.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_adc2.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_adc2.Init.Mode = DMA_NORMAL;
    hdma_adc2.Init.Priority = DMA_PRIORITY_LOW;
    hdma_adc2.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_adc2) != HAL_OK)
    {
      //_Error_Handler(__FILE__, __LINE__);
    }

    __HAL_LINKDMA(hadc,DMA_Handle,hdma_adc2);

    /* ADC2 interrupt Init */
    HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(ADC_IRQn);
  }
  else if(hadc->Instance==ADC3)
  {
    /* Peripheral clock enable */
    __HAL_RCC_ADC3_CLK_ENABLE();

    /* ADC3 DMA Init */
    /* ADC3 Init */
    hdma_adc3.Instance = DMA2_Stream1;
    hdma_adc3.Init.Channel = DMA_CHANNEL_2;
    hdma_adc3.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc3.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc3.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc3.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_adc3.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_adc3.Init.Mode = DMA_NORMAL;
    hdma_adc3.Init.Priority = DMA_PRIORITY_LOW;
    hdma_adc3.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_adc3) != HAL_OK)
    {
      //_Error_Handler(__FILE__, __LINE__);
    }

    __HAL_LINKDMA(hadc,DMA_Handle,hdma_adc3);

    /* ADC3 interrupt Init */
    HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(ADC_IRQn);
  }

}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{
  if(hadc->Instance==ADC1)
  {
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();

    /**ADC1 GPIO Configuration
    PC4     ------> ADC1_IN14
    PC5     ------> ADC1_IN15
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_4|GPIO_PIN_5);

    /* ADC1 DMA DeInit */
    HAL_DMA_DeInit(hadc->DMA_Handle);

    /* ADC1 interrupt DeInit */
  /* USER CODE BEGIN ADC1:ADC_IRQn disable */
    /**
    * Uncomment the line below to disable the "ADC_IRQn" interrupt
    * Be aware, disabling shared interrupt may affect other IPs
    */
    /* HAL_NVIC_DisableIRQ(ADC_IRQn); */
  /* USER CODE END ADC1:ADC_IRQn disable */

  }
  else if(hadc->Instance==ADC2)
  {
  /* USER CODE BEGIN ADC2_MspDeInit 0 */

  /* USER CODE END ADC2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC2_CLK_DISABLE();

    /**ADC2 GPIO Configuration
    PC0     ------> ADC2_IN10
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_0);

    /* ADC2 DMA DeInit */
    HAL_DMA_DeInit(hadc->DMA_Handle);

    /* ADC2 interrupt DeInit */
  /* USER CODE BEGIN ADC2:ADC_IRQn disable */
    /**
    * Uncomment the line below to disable the "ADC_IRQn" interrupt
    * Be aware, disabling shared interrupt may affect other IPs
    */
    /* HAL_NVIC_DisableIRQ(ADC_IRQn); */
  /* USER CODE END ADC2:ADC_IRQn disable */

  }
  else if(hadc->Instance==ADC3)
  {
  /* USER CODE BEGIN ADC3_MspDeInit 0 */

  /* USER CODE END ADC3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC3_CLK_DISABLE();

    /**ADC3 GPIO Configuration
    PC3     ------> ADC3_IN13
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_3);

    /* ADC3 DMA DeInit */
    HAL_DMA_DeInit(hadc->DMA_Handle);

    /* ADC3 interrupt DeInit */
  /* USER CODE BEGIN ADC3:ADC_IRQn disable */
    /**
    * Uncomment the line below to disable the "ADC_IRQn" interrupt
    * Be aware, disabling shared interrupt may affect other IPs
    */
    /* HAL_NVIC_DisableIRQ(ADC_IRQn); */
  /* USER CODE END ADC3:ADC_IRQn disable */

  }
}

void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{

  //GPIO_InitTypeDef GPIO_InitStruct;
  if(hspi->Instance==SPI1)
  {
	  GPIO_InitTypeDef GPIO_InitStruct;
	  	if(hspi->Instance==SPI1)
	  	{

	  		__SPI1_CLK_ENABLE();
	  		__GPIOA_CLK_ENABLE();

	  		GPIO_InitTypeDef  GPIO_InitStruct;

	  		GPIO_InitStruct.Pin       = GPIO_PIN_6;
	  		GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	  		GPIO_InitStruct.Pull      = GPIO_PULLUP;
	  		GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
	  		GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;

	  		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  		GPIO_InitStruct.Pin  = GPIO_PIN_5 | GPIO_PIN_7;
	  		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	  		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  		GPIO_InitStruct.Pin  = GPIO_PIN_4;
	  		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	  		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  		HAL_NVIC_SetPriority(SPI1_IRQn, 1,1);
	  		HAL_NVIC_EnableIRQ(SPI1_IRQn);
	  	  }
  }
  else if(hspi->Instance==SPI3)
  {
    /* Peripheral clock enable */
    __HAL_RCC_SPI3_CLK_ENABLE();
  }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* hspi)
{
  if(hspi->Instance==SPI1)
  {
    // Peripheral clock disable
    __HAL_RCC_SPI1_CLK_DISABLE();

    //SPI1 GPIO Configuration
    //PA5     ------> SPI1_SCK
    //PA6     ------> SPI1_MISO
    //PA7     ------> SPI1_MOSI
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
  }
  else if(hspi->Instance==SPI3)
  {
    /* Peripheral clock disable */
    __HAL_RCC_SPI3_CLK_DISABLE();
    //SPI3 GPIO Configuration
    //PC1     ------> SPI3_MOSI
    //PC10     ------> SPI3_SCK
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_1|GPIO_PIN_10);
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
