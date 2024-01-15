#pragma once
#include "params.h"

int32_t ConvertBatteryVoltageToPercent(int32_t mV)
{
	int32_t res = (100 * (mV - MIN_BATTERY_VOLTAGE)) / MAX_BATTERY_VOLTAGE;
	if (res < 0) {
		res = 0;
	}
	if (res > 100) {
		res = 100;
	}
	return res;
}

float map(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}