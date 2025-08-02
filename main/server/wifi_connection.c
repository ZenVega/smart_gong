#include "../CONSTANTS.h"
#include "../events/events.h"
#include "../libs.h"

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
