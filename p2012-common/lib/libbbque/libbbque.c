#define LOG_TAG "libbbque"

#include <cutils/logger.h>
#include <cutils/log.h>
#include "libbbque.h"

extern int bbq_send_message_to_rtrm(char *c) {
	LOGI("%s - Called bbq_send_message_to_rtrm with message: %s", LOG_TAG, c);
	return 0;
}

extern int bbq_send_message_to_app(char *c) {
	LOGI("%s - Called bbq_send_message_to_app with message: %s", LOG_TAG, c);
	return 0;
}
