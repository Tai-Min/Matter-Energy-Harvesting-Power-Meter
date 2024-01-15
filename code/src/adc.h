#pragma once
#include <zephyr/drivers/adc.h>

namespace adc
{
struct Measurement {
	bool success;
	int32_t value;
};

bool Init();
Measurement ReadBurdenVoltage();
Measurement ReadCapVoltage();
} // namespace adc