#include "../controls/controls.h"
#include "../events/events.h"
#include "../libs.h"
#include "esp_http_server.h"

#include "libs.h"

esp_err_t root_get_handler(httpd_req_t *req)
{
	const char *html = "<!DOCTYPE html><html><head><title>ESP32 LED</title><script>function toggleLED() {fetch('/toggle_led').then(response => response.text()).then(data => alert(data));}</script></head><body><h1>ESP32 LED Control</h1><button onclick='toggleLED()'>Toggle LED</button></body></html>";
	httpd_resp_send(req, html, HTTPD_RESP_USE_STRLEN);
	return ESP_OK;
}

httpd_handle_t start_webserver(void)
{
	httpd_config_t config = HTTPD_DEFAULT_CONFIG();
	httpd_handle_t server = NULL;

	esp_event_handler_register(ESP_HTTPS_SERVER_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL);
	if (httpd_start(&server, &config) == ESP_OK)
	{
		httpd_uri_t uri_get =
			{
				.uri	  = "/",
				.method	  = HTTP_GET,
				.handler  = root_get_handler,
				.user_ctx = NULL};
		httpd_register_uri_handler(server, &uri_get);
		httpd_uri_t toggle_onboard_led_uri =
			{
				.uri	  = "/toggle_led",
				.method	  = HTTP_GET,
				.handler  = toggle_onboard_led_handler,
				.user_ctx = NULL};
		httpd_register_uri_handler(server, &toggle_onboard_led_uri);
	}
	printf("Server running on %s\n", CONFIG_WIFI_STATIC_IP);
	return server;
}
