#include "../controls/controls.h"
#include "../events/events.h"
#include "../libs.h"
#include "esp_http_server.h"

#include "libs.h"
#define FILE_PATH_MAX 600

static esp_err_t file_get_handler(httpd_req_t *req)
{
	char filepath[FILE_PATH_MAX];

	if (strcmp(req->uri, "/") == 0)
	{
		snprintf(filepath, sizeof(filepath), "/storage/index.html");
	}
	else
	{
		snprintf(filepath, sizeof(filepath), "/storage%s", req->uri);
	}

	FILE *f = fopen(filepath, "r");
	if (!f)
	{
		ESP_LOGE("HTTP", "Failed to open %s", filepath);
		httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "File not found");
		return ESP_FAIL;
	}

	char   chunk[512];
	size_t read_bytes;
	while ((read_bytes = fread(chunk, 1, sizeof(chunk), f)) > 0)
	{
		httpd_resp_send_chunk(req, chunk, read_bytes);
	}
	fclose(f);

	httpd_resp_send_chunk(req, NULL, 0); // end response
	return ESP_OK;
}

httpd_handle_t start_webserver(void)
{
	httpd_config_t config = HTTPD_DEFAULT_CONFIG();
	httpd_handle_t server = NULL;

	esp_event_handler_register(ESP_HTTPS_SERVER_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL);
	if (httpd_start(&server, &config) == ESP_OK)
	{
		httpd_uri_t root = {
			.uri	  = "/",
			.method	  = HTTP_GET,
			.handler  = file_get_handler,
			.user_ctx = NULL};

		httpd_uri_t css = {
			.uri	  = "/style.css",
			.method	  = HTTP_GET,
			.handler  = file_get_handler,
			.user_ctx = NULL};

		httpd_uri_t js = {
			.uri	  = "/script.js",
			.method	  = HTTP_GET,
			.handler  = file_get_handler,
			.user_ctx = NULL};

		httpd_register_uri_handler(server, &root);
		httpd_register_uri_handler(server, &css);
		httpd_register_uri_handler(server, &js);

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
