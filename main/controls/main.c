#include "../CONSTANTS.h"
#include "../libs.h"

bool led_state = true;

esp_err_t toggle_onboard_led_handler(httpd_req_t *req)
{
	led_state = !led_state;
	gpio_set_level(ONBOARD_LED, led_state);
	gpio_set_level(RED_LED, led_state);
	const char *resp = led_state ? "LED ON" : "LED OFF";
	printf("Switch %s\n", resp);
	httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
	return ESP_OK;
}

void init_onboard_led(void)
{
	gpio_set_direction(ONBOARD_LED, GPIO_MODE_OUTPUT);
	gpio_set_level(ONBOARD_LED, 0);
	gpio_set_direction(RED_LED, GPIO_MODE_OUTPUT);
	gpio_set_level(RED_LED, 0);
}
