#pragma once

#include "driver/i2c_master.h"
#include "esp_err.h"

esp_err_t bh1750_init(i2c_master_bus_handle_t bus, i2c_master_dev_handle_t *device);
esp_err_t bh1750_read_lux(i2c_master_dev_handle_t device, float *lux);
