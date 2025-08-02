#ifndef CONTROLS_H
#define CONTROLS_H

#include "../libs.h"

void	  init_onboard_led(void);
esp_err_t toggle_onboard_led_handler(httpd_req_t *req);

#endif
