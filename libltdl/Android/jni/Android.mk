LOCAL_PATH := $(call my-dir)

# build the library
include $(CLEAR_VARS)
LOCAL_MODULE := ltdl

LOCAL_SRC_FILES := \
	$(LOCAL_PATH)/../../loaders/dlopen.c \
	$(LOCAL_PATH)/../../loaders/preopen.c \
	$(LOCAL_PATH)/../../lt__alloc.c \
	$(LOCAL_PATH)/../../lt__argz.c \
	$(LOCAL_PATH)/../../lt__dirent.c \
	$(LOCAL_PATH)/../../lt__strl.c \
	$(LOCAL_PATH)/../../lt_dlloader.c \
	$(LOCAL_PATH)/../../lt_error.c \
	$(LOCAL_PATH)/../../ltdl.c \
	$(LOCAL_PATH)/../../slist.c

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../.. \
	$(LOCAL_PATH)/../../libltdl

LOCAL_CFLAGS := -DHAVE_CONFIG_H -DHAVE_LIBDL -W -Wall -O3 -fPIC -DPIC -DLTDL #-DSTDC_HEADERS
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -ldl

include $(BUILD_SHARED_LIBRARY)
