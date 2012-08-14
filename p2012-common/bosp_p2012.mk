MY_COMMON_PATH := $(LOCAL_PATH)/../p2012-common/

# Copy our init.rc file over the existing one (since ours contains extra changes)
PRODUCT_COPY_FILES += $(MY_COMMON_PATH)/init.rc:root/init.rc

#BOSP PACKAGES
PRODUCT_PACKAGES += libbbque
PRODUCT_PACKAGES += bbclient
PRODUCT_PACKAGES += bbqued
PRODUCT_PACKAGES += \
        com.bbque.android.lib \
        com.bbque.android.lib.xml \
        libbbque_jni
PRODUCT_PACKAGES += \
        com.bbque.android.service \
        com.bbque.android.service.xml
PRODUCT_PACKAGES += BbqueService
