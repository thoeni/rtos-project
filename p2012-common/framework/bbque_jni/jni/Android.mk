LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := com_bbque_android_lib_LibBbque.c
LOCAL_C_INCLUDES += $(JNI_H_INCLUDE) $(LOCAL_PATH)/../../../lib/libbbque
LOCAL_SHARED_LIBRARIES := libbbque
LOCAL_MODULE := libbbque_jni
include $(BUILD_SHARED_LIBRARY)
