#pragma once
#include <cstdint>

constexpr uint8_t ENDPOINT_ID = 1;

constexpr int32_t PARAM_DIVISOR = 1000;

constexpr uint8_t RMS_MAX_SAMPLES = 50;

constexpr int32_t MAINS_VOLTAGE = (230 * 1000); // mV
constexpr int32_t MAINS_FREQUENCY = 50; // Hz

constexpr int32_t MIN_CURR = 0; // mA
constexpr int32_t MAX_CURR = 800; // mA
constexpr int32_t BURDE_VALUE = 100; // mOhm

constexpr int32_t MIN_BURDEN_VOLTAGE = 0; // mV stop measure here due to critical voltage
constexpr int32_t MAX_BURDEN_VOLTAGE = 3000; // mV

constexpr int32_t MIN_BATTERY_VOLTAGE = 2100; // mV stop measure here due to critical voltage
constexpr int32_t MAX_BATTERY_VOLTAGE = 3000; // mV
