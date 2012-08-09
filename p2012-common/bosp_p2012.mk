MY_COMMON_PATH := $(LOCAL_PATH)/../p2012-common/

# Copy our init.rc file over the existing one (since ours contains extra changes)
PRODUCT_COPY_FILES += $(MY_COMMON_PATH)/init.rc:root/init.rc

#MARAKANA EXAMPLE PACKAGES
PRODUCT_PACKAGES += libmrknlog
PRODUCT_PACKAGES += mrknlogd
PRODUCT_PACKAGES += \
        com.marakana.android.lib.log \
        com.marakana.android.lib.log.xml \
        libmrknlog_jni
PRODUCT_PACKAGES += \
        com.marakana.android.service.log \
        com.marakana.android.service.log.xml
PRODUCT_PACKAGES += MrknLogService

#BOSP EXAMPLE PACKAGES
