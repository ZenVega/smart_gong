#include "esp_http_server.h" //esp_wifi_init functions and wifi operations
#include "esp_log.h"		 //for showing logs
#include "esp_netif.h"
#include "esp_netif_types.h"
#include "esp_wifi.h" //esp_wifi_init functions and wifi operations
#include "esp_wifi_types_generic.h"
#include "freertos/FreeRTOS.h" //for delay,mutexs,semphrs rtos operations
#include "lwip/err.h"		   //light weight ip packets error handling
#include "lwip/sys.h"		   //system applications for light weight ip apps
#include "nvs_flash.h"		   //non volatile storage
#include <esp_event.h>
#include <esp_https_server.h>
#include <esp_log.h>
#include <esp_system.h>
#include <esp_wifi.h>
#include <nvs_flash.h>
#include <stdio.h>	//for basic printf commands
#include <string.h> //for handling strings
#include <sys/param.h>

#include "esp_tls.h"
#include "sdkconfig.h"
#include <esp_https_server.h>
