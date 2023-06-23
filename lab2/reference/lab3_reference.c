#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/FreeRTOSConfig.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "rtc_wdt.h"

static const char *pcTextForTask1 = "Task 1 is running\r\n";
static const char *pcTextForTask2 = "Task 2 is running\r\n";

void vTask1Function(void *pvParameters)
{
	char *pcTaskName;
	const TickType_t xDelay250ms = pdMS_TO_TICKS(250);
	pcTaskName = (char * ) pvParameters;
	for(;;)
	{
		printf ( pcTaskName );
		vTaskDelay(xDelay250ms);
	}
}
void vTask2Function(void *pvParameters)
{
	char *pcTaskName;
	const TickType_t xDelay250ms = pdMS_TO_TICKS(1250);
	pcTaskName = (char * ) pvParameters;
	for(;;)
	{
		printf ( pcTaskName );
		vTaskDelay(xDelay250ms);
	}
}

void app_main(void)
{
    //create task 1 at priority 1
	xTaskCreate(vTask1Function, "Task 1", 4096, (void*)pcTextForTask1, 1, NULL);
	//create task 2 at priority 2
    xTaskCreate(vTask2Function, "Task 2", 4096, (void*)pcTextForTask2, 2, NULL);
    //start task scheduler
    //rtc_wdt_protect_off();
    //rtc_wdt_disable();
    //rtc_wdt_feed();
    //vTaskStartScheduler();
}
