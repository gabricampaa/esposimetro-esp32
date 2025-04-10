#include "bh1750_mio.h"


#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/message_buffer.h"
#include "esp_log.h"
#include "soc/adc_channel.h"
#include "esp_adc/adc_oneshot.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "driver/gpio.h"
#include "esp_netif.h"
#include "esp_log.h"
#include <stdio.h>
#include <math.h>
#include "driver/i2c.h"
#include "esp_check.h"


#define TAG "DRIVERO LUX---"


esp_err_t bh1750_init(i2c_master_bus_handle_t bus, i2c_master_dev_handle_t *device) {
    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = 0x23, // BH1750 address
        .scl_speed_hz = 100000,
    };
    return i2c_master_bus_add_device(bus, &dev_cfg, device);
}

esp_err_t bh1750_read_lux(i2c_master_dev_handle_t device, float *lux) {
    uint8_t cmd = 0x10;  // Continuously H-Resolution mode
    ESP_RETURN_ON_ERROR(i2c_master_transmit(device, &cmd, 1, -1), TAG, "Write failed");

    vTaskDelay(pdMS_TO_TICKS(180)); // Max conversion time

    uint8_t data[2];
    ESP_RETURN_ON_ERROR(i2c_master_receive(device, data, 2, -1), TAG, "Read failed");

    uint16_t raw = (data[0] << 8) | data[1];
    *lux = raw / 1.2;
    return ESP_OK;
}
