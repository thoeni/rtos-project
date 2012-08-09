LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := skclient.c
LOCAL_SHARED_LIBRARIES := libcutils
LOCAL_MODULE := skclient
include $(BUILD_EXECUTABLE)
