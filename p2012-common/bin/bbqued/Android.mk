LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := bbqued.c
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../lib/libbbque/
LOCAL_SHARED_LIBRARIES := libbbque libcutils
LOCAL_MODULE := bbqued
include $(BUILD_EXECUTABLE)
