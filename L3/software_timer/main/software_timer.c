#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "freertos/timers.h"

#define NUM_OF_TIMERS 2

TimerHandle_t mytimer[NUM_OF_TIMERS];

char *mytimer_name[NUM_OF_TIMERS] = {"ahihi", "ihaha"};
uint32_t mytimer_delay[NUM_OF_TIMERS] = {2000, 3000};
uint16_t mytimer_countToStop[NUM_OF_TIMERS] = {10, 5};

void mytimer_callback(TimerHandle_t xTimer)
{
    const char *xTimer_name;
    xTimer_name = pcTimerGetName(xTimer);

    uint16_t xTimer_ID;
    for (long x = 0; x < NUM_OF_TIMERS; x++)
    {
        if (xTimer_name == mytimer_name[x])
            xTimer_ID = x;
    }
    
    const uint32_t ulMaxExpiryCountBeforeStopping = mytimer_countToStop[xTimer_ID];
    uint32_t ulCount;
    ulCount = (uint32_t)pvTimerGetTimerID(xTimer);
    ulCount++;
    if (ulCount > ulMaxExpiryCountBeforeStopping)
    {
        xTimerStop(xTimer, 0);
        printf("Timer %s has stopped!\n", xTimer_name);
    }
    else
    {
        vTimerSetTimerID(xTimer, (void *)ulCount);
        printf("Message: %s. Count: %d.\n", xTimer_name, ulCount);
    }
}

void app_main(void)
{
    printf("Timers start!\n");
    for (long x = 0; x < NUM_OF_TIMERS; x++)
    {
        mytimer[x] = xTimerCreate(mytimer_name[x], pdMS_TO_TICKS(mytimer_delay[x]), pdTRUE, (void *)0, mytimer_callback);
        xTimerStart(mytimer[x], 0);
    }

    for (int i = 0; i <= 30; i++)
    {
        printf("%ds\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    printf("Done! Restarting now.\n");
    fflush(stdout);
    esp_restart();

    /* Print chip information */
    // esp_chip_info_t chip_info;
    // esp_chip_info(&chip_info);
    // printf("This is %s chip with %d CPU core(s), WiFi%s%s, ",
    //         CONFIG_IDF_TARGET,
    //         chip_info.cores,
    //         (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
    //         (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    // printf("silicon revision %d, ", chip_info.revision);

    // printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
    //         (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    // printf("Minimum free heap size: %d bytes\n", esp_get_minimum_free_heap_size());
}
