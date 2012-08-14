LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := libbbque.c
LOCAL_SHARED_LIBRARIES := libcutils libutils libc
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog 
LOCAL_MODULE := libbbque
include $(BUILD_SHARED_LIBRARY)
