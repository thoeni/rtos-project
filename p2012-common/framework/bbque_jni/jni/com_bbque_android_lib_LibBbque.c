#include <libbbque.h>
#include "com_bbque_android_lib_LibBbque.h"

static void ThrowLibBbqueException(JNIEnv *env, const char *message) {
  jclass class = (*env)->FindClass(env, "com/bbque/android/lib/LibBbqueException");
  if (class) {
    (*env)->ThrowNew(env, class, message);
    (*env)->DeleteLocalRef(env, class);
  }
}

JNIEXPORT jint JNICALL Java_com_bbque_android_lib_LibBbque_getNumCore
  (JNIEnv *env, jclass clazz) {
  jint result = get_core_availability();
  if (result < 0) {
    ThrowLibBbqueException(env, "Failed to get current core number");
  }
  return result;
}

JNIEXPORT jint JNICALL Java_com_bbque_android_lib_LibBbque_getMoreCore
  (JNIEnv *env, jclass clazz) {
  jint result = ask_more_core();
  if (result < 0) {
    ThrowLibBbqueException(env, "Failed to ask for more core");
  }
  return result;
}

JNIEXPORT jint JNICALL Java_com_bbque_android_lib_LibBbque_getLessCore
  (JNIEnv *env, jclass clazz) {
  jint result = ask_less_core();
  if (result < 0) {
    ThrowLibBbqueException(env, "Failed to release a core");
  }
  return result;
}

JNIEXPORT jint JNICALL Java_com_bbque_android_lib_LibBbque_freeCore
  (JNIEnv *env, jclass clazz) {
  jint result = free_core();
  if (result < 0) {
    ThrowLibBbqueException(env, "Failed to free cores");
  }
  return result;
}

JNIEXPORT jint JNICALL Java_com_bbque_android_lib_LibBbque_sendMessageToApp
  (JNIEnv *env, jclass clazz) {
  jint result = send_message_to_app(env, clazz);
  if (result < 0) {
    ThrowLibBbqueException(env, "Failed to send message to App");
  }
  return result;
}
