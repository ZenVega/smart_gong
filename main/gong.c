#include "CONSTANTS.h"
#include "controls/controls.h"
#include "littlefs/littlefs.h"
#include "server/server.h"

void app_main(void)
{
	nvs_flash_init(); // inits Non-volatile storage (NVS) - used to store wifi configs
	init_littlefs();
	init_onboard_led();
	wifi_connection();
	vTaskDelay(pdMS_TO_TICKS(5000));

	start_webserver();
}
