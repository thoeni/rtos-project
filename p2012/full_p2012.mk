$(call inherit-product, $(SRC_TARGET_DIR)/product/languages_small.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/generic.mk)

#if I wanted a full environment I should've used the following:
#$(call inherit-product, $(SRC_TARGET_DIR)/product/languages_full.mk)
#$(call inherit-product, $(SRC_TARGET_DIR)/product/full.mk)

# Discard inherited values and use our own instead.
PRODUCT_NAME := full_bosp_p2012
PRODUCT_DEVICE := p2012
PRODUCT_MODEL := Full BBQUE P2012 Image for Emulator

#PRODUCT_COPY_FILES += \
#$(MY_PATH)/list/sources.lst:/root/data/myfiles/list/sources.lst \
#$(MY_PATH)/list/sinks.lst:/root/data/myfiles/list/sinks.lst \
#$(MY_PATH)/policy/Policy.xml:/root/data/myfiles/policy/Policy.xml

# Include the common definition and packages
include $(LOCAL_PATH)/../p2012-common/bosp_p2012.mk
PRODUCT_PACKAGES += MrknLogServiceClient

include $(call all-makefiles-under,$(LOCAL_PATH))
