/*
 * bmsEmulation.c
 *
 *  Created on: Sep 1, 2023
 *      Author: GGPC
 */

#include <emulatedBMSStatus.h>
#include <main.h>
#include <sys/_stdint.h>

extern CAN_HandleTypeDef hcan;
extern uint32_t Tx_mailbox;


extern CAN_TxHeaderTypeDef TxHeaderTSActive;

extern CAN_TxHeaderTypeDef TxHeaderBmsDataPack0;
extern CAN_TxHeaderTypeDef TxHeaderBmsDataPack1;
extern CAN_TxHeaderTypeDef TxHeaderBmsDataPack2;
extern CAN_TxHeaderTypeDef TxHeaderBmsDataPack3;
extern CAN_TxHeaderTypeDef TxHeaderBmsDataPack4;
extern CAN_TxHeaderTypeDef TxHeaderBmsDataPack5;

extern CAN_TxHeaderTypeDef TxHeaderTemBMSBroadcast;
extern CAN_TxHeaderTypeDef TxHeaderTemGenBroadcast;

extern EmulatedBMSStatus bmsStatus;


void SendCanFrames(HAL_TIM_ActiveChannel timChannel) {

	uint8_t TxData[8];
	uint8_t checksum;

    if(timChannel == HAL_TIM_ACTIVE_CHANNEL_1) {
        // Send 48ms period CAN Frame

    	// Send Data Pack 5 - Custom Flags
    	 TxData[0] = 0x00;
    	 TxData[1] = 0x00;
    	 TxData[2] = 0x00;
    	 TxData[3] = 0x00;
    	 TxData[4] = 0x00;
    	 TxData[5] = 0x00;
    	 TxData[6] = 0x48;
    	 HAL_GPIO_TogglePin(FAULT_LED_GPIO_Port, FAULT_LED_Pin);

    	if (HAL_CAN_AddTxMessage(&hcan, &TxHeaderBmsDataPack5, TxData, &Tx_mailbox) != HAL_OK)
    				Error_Handler();
    }
    else if(timChannel == HAL_TIM_ACTIVE_CHANNEL_2) {
    	// Send 56ms period CAN Frames

    	// Send Data Pack 3 - Cell Voltages
    	 TxData[0] = (bmsStatus.maxCellVoltage >> 8) & 0xFF;
    	 TxData[1] = bmsStatus.maxCellVoltage & 0xFF;

    	 uint16_t avgCellVoltage = (bmsStatus.maxCellVoltage + bmsStatus.minCellVoltage)/2;
    	 TxData[2] = (avgCellVoltage >> 8) & 0xFF;
    	 TxData[3] = avgCellVoltage & 0xFF;

    	 TxData[4] = (bmsStatus.minCellVoltage >> 8) & 0xFF;
    	 TxData[5] = bmsStatus.minCellVoltage & 0xFF;

    	 TxData[6] = 0x00;

    	 checksum = 0x00; // TODO
    	 TxData[7] = checksum;
    	 HAL_GPIO_TogglePin(FAULT_LED_GPIO_Port, FAULT_LED_Pin);
    	if (HAL_CAN_AddTxMessage(&hcan, &TxHeaderBmsDataPack3, TxData, &Tx_mailbox) != HAL_OK)
    				Error_Handler();

    	// Send Data Pack 4 - Pack Temperature
    	 TxData[0] = 0x00;
    	 TxData[1] = 0x00;
    	 TxData[2] = 0x00;
    	 TxData[3] = 0x00;
    	 TxData[4] = 0x00;
    	 TxData[5] = 0x00;
    	 TxData[6] = 0x56;

    	 checksum = 0x00; // TODO
    	 TxData[7] = checksum;
    	if (HAL_CAN_AddTxMessage(&hcan, &TxHeaderBmsDataPack4, TxData, &Tx_mailbox) != HAL_OK)
    				Error_Handler();
    }
    else if(timChannel == HAL_TIM_ACTIVE_CHANNEL_3) {
    	// Send 104ms period CAN Frames

    	// Send Data Pack 0 - Pack State 1
    	 TxData[0] = 0x00;
    	 TxData[1] = 0x00;
    	 TxData[2] = 0x00;
    	 TxData[3] = 0x00;
    	 TxData[4] = 0x00;
    	 TxData[5] = 0x01;
    	 TxData[6] = 0x56;

    	 checksum = 0x00; // TODO
    	 TxData[7] = checksum;
    	 HAL_GPIO_TogglePin(CUSTOM_LED_GPIO_Port, CUSTOM_LED_Pin);
    	if (HAL_CAN_AddTxMessage(&hcan, &TxHeaderBmsDataPack0, TxData, &Tx_mailbox) != HAL_OK)
    				Error_Handler();

    	// Send Data Pack 2 - Pack State 3
    	 TxData[0] = 0x00;
    	 TxData[1] = 0x00;
    	 TxData[2] = 0x00;
    	 TxData[3] = 0x00;
    	 TxData[4] = 0x00;
    	 TxData[5] = 0x02;
    	 TxData[6] = 0x56;

    	 checksum = 0x00; // TODO
    	 TxData[7] = checksum;
    	if (HAL_CAN_AddTxMessage(&hcan, &TxHeaderBmsDataPack2, TxData, &Tx_mailbox) != HAL_OK)
    				Error_Handler();
    }
    else if(timChannel == HAL_TIM_ACTIVE_CHANNEL_4) {
    	// Send 152ms period CAN Frame

    	// Send Data Pack 1 - Pack State 2
    	 TxData[0] = 0x00;
    	 TxData[1] = 0x00;
    	 TxData[2] = 0x00;
    	 TxData[3] = 0x00;
    	 TxData[4] = 0x00;
    	 TxData[5] = 0x01;
    	 TxData[6] = 0x52;

    	 checksum = 0x00; // TODO
    	 TxData[7] = checksum;
    	 HAL_GPIO_TogglePin(CUSTOM_LED_GPIO_Port, CUSTOM_LED_Pin);
    	if (HAL_CAN_AddTxMessage(&hcan, &TxHeaderBmsDataPack1, TxData, &Tx_mailbox) != HAL_OK)
    				Error_Handler();
    }
}
