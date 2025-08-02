#include "esp_event.h"		 //for wifi event
#include "esp_http_server.h" //esp_wifi_init functions and wifi operations
#include "esp_wifi.h"		 //esp_wifi_init functions and wifi operations

int retry_num = 0;

// event handler for wifi events, basically logging the wifi connection
static void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
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
		if (retry_num < 5)
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

void define_fixed_ip_addr(esp_netif_t *netif)
{
	esp_netif_ip_info_t ip_info;

	ip_info.ip.addr		 = esp_ip4addr_aton(CONFIG_WIFI_STATIC_IP);
	ip_info.gw.addr		 = esp_ip4addr_aton(CONFIG_WIFI_GATEWAY);
	ip_info.netmask.addr = esp_ip4addr_aton(CONFIG_WIFI_SN_MASK);
	esp_netif_dhcpc_stop(netif); // Disable DHCP client
	esp_netif_set_ip_info(netif, &ip_info);
}

void wifi_connection(void)
{
	esp_netif_init();										  // Initialize the underlying TCP/IP stack.
	esp_event_loop_create_default();						  // responsible for creating and dispatching events
	esp_netif_t *netif = esp_netif_create_default_wifi_sta(); // creates structs for wifi-station
	define_fixed_ip_addr(netif);							  // disables dhcp and sets static IP

	wifi_init_config_t wifi_initiation = WIFI_INIT_CONFIG_DEFAULT(); // sets up wifi wifi_init_config struct with default values
	esp_wifi_init(&wifi_initiation);
	esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler, NULL);	 // register wifi events
	esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event_handler, NULL); // register GOT IP
																						 //
	wifi_config_t wifi_config = {
		.sta = {
			.ssid	  = CONFIG_WIFI_SSID,
			.password = CONFIG_WIFI_PASSWORD}};
	esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config);
	esp_wifi_start();				  // build wifi engine with configs
	esp_wifi_set_mode(WIFI_MODE_STA); // use station mode
	esp_wifi_connect();				  // connect with ssid and pw
}
