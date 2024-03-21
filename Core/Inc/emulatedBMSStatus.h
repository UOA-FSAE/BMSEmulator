/*
 * EmulatedBMSStatus.h
 *
 *  Created on: Sep 1, 2023
 *      Author: GGPC
 */

#ifndef INC_EMULATEDBMSSTATUS_H_
#define INC_EMULATEDBMSSTATUS_H_

#include <sys/_stdint.h>
#include <stdbool.h>

typedef struct {

	// Inputs from ADC
	bool tsActive;
	bool bmsActive;
	bool cellCount;
	bool spareToggle;

	// Inputs from Switches
	uint16_t maxCellVoltage;
	uint16_t minCellVoltage;
	uint16_t maxTemp;
	uint16_t spareADC;

	// Pack State 1
	uint16_t PackCurrent;
	uint16_t PackInstVoltage;
	uint8_t PackSOC;

	// Pack State 2
	uint16_t AdaptiveTotalCapacity;
	uint16_t AdaptiveSOC;
	uint8_t RollingCounter;

	// Pack State 3
	// uint16_t PackSOC; // DEFINED ABOVE
	uint8_t PackAmphours;
	uint8_t PackDOD;
	uint8_t PackHealth;

	// Cell Voltages
	uint16_t HighCellVoltage;
	uint16_t AvgCellVoltage;
	uint16_t LowCellVoltage;

	// Pack Temperature
	uint16_t HighTemperature;
	uint16_t AvgTemperature;
	uint8_t LowTemperature;

	// Custom Flags
	uint8_t CUSTOMFLAG; // ????
	uint16_t ConstantValue; // ????
	uint16_t MaximumCellVoltage;
	uint16_t PackCL;
} EmulatedBMSStatus;

#endif /* INC_EMULATEDBMSSTATUS_H_ */
