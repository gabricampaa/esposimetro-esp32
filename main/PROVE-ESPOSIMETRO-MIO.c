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

#include "ssd1306.h"
#include "font8x8_basic.h"

#include "src/joy_stick.h"
//#include "bh1750_mio.h"

#define tag "MIEI_TEST---"

//0x3C è schermo OLED
//0x23 è BH1750

//#define SCL_PIN_LED 21 //D21
//#define SDA_PIN_LED 22 //D22

typedef enum  {
  STATE_READING_LIGHT,
  STATE_MENU_JOYSTICK_MOVEMENT,
  STATE_SETTING_ADJUST,
  STATE_LOCKED
}AppState;


void init_LCD(SSD1306_t dev);// wip

void app_main(void)
{

SSD1306_t dev;
	int center, top, bottom;
	char lineChar[20];


	ESP_LOGI(tag, "INTERFACE is i2c");
	ESP_LOGI(tag, "CONFIG_SDA_GPIO=%d",CONFIG_SDA_GPIO);
	ESP_LOGI(tag, "CONFIG_SCL_GPIO=%d",CONFIG_SCL_GPIO);
	ESP_LOGI(tag, "CONFIG_RESET_GPIO=%d",CONFIG_RESET_GPIO);
	i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);


	ESP_LOGI(tag, "Panel is 128x64");
	ssd1306_init(&dev, 128, 64);


	top = 2;
	center = 3;
	bottom = 8;
	ssd1306_display_text(&dev, 0, "Benvenuto!", 12, false);
	ssd1306_display_text(&dev, 2, "3 secondi", 10, false);
    ssd1306_display_text(&dev, 3, "e si va", 8, false);
	ssd1306_display_text(&dev, 4, "lol\n",3, false);
	ssd1306_display_text(&dev, 5, "si vola", 8, false);



joystick_t my_joystick = {
        .x_channel = ADC1_CHANNEL_6,  // GPIO34
        .y_channel = ADC1_CHANNEL_7,  // GPIO35
        .sw_gpio = GPIO_NUM_32        // Pulsante
    };

    joystick_state_t state;

    joystick_init(&my_joystick);

for(int i = 5; i >= 0; i--) {
    int number = i;
    char ch = (char)(number + '0');  // Convert 0 -> '0', 1 -> '1', etc.

    char ch_str[2];
    ch_str[0] = ch;
    ch_str[1] = '\0';  // Null-terminate the string

    ssd1306_display_text(&dev, 6, ch_str, 1, false);
    vTaskDelay(pdMS_TO_TICKS(1000));
    ssd1306_clear_line(&dev, 6, true);
    ssd1306_clear_screen(&dev, false);
}



//vTaskDelay(pdMS_TO_TICKS(5000));  // 1000ms = 1 second
ssd1306_clear_screen(&dev, false);

ssd1306_display_text(&dev, 1, "We are RUNNIN!", 16, false);



    while (1) {


        joystick_read(&my_joystick, &state);
        printf("X: %d, Y: %d, Button: %s\n",
               state.x_value,
               state.y_value,
               state.button_pressed ? "Pressed" : "Released");
        vTaskDelay(pdMS_TO_TICKS(200));

  if(state.x_value==0){
  ESP_LOGW(tag, "vai a sx");
  ssd1306_display_text(&dev, 3, "SX",4, false);
  vTaskDelay(pdMS_TO_TICKS(500));  // 1000ms = 1 second
  ssd1306_clear_line(&dev, 3, true);
  //ssd1306_clear_screen(&dev, false);
  }
  else if (state.x_value==4095){
  ESP_LOGW(tag, "vai a dx");
  ssd1306_display_text(&dev, 3, "DX",4, false);
  vTaskDelay(pdMS_TO_TICKS(500));  // 1000ms = 1 second
  ssd1306_clear_line(&dev, 3, true);
  //ssd1306_clear_screen(&dev, false);
  }



	//esp_restart();
}
}



/*
https://app.diagrams.net/?src=about
HANDLER BUTTON
HANDLER LCD_SCREEN-> I2C interface
HANDLER ESPOSSIMETRO

*/
#define SCL_PIN_LED 21 //D21
#define SDA_PIN_LED 22 //D22

#define JOYSTICK_VRX_GPIO 32// oppure 32
#define JOYSTICK_VRY_GPIO 33 // oppure 33

#define LIGHT_SENSOR_I2C_SCL 19 //A5 ARDUINO
#define LIGHT_SENSOR_I2C_SDA 18 //A4




//AppState currentState = STATE_READING_LIGHT;
/*
void loop() {
  readJoystick();
  updateState();        // Cambia stato se serve
  readSensorIfNeeded(); // Solo se nello stato giusto
  calculateExposure();
  renderScreen();       // Disegna solo ciò che serve
}


unsigned long lastUpdate = 0;
void renderScreen() {
  if (millis() - lastUpdate > 500) {
    // aggiorna display
    lastUpdate = millis();
  }
}

*/
