#define LOG_TAG "BBQUE Daemon"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <utils/Log.h>
#include <libbbque.h>

int main (int argc, char* argv[]) {
	if (argc != 2) {
    fprintf(stderr, "Usage: %s <resources-assignment-frequency-in-seconds>\n", argv[0]);
    exit(2);
  } else {
    int frequency = atoi(argv[1]);
    int count = 1;
    while(1) {
      if (bbq_send_message_to_app("msg") != 0) {
        LOGI("Sent resource assignment update. Waiting %d seconds before the next check.", frequency);
        count++;
      } else {
        LOGE("Failed to handle assignment. Waiting %d seconds before the next check", frequency);
      }
      sleep(frequency);
    }
  }
}
