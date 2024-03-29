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

extern CAN_TxHeaderTypeDef TxHeaderMotecKeepalive;

extern CAN_TxHeaderTypeDef TxHeaderTemBMSBroadcast;
extern CAN_TxHeaderTypeDef TxHeaderTemGenBroadcast;

extern EmulatedBMSStatus bmsStatus;

uint8_t calculateChecksum(uint16_t canID, uint8_t FrameData[8]) {
	uint32_t checksum = canID + 8;
	for (uint8_t i = 0; i < 7; i++) {
		checksum += FrameData[i];
	}
	checksum &= 0xFF;
	return checksum;

}

void SendCanFrames(uint16_t timeElapsed) {
	uint8_t TxData[8];
	HAL_GPIO_WritePin(CUSTOM_LED_GPIO_Port, CUSTOM_LED_Pin, GPIO_PIN_SET);
	if (timeElapsed % 48 == 0) {
		// Send 48ms period CAN Frame

		// Send Data Pack 5 - Custom Flags - 0x618
		TxData[0] = 0x00; // Custom Flag
		TxData[1] = 0x00; // Constant Value H
		TxData[2] = 0x00; // Constant value L
		TxData[3] = bmsStatus.MaximumCellVoltage >> 8;
		TxData[4] = bmsStatus.MaximumCellVoltage & 0xFF;
		TxData[5] = 0x00; // Pack CCL H
		TxData[6] = 0x00; // Pack CCL L
		TxData[7] = 0x00;


		while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) == 0) {
			// wait for free mailbox
		}
		if (HAL_CAN_AddTxMessage(&hcan, &TxHeaderBmsDataPack5, TxData, &Tx_mailbox) != HAL_OK)
			Error_Handler();

		// Send Motec Keepalive - 0x100
		TxData[0] = 0x01; // Keepalive
		TxData[1] = 0x00;
		TxData[2] = 0x00;
		TxData[3] = 0x00;
		TxData[4] = 0x00;
		TxData[5] = 0x00;
		TxData[6] = 0x00;
		TxData[7] = 0x00;


		while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) == 0) {
			// wait for free mailbox
		}
		if (HAL_CAN_AddTxMessage(&hcan, &TxHeaderMotecKeepalive, TxData, &Tx_mailbox) != HAL_OK)
			Error_Handler();
	} else if (timeElapsed % 56 == 0) {
		// Send 56ms period CAN Frames

		// Send Data Pack 3 - Cell Voltages - 0x6B3
		TxData[0] = (bmsStatus.maxCellVoltage >> 8) & 0xFF;
		TxData[1] = bmsStatus.maxCellVoltage & 0xFF;

		uint16_t avgCellVoltage = (bmsStatus.maxCellVoltage
				+ bmsStatus.minCellVoltage) / 2;
		TxData[2] = (avgCellVoltage >> 8) & 0xFF;
		TxData[3] = avgCellVoltage & 0xFF;

		TxData[4] = (bmsStatus.minCellVoltage >> 8) & 0xFF;
		TxData[5] = bmsStatus.minCellVoltage & 0xFF;

		TxData[6] = bmsStatus.NumCells;

		TxData[7] = calculateChecksum(TxHeaderBmsDataPack3.StdId, TxData);
		while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) == 0) {
			// wait for free mailbox
		}
		if (HAL_CAN_AddTxMessage(&hcan, &TxHeaderBmsDataPack3, TxData, &Tx_mailbox) != HAL_OK)
			Error_Handler();

		// Send Data Pack 4 - Pack Temperature - 0x6B4
		TxData[0] = bmsStatus.HighTemperature >> 8; // High Temp H
		TxData[1] = bmsStatus.HighTemperature & 0xFF; // High Temp L
		TxData[2] = bmsStatus.AvgTemperature >> 8; // Avg Temp H
		TxData[3] = bmsStatus.AvgTemperature & 0xFF; // Avg Temp L
		TxData[4] = bmsStatus.LowTemperature >> 8; // Low Temp H
		TxData[5] = bmsStatus.LowTemperature & 0xFF; // Low Temp L
		TxData[6] = 0x00; // Blank

		TxData[7] = calculateChecksum(TxHeaderBmsDataPack4.StdId, TxData);
		while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) == 0) {
			// wait for free mailbox
		}
		if (HAL_CAN_AddTxMessage(&hcan, &TxHeaderBmsDataPack4, TxData, &Tx_mailbox) != HAL_OK)
			Error_Handler();
	} else if (timeElapsed % 104 == 0) {
		// Send 104ms period CAN Frames

		// Send Data Pack 0 - Pack State 1 - 0x6B0
		TxData[0] = 0x00; // Pack Current H
		TxData[1] = 0x00; // Pack Current L
		TxData[2] = 0x00; // Pack Inst. Voltage H
		TxData[3] = 0x00; // Pack Inst. Voltage L
		TxData[4] = 0x00; // Pack SOC H
		TxData[5] = 0x00; // Pack SOC L
		TxData[6] = 0x00;

		TxData[7] = calculateChecksum(TxHeaderBmsDataPack0.StdId, TxData);

		while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) == 0) {
			// wait for free mailbox
		}
		if (HAL_CAN_AddTxMessage(&hcan, &TxHeaderBmsDataPack0, TxData, &Tx_mailbox) != HAL_OK)
			Error_Handler();

		// Send Data Pack 2 - Pack State 3 - 0x6B2
		TxData[0] = bmsStatus.PackSOC;
		TxData[1] = bmsStatus.PackAmphours;
		TxData[2] = bmsStatus.PackDOD;
		TxData[3] = bmsStatus.PackHealth;
		TxData[4] = 0x00;
		TxData[5] = 0x00;
		TxData[6] = 0x00;

		TxData[7] = calculateChecksum(TxHeaderBmsDataPack2.StdId, TxData);

		while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) == 0) {
			// wait for free mailbox
		}
		if (HAL_CAN_AddTxMessage(&hcan, &TxHeaderBmsDataPack2, TxData, &Tx_mailbox) != HAL_OK)
			Error_Handler();
	} else if (timeElapsed % 152 == 0) {
		// Send 152ms period CAN Frame

		// Send Data Pack 1 - Pack State 2
		TxData[0] = bmsStatus.AdaptiveTotalCapacity >> 8;
		TxData[1] = bmsStatus.AdaptiveTotalCapacity & 0xFF;
		TxData[2] = bmsStatus.AdaptiveSOC >> 8;
		TxData[3] = bmsStatus.AdaptiveSOC & 0xFF;
		TxData[4] = 0x00;
		TxData[5] = 0x00;
		TxData[6] = bmsStatus.RollingCounter;
		bmsStatus.RollingCounter++; // Increment counter

		TxData[7] = calculateChecksum(TxHeaderBmsDataPack1.StdId, TxData);

		while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) == 0) {
			// wait for free mailbox
		}
		if (HAL_CAN_AddTxMessage(&hcan, &TxHeaderBmsDataPack1, TxData, &Tx_mailbox) != HAL_OK)
			Error_Handler();
	}


	HAL_GPIO_WritePin(CUSTOM_LED_GPIO_Port, CUSTOM_LED_Pin, GPIO_PIN_RESET);
}
