#define LOG_TAG "RTLib"

#include <cutils/logger.h>
#include <cutils/log.h>
#include "rtlib.h"

extern int bbq_send_message_to_rtrm(char *c) {
	LOGI("%s - Called bbq_send_message_to_rtrm.",LOG_TAG);
	return 0;
}

extern int bbq_send_message_to_app(char *c) {
	LOGI("%s - Called bbq_send_message_to_app.",LOG_TAG);
	return 0;
}
