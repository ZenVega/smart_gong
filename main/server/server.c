#include "../events/events.h"
#include "../libs.h"
#include "esp_http_server.h"

#include "libs.h"

esp_err_t root_get_handler(httpd_req_t *req)
{
	const char *html = "<!DOCTYPE html><html><body><h1>Hello from ESP32!</h1></body></html>";
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
	}
	printf("Server running on %s\n", CONFIG_WIFI_STATIC_IP);
	return server;
}
