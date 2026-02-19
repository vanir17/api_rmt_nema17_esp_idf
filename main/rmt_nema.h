#ifndef rmt_nema_h
#define rmt_nema_h
#include "driver/rmt_tx.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "stdio.h"
#include "math.h"
#include "driver/gpio.h"

typedef struct 
{
    uint16_t step_pin;
    uint16_t dir_pin;
    uint64_t rmt_resolution_hz;
    uint64_t pulses_per_rev;
    uint64_t duration;
}rmt_nema_config_t;
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
esp_err_t init_rmt(const rmt_nema_config_t *config);





#endif /* rmt_nema_h*/  