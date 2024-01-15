#include "burden_ctrl.h"

#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(burden, CONFIG_CHIP_APP_LOG_LEVEL);

namespace burden
{

namespace
{
	constexpr gpio_dt_spec burden_ctrl_gpio_dt = GPIO_DT_SPEC_GET(DT_ALIAS(burden_ctrl), gpios);
    constexpr gpio_dt_spec charge_ctrl_gpio_dt = GPIO_DT_SPEC_GET(DT_ALIAS(burden_ctrl), gpios);
} // namespace

bool Init()
{
	if (!gpio_is_ready_dt(&burden_ctrl_gpio_dt)) {
		LOG_ERR("Failed to initialize burden GPIO");
		return false;
	}

	if (!gpio_is_ready_dt(&charge_ctrl_gpio_dt)) {
		LOG_ERR("Failed to initialize charge GPIO");
		return false;
	}

	int err = gpio_pin_configure_dt(&burden_ctrl_gpio_dt, GPIO_OUTPUT);
	if (err) {
		LOG_ERR("Failed to configure burden gpio");
		return false;
	}

	err = gpio_pin_configure_dt(&charge_ctrl_gpio_dt, GPIO_OUTPUT);
	if (err) {
		LOG_ERR("Failed to configure burden gpio");
		return false;
	}

	return true;
}

bool SetMeasurementMode()
{
	int err = gpio_pin_set(charge_ctrl_gpio_dt.port, charge_ctrl_gpio_dt.pin, 1);
	if (err) {
		LOG_ERR("Failed to set charge pin");
		return false;
	}

	err = gpio_pin_set(burden_ctrl_gpio_dt.port, burden_ctrl_gpio_dt.pin, 0);
	if (err) {
		LOG_ERR("Failed to set burden pin");
		return false;
	}
	return true;
}

bool SetChargingMode()
{
	int err = gpio_pin_set(charge_ctrl_gpio_dt.port, charge_ctrl_gpio_dt.pin, 0);
	if (err) {
		LOG_ERR("Failed to set charge pin");
		return false;
	}

	err = gpio_pin_set(burden_ctrl_gpio_dt.port, burden_ctrl_gpio_dt.pin, 1);
	if (err) {
		LOG_ERR("Failed to set burden pin");
		return false;
	}
	return true;
}
} // namespace burden