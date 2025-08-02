idf_component_register(
	SRCS
		"gong.c"
		"server/server.c"
		"server/wifi_connection.c"
		"events/events.c"

    PRIV_REQUIRES
		esp_http_server
		esp_netif
		esp_wifi
		esp_https_server
		nvs_flash
    INCLUDE_DIRS
		"."
)
