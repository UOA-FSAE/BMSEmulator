/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */
extern CAN_TxHeaderTypeDef TxHeaderBmsDataPack0;
extern CAN_TxHeaderTypeDef TxHeaderBmsDataPack1;
extern CAN_TxHeaderTypeDef TxHeaderBmsDataPack2;
extern CAN_TxHeaderTypeDef TxHeaderBmsDataPack3;
extern CAN_TxHeaderTypeDef TxHeaderBmsDataPack4;
extern CAN_TxHeaderTypeDef TxHeaderBmsDataPack5;

extern CAN_TxHeaderTypeDef TxHeaderTemBMSBroadcast;
extern CAN_TxHeaderTypeDef TxHeaderTemGenBroadcast;
/* USER CODE END 0 */

CAN_HandleTypeDef hcan;

/* CAN init function */
void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */
	// Data Pack 0 - Pack State 1
	TxHeaderBmsDataPack0.StdId = 0x6B0;
	TxHeaderBmsDataPack0.DLC = 8;
	TxHeaderBmsDataPack0.RTR = CAN_RTR_DATA;
	TxHeaderBmsDataPack0.IDE = CAN_ID_STD;
	TxHeaderBmsDataPack0.TransmitGlobalTime = DISABLE;

	// Data Pack 1 - Pack State 2
	TxHeaderBmsDataPack1.StdId = 0x6B1;
	TxHeaderBmsDataPack1.DLC = 8;
	TxHeaderBmsDataPack1.RTR = CAN_RTR_DATA;
	TxHeaderBmsDataPack1.IDE = CAN_ID_STD;
	TxHeaderBmsDataPack1.TransmitGlobalTime = DISABLE;

	// Data Pack 2 - Pack State 3
	TxHeaderBmsDataPack2.StdId = 0x6B2;
	TxHeaderBmsDataPack2.DLC = 8;
	TxHeaderBmsDataPack2.RTR = CAN_RTR_DATA;
	TxHeaderBmsDataPack2.IDE = CAN_ID_STD;
	TxHeaderBmsDataPack2.TransmitGlobalTime = DISABLE;

	// Data Pack 3 - Cell Voltages
	TxHeaderBmsDataPack3.StdId = 0x6B3;
	TxHeaderBmsDataPack3.DLC = 8;
	TxHeaderBmsDataPack3.RTR = CAN_RTR_DATA;
	TxHeaderBmsDataPack3.IDE = CAN_ID_STD;
	TxHeaderBmsDataPack3.TransmitGlobalTime = DISABLE;

	// Data Pack 4 - Pack Temperature
	TxHeaderBmsDataPack4.StdId = 0x6B4;
	TxHeaderBmsDataPack4.DLC = 8;
	TxHeaderBmsDataPack4.RTR = CAN_RTR_DATA;
	TxHeaderBmsDataPack4.IDE = CAN_ID_STD;
	TxHeaderBmsDataPack4.TransmitGlobalTime = DISABLE;

	// Data Pack 5 - Custom Flags
	TxHeaderBmsDataPack5.StdId = 0x618;
	TxHeaderBmsDataPack5.DLC = 7;
	TxHeaderBmsDataPack5.RTR = CAN_RTR_DATA;
	TxHeaderBmsDataPack5.IDE = CAN_ID_STD;
	TxHeaderBmsDataPack5.TransmitGlobalTime = DISABLE;

	// TEM BMS Broadcast
	TxHeaderTemBMSBroadcast.StdId = 0x1838F380;
	TxHeaderTemBMSBroadcast.DLC = 8;
	TxHeaderTemBMSBroadcast.RTR = CAN_RTR_DATA;
	TxHeaderTemBMSBroadcast.IDE = CAN_ID_EXT;
	TxHeaderTemBMSBroadcast.TransmitGlobalTime = DISABLE;

	// TEM Gen Broadcast
	TxHeaderTemGenBroadcast.StdId = 0x1839F380;
	TxHeaderTemGenBroadcast.DLC = 8;
	TxHeaderTemGenBroadcast.RTR = CAN_RTR_DATA;
	TxHeaderTemGenBroadcast.IDE = CAN_ID_EXT;
	TxHeaderTemGenBroadcast.TransmitGlobalTime = DISABLE;


  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN;
  hcan.Init.Prescaler = 16;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_1TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */

	if (HAL_CAN_Start(&hcan) != HAL_OK)
	{
	  /* Start Error */
	  Error_Handler();
	}


  /* USER CODE END CAN_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN)
  {
  /* USER CODE BEGIN CAN_MspInit 0 */

  /* USER CODE END CAN_MspInit 0 */
    /* CAN clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**CAN GPIO Configuration
    PB8     ------> CAN_RX
    PB9     ------> CAN_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_CAN;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN CAN_MspInit 1 */

  /* USER CODE END CAN_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN)
  {
  /* USER CODE BEGIN CAN_MspDeInit 0 */

  /* USER CODE END CAN_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN GPIO Configuration
    PB8     ------> CAN_RX
    PB9     ------> CAN_TX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8|GPIO_PIN_9);

  /* USER CODE BEGIN CAN_MspDeInit 1 */

  /* USER CODE END CAN_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
