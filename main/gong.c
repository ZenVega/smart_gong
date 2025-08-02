#include "CONSTANTS.h"
#include "server/server.h"

void app_main(void)
{
	nvs_flash_init(); // inits Non-volatile storage (NVS) - used to store wifi configs
	wifi_connection();
	vTaskDelay(pdMS_TO_TICKS(5000));

	start_webserver();
}
