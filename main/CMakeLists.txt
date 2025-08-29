idf_component_register(
	SRCS
		"gong.c"
		"server/server.c"
		"server/wifi_connection.c"
		"events/events.c"
		"littlefs/littlefs.c"
		"controls/main.c"

    PRIV_REQUIRES
		esp_http_server
		esp_netif
		esp_wifi
		esp_https_server
		nvs_flash
		esp_driver_ledc
		esp_driver_gpio
		vfs
    REQUIRES
		littlefs
    INCLUDE_DIRS
		"."
)

littlefs_create_partition_image(storage ../partition FLASH_IN_PROJECT)
