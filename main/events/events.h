#ifndef EVENTS_H
#define EVENTS_H

#include "esp_event.h" //for wifi event
					   //
void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data);
#endif
