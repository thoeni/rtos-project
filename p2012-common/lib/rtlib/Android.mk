LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := rtlib.c
LOCAL_SHARED_LIBRARIES := libcutils libutils libc
LOCAL_MODULE := rtlib
LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)
