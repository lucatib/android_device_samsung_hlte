$(call inherit-product, device/samsung/hlte/full_hlte.mk)

# Enhanced NFC
#$(call inherit-product, vendor/cm/config/nfc_enhanced.mk)

# Inherit some common CM stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

# Custom unofficial build tag
TARGET_UNOFFICIAL_BUILD_ID := lt

PRODUCT_DEVICE := hltexx
PRODUCT_NAME := cm_hlte
