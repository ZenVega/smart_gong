#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "esp_log.h"		   //for showing logs
#include "freertos/FreeRTOS.h" //for delay,mutexs,semphrs rtos operations
#include "lwip/err.h"		   //light weight ip packets error handling
#include "lwip/sys.h"		   //system applications for light weight ip apps
#include "nvs_flash.h"		   //non volatile storage
#include <stdio.h>			   //for basic printf commands
#include <string.h>			   //for handling strings
							   //
#define WIFI_SSID CONFIG_WIFI_SSID
#define WIFI_PASS CONFIG_WIFI_PASSWORD
#define MAX_RETRY 10

#define LED_GPIO GPIO_NUM_2

#endif
