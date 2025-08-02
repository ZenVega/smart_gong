#include <stdio.h> //for basic printf commands
#include <string.h> //for handling strings
#include "freertos/FreeRTOS.h" //for delay,mutexs,semphrs rtos operations
#include "esp_system.h" //esp_init funtions esp_err_t 
#include "esp_wifi.h" //esp_wifi_init functions and wifi operations
#include "esp_log.h" //for showing logs
#include "esp_event.h" //for wifi event
#include "nvs_flash.h" //non volatile storage
#include "lwip/err.h" //light weight ip packets error handling
#include "lwip/sys.h" //system applications for light weight ip apps

int retry_num = 0;

//event handler for wifi events, basically logging the wifi connection
static void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
	switch(event_id)
	{
		case WIFI_EVENT_STA_START:
		{
			printf("WIFI CONNECTING...\n");
			break;
		}
		case WIFI_EVENT_STA_CONNECTED:
		{
			printf("WIFI CONNECTED\n");
			retry_num = 0;
			break;
		}
		case WIFI_EVENT_STA_DISCONNECTED:
		{
			printf("WIFI DISCONNECTED\n");
			if (retry_num < 5){
				esp_wifi_connect();
				retry_num++;
				printf("Retrying to Connect...\n");
			}
			break;
		}
		case IP_EVENT_STA_GOT_IP:
		{
			printf("WIFI GOT IP\n");
			break;
		}
		default:
		{
			printf("WIFI UNKNOWN EVENT\n");
		}
	}
}

void wifi_connection(void)
{
	esp_netif_init(); //Initialize the underlying TCP/IP stack.
	esp_event_loop_create_default(); //responsible for creating and dispatching events
	esp_netif_create_default_wifi_sta(); //creates structs for wifi-station
	wifi_init_config_t wifi_initiation = WIFI_INIT_CONFIG_DEFAULT(); //sets up wifi wifi_init_config struct with default values
	esp_wifi_init(&wifi_initiation);
	esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler, NULL); //register wifi events
	esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event_handler, NULL); //register GOT IP
	wifi_config_t wifi_config = {
		.sta={
			.ssid = CONFIG_WIFI_SSID,
			.password = CONFIG_WIFI_PASSWORD
		}
	};
}
