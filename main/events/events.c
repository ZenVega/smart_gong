#include "events.h"
#include "../CONSTANTS.h"
#include "../libs.h"
#include "esp_event.h" //for wifi event

int retry_num = 0;

// event handler for wifi events, basically logging the wifi connection
void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
	switch (event_id)
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
		if (retry_num < MAX_RETRY)
		{
			esp_wifi_connect();
			retry_num++;
			printf("Retrying to Connect...\n");
		}
		break;
	}
	case IP_EVENT_STA_GOT_IP:
	{
		ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
		printf("IP Address: " IPSTR "\n", IP2STR(&event->ip_info.ip));
		printf("Subnet Mask: " IPSTR "\n", IP2STR(&event->ip_info.netmask));
		printf("Gateway (Router): " IPSTR "\n", IP2STR(&event->ip_info.gw));
		break;
	}
	default:
	{
		printf("WIFI UNKNOWN EVENT\n");
	}
	}
}
