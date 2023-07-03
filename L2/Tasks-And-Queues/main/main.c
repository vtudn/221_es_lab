// #include <stdio.h>
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "freertos/queue.h"
// #include "esp_system.h"

// #define MaxQueueSize 3
// #define MaxElementsPerQueue 20

// char TxBuffer[5][MaxElementsPerQueue] = {"Hello!", "Nice", "to", "meet", "you!"};
// char RxBuffer[5][MaxElementsPerQueue];

// xTaskHandle SendTaskHandle;
// xTaskHandle ReceiveTaskHandle;
// xQueueHandle MessageQueueHandle;

// bool DataSent = false;
// bool DataReceived = false;

// void sender_task(void *pvParameter)
// {
//     unsigned char tx_int;
//     for (tx_int = 0; tx_int < 5; tx_int++)
//     {
//         if (!xQueueSend(MessageQueueHandle, TxBuffer[tx_int], 100))
//         {
//             printf("Failed to send the messages\n");
//         }
//         else
//         {
//             printf("Successfully sent data\n");
//         }
//         vTaskDelay(1000 / portTICK_PERIOD_MS);
//     }
//     DataSent = true;
//     vTaskDelete(SendTaskHandle);
// }

// void receiver_task(void *pvParameter)
// {
//     unsigned char rx_int;
//     for (rx_int = 0; rx_int < 5; rx_int++)
//     {
//         if (xQueueReceive(MessageQueueHandle, RxBuffer[rx_int], 100))
//         {
//             printf("Received data is: %s\n", RxBuffer[rx_int]);
//         }
//         else
//         {
//             printf("No Data received\n");
//         }
//         vTaskDelay(1000 / portTICK_PERIOD_MS);
//     }
//     DataReceived = true;
//     vTaskDelete(ReceiveTaskHandle);
// }

// void app_main()
// {
//     /* Initialize Queue */
//     MessageQueueHandle = xQueueCreate(MaxQueueSize, MaxElementsPerQueue);

//     /* create new task */
//     xTaskCreate(&sender_task, "tx_task", 2048, NULL, 1, &SendTaskHandle);
//     xTaskCreate(&receiver_task, "rx_task", 2048, NULL, 1, &ReceiveTaskHandle);

//     while (1)
//     {
//         if (DataSent && DataReceived)
//         {
//             printf("Restarting now.\n");
//             vTaskDelay(1000 / portTICK_PERIOD_MS);
//             fflush(stdout);
//             esp_restart();
//         }
//     }
// }

//                                                                                                                      ver 2 (use struct)
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_system.h"

TaskHandle_t taskHandle[3];
QueueHandle_t xQueue;

typedef struct
{
    int id;
    int data[10];
} QMsg_t;

bool DataSent = false;
bool DataReceived = false;

void TaskQueueSend1(void *args)
{
    QueueHandle_t queue = (QueueHandle_t)args;
    QMsg_t msg1;
    msg1.id = 1;
    msg1.data[0] = 1;
    msg1.data[1] = 2;
    while (true)
    {
        xQueueSend(queue, (void *)&msg1, 0);
        printf("TaskQueueSend 1\r\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        msg1.data[0] += 10;
        msg1.data[1] += 10;
    }
    DataSent = true;
    vTaskDelete(taskHandle[1]);
}

void TaskQueueSend2(void *args)
{
    QueueHandle_t queue = (QueueHandle_t)args;
    QMsg_t msg2;
    msg2.id = 2;
    msg2.data[0] = 3;
    msg2.data[1] = 4;
    while (true)
    {
        xQueueSend(queue, (void *)&msg2, 0);
        printf("TaskQueueSend 2\r\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        msg2.data[0] += 100;
        msg2.data[1] += 100;
    }
    DataSent = true;
    vTaskDelete(taskHandle[1]);
}

void TaskQueueRecv(void *args)
{
    QueueHandle_t queue = (QueueHandle_t)args;
    QMsg_t msg;
    UBaseType_t itemNums;
    BaseType_t ret;
    while (true)
    {
        itemNums = uxQueueMessagesWaiting(queue);
        printf("Items = %d\r\n", itemNums);
        if (itemNums)
        {
            ret = xQueueReceive(queue, &msg, 0);
            if (ret == pdTRUE)
            {
                printf("TaskRecv, id = %d data[0] = %d data[1] = %d \r\n", msg.id, msg.data[0], msg.data[1]);
            }
            else
            {
                printf("TaskRecv, not received.\r\n");
            }
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    DataReceived = true;
    vTaskDelete(taskHandle[0]);
}

void app_main()
{
    xQueue = xQueueCreate(10, sizeof(QMsg_t));
    xTaskCreatePinnedToCore(TaskQueueSend1, "TaskQueueSend1", 4096, xQueue, 10, &taskHandle[1], APP_CPU_NUM);
    xTaskCreatePinnedToCore(TaskQueueSend2, "TaskQueueSend2", 4096, xQueue, 10, &taskHandle[1], APP_CPU_NUM);
    xTaskCreatePinnedToCore(TaskQueueRecv, "TaskQueueRecv", 4096, xQueue, 11, &taskHandle[0], APP_CPU_NUM);
    while (true)
    {
        if (DataSent && DataReceived)
        {
            printf("Restarting now.\n");
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            fflush(stdout);
            esp_restart();
        }
    }
}