LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := bbqued.c
LOCAL_SHARED_LIBRARIES := libcutils
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog 
LOCAL_MODULE := bbqued
include $(BUILD_EXECUTABLE)
