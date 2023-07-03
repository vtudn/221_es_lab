#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

void cyclictask()
{
    while (1)
    {
        printf("1952521\n");
        vTaskDelay(2200 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void acyclictask()
{
    while (1)
    {
        printf("ESP32\n");
        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void app_main(void)
{
    xTaskCreate(
        cyclictask,
        "cyclic ",
        1024 * 2,
        NULL,
        1,
        NULL);
    xTaskCreate(
        acyclictask,
        "acyclic ",
        1024 * 2,
        NULL,
        1,
        NULL);
}