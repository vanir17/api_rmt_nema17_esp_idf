#include <stdio.h>
#include "freertos/FreeRTOS.h" 
#include "freertos/task.h"     
#include "sdkconfig.h"
#include "rmt_nema.h"
#include "esp_log.h"

int count = 0;
void app_main(void)
{
    rmt_nema_config_t motor_config = {
        .dir_pin = 22,
        .step_pin = 23,
        .pulses_per_rev = 3200,
        .rmt_resolution_hz = 1000000, 
    };
    int32_t speed = 1000;
    ESP_ERROR_CHECK(init_rmt(&motor_config));


    printf("Starting motor...\n");
    rmt_nema_set_speed(&motor_config, speed);

    while(1)
    {
        speed = -2000;
        count = count + 1;
        rmt_nema_set_speed(&motor_config, speed);
        vTaskDelay(pdMS_TO_TICKS(1000)); 
        printf("%d\n", count);
    }
}