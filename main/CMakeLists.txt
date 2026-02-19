idf_component_register(
    SRCS "rmt_nema.c" "main.c"
    INCLUDE_DIRS "rmt_nema.h"
    REQUIRES driver esp_hw_support 
)