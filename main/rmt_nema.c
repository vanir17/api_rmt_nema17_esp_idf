#include "rmt_nema.h"

#define DIR_CW 0
#define DIR_CCW !DIR_CW
#define RMT_

/*******************************************************************************
 * Variables
 ******************************************************************************/
static rmt_symbol_word_t *g_payload = NULL;
static rmt_encoder_handle_t g_copy_encoder = NULL;
static rmt_channel_handle_t g_tx_channel = NULL;

/*******************************************************************************
 * Functions
 ******************************************************************************/
static void init_rmt(const rmt_nema_config_t *config);

void rmt_nema(rmt_nema_config_t *config, float speed_hz, )
{
    init_rmt(config);
    gpio_set_level (config->)
    if(g_payload == NULL)
    {
        return ESP_FAILED;
    }

    for (int i = 0; i < config->pulses_per_rev; i++)
    {
        g_payload[i].level0 = DIR_CW;
        g_payload[i].duration0 = config->duration;
        g_payload[i].level1 = DIR_CCW;
        g_payload[i].duration1 = config->duration;
    }



}

static void init_rmt(const rmt_nema_config_t *config)
{
    gpio_config_t dir_conf = {
        .pin_bit_mask = (1ULL << config->dir_pin), //1: giá trị 01, ULL: unsigned long long(8byte - 64bit), <<: dịch trái
        .mode = GPIO_MODE_OUTPUT, // OUTPUT
        .pull_up_en = GPIO_PULLUP_DISABLE, 
        .pull_down_en = GPIO_PULLDOWN_DISABLE, 
        .intr_type = GPIO_INTR_DISABLE, 
    };
    gpio_config(&dir_conf);

    //RMT Channel Config
    rmt_tx_channel_config_t tx_chan_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT, 
        .gpio_num = config->step_pin,   
        .mem_block_symbols = 128, 
        .resolution_hz = config->rmt_resolution_hz, 
        .trans_queue_depth = 4, 
    };
    ESP_ERROR_CHECK(rmt_new_tx_channel(&tx_chan_config, &g_tx_channel));
    ESP_ERROR_CHECK(rmt_enable(g_tx_channel));

    rmt_copy_encoder_config_t copy_encoder_config = {};
    ESP_ERROR_CHECK(rmt_new_copy_encoder(&copy_encoder_config, &g_copy_encoder));
    rmt_transmit_config_t tx_config = {
        .loop_count = -1,
    };
    size_t size = config->pulses_per_rev * sizeof(rmt_symbol_word_t);
    g_payload = (rmt_symbol_word_t *)malloc(size);
}


