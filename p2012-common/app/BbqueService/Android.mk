LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := $(call all-java-files-under,src)
LOCAL_REQUIRED_MODULES := \
	com.bbque.android.service \
	com.bbque.android.lib
LOCAL_JAVA_LIBRARIES := \
	com.bbque.android.service \
	com.bbque.android.lib \
	core \
	framework
LOCAL_PACKAGE_NAME := BbqueService
LOCAL_SDK_VERSION := current
LOCAL_PROGUARD_ENABLED := disabled
LOCAL_CERTIFICATE := platform
include $(BUILD_PACKAGE)
