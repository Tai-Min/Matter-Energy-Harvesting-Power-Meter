#include "adc.h"
#include <zephyr/drivers/adc.h>
#include <zephyr/logging/log.h>

#include "params.h"
#include "burden_ctrl.h"

LOG_MODULE_REGISTER(adc, CONFIG_CHIP_APP_LOG_LEVEL);

namespace adc
{
namespace
{
	const device *adc_dev = DEVICE_DT_GET(DT_NODELABEL(adc));
	constexpr adc_channel_cfg burden_cfg_dt = ADC_CHANNEL_CFG_DT(DT_CHILD(DT_NODELABEL(adc), channel_0));

	// device *adc_battery_dev = DEVICE_DT_GET(DT_NODELABEL(adc));
	constexpr adc_channel_cfg battery_cfg_dt = ADC_CHANNEL_CFG_DT(DT_CHILD(DT_NODELABEL(adc), channel_1));

	constexpr uint8_t ADC_RESOLUTION = 10;

} // namespace

bool Init()
{
    if (!burden::Init())
    {
        LOG_ERR("Failed to initialize burden controller");
        return false;
    }

	if (!device_is_ready(adc_dev)) {
		LOG_ERR("ADC device is not ready");
		return false;
	}

	int err = adc_channel_setup(adc_dev, &burden_cfg_dt);
	if (err) {
		LOG_ERR("Couldn't setup burden ADC");
		return false;
	}

	err = adc_channel_setup(adc_dev, &battery_cfg_dt);
	if (err) {
		LOG_ERR("Couldn't setup battery ADC");
		return false;
	}
	return true;
}

Measurement ReadBurdenVoltage()
{
	static int16_t buffer[1];
	static adc_sequence seq = { .channels = BIT(burden_cfg_dt.channel_id),
				    .buffer = buffer,
				    .buffer_size = sizeof(buffer),
				    .resolution = ADC_RESOLUTION };
	static int32_t adcVRef = adc_ref_internal(adc_dev);

	Measurement res;

    burden::SetMeasurementMode();
	int err = adc_read(adc_dev, &seq);
	if (err) {
		LOG_WRN("Failed to read burden ADC");
        burden::SetChargingMode();
		res.success = false;
		return res;
	}

	int32_t mV = buffer[0];
	err = adc_raw_to_millivolts(adcVRef, burden_cfg_dt.gain, ADC_RESOLUTION, &mV);
	if (err) {
		LOG_WRN("Failed to convert burden reading to mV");
        burden::SetChargingMode();
		res.success = false;
		return res;
	}
    burden::SetChargingMode();

	res.value = mV;
	res.success = true;

	return res;
}

Measurement ReadCapVoltage()
{
	static int16_t buffer[1];
	static adc_sequence seq = { .channels = BIT(battery_cfg_dt.channel_id),
				    .buffer = buffer,
				    .buffer_size = sizeof(buffer),
				    .resolution = ADC_RESOLUTION };
	static int32_t adcVRef = adc_ref_internal(adc_dev);

	Measurement res;

	int err = adc_read(adc_dev, &seq);
	if (err) {
		LOG_WRN("Failed to read cap ADC");
		res.success = false;
		return res;
	}

	int32_t mV = buffer[0];
	err = adc_raw_to_millivolts(adcVRef, battery_cfg_dt.gain, ADC_RESOLUTION, &mV);
	if (err) {
		LOG_WRN("Failed to convert cap reading to mV");
		res.success = false;
		return res;
	}

	res.value = mV;
	res.success = true;

	return res;
}
} // namespace adc
