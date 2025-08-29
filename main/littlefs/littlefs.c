// https://docs.espressif.com/projects/esp-idf/en/v5.0/esp32/api-reference/storage/spiffs.html#_CPPv423esp_vfs_spiffs_registerPK21esp_vfs_spiffs_conf_t

#include "../libs.h"
#include "esp_littlefs.h"

static const char *TAG = "Filesystem";

void init_littlefs(void)
{
	esp_vfs_littlefs_conf_t conf = {
		.base_path				= "/storage",
		.partition_label		= "storage",
		.format_if_mount_failed = false,
		.read_only				= true,
	};

	esp_err_t ret = esp_vfs_littlefs_register(&conf);
	if (ret != ESP_OK)
	{
		if (ret == ESP_FAIL)
		{
			ESP_LOGE(TAG, "Failed to mount or format filesystem");
		}
		else if (ret == ESP_ERR_NOT_FOUND)
		{
			ESP_LOGE(TAG, "Failed to find LittleFS partition");
		}
		else
		{
			ESP_LOGE(TAG, "Failed to initialize LittleFS (%s)", esp_err_to_name(ret));
		}
		return;
	}

	size_t total = 0, used = 0;
	ret = esp_littlefs_info(conf.partition_label, &total, &used);
	if (ret != ESP_OK)
	{
		ESP_LOGE(TAG, "Failed to get LittleFS partition information (%s)", esp_err_to_name(ret));
		esp_littlefs_format(conf.partition_label);
	}
	else
		ESP_LOGI(TAG, "\n\nPARTITION SIZE: total: %d, used: %d\n\n", total, used);
}
