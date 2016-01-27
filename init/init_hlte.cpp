/*
 * Copyright 2016, The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

#include "init_msm.h"

/* Serial number */
#define SERIAL_FILE "/efs/FactoryApp/serial_no"
#define SERIAL_PROP "ro.serialno"
#define SERIAL_OFFSET 0x00
#define SERIAL_LENGTH 11

static int read_file(const char *fname, char *data, int max_size)
{
    int fd, rc;

    if (max_size < 1)
        return 0;

    fd = open(fname, O_RDONLY);
    if (fd < 0) {
        ERROR("failed to open '%s'\n", fname);
        return 0;
    }

    rc = read(fd, data, max_size -1);
    if ((rc > 0) && (rc < max_size ))
        data[rc] = '\0';
    else
        data[0] = '\0';
    close(fd);

    return 1;
}

static void get_serial()
{
    int ret = 0;
    char const *path = SERIAL_FILE;
    char buf[SERIAL_LENGTH + 1];
    prop_info *pi;

    if(read_file(path, buf, sizeof(buf))) {

        if (strlen(buf) > 0) {
            pi = (prop_info*) __system_property_find(SERIAL_PROP);
            if(pi)
                ret = __system_property_update(pi, buf,
                        strlen(buf));
            else
                ret = __system_property_add(SERIAL_PROP,
                        strlen(SERIAL_PROP),
                        buf, strlen(buf));
        }
    }
}

void gsm_properties()
{
    property_set("ro.telephony.default_network", "9");
    property_set("telephony.lteOnGsmDevice", "1");
}

void init_msm_properties(unsigned long msm_id, unsigned long msm_ver, char *board_type)
{
    char platform[PROP_VALUE_MAX];
    char bootloader[PROP_VALUE_MAX];
    char device[PROP_VALUE_MAX];
    char devicename[PROP_VALUE_MAX];
    int rc;

    UNUSED(msm_id);
    UNUSED(msm_ver);
    UNUSED(board_type);

    rc = property_get("ro.board.platform", platform);
    if (!rc || !ISMATCH(platform, ANDROID_TARGET))
        return;

    property_get("ro.bootloader", bootloader);

    if (strstr(bootloader, "N900S")) {
        /* hlteskt */
        property_set("ro.build.fingerprint", "samsung/hlteskt/hlteskt:5.0/LRX21V/N900SKSU0GOJ2:user/release-keys");
        property_set("ro.build.description", "hlteskt-user 5.0 LRX21V N900SKSU0GOJ2 release-keys");
        property_set("ro.product.model", "SM-N900S");
        property_set("ro.product.name", "hlteskt");
        property_set("ro.product.device", "hlteskt");
    } else if (strstr(bootloader, "N900K")) {
        /* hltektt */
        property_set("ro.build.fingerprint", "samsung/hltektt/hltektt:5.0/LRX21V/N900KKKU0GOF2:user/release-keys");
        property_set("ro.build.description", "hltektt-user 5.0 LRX21V N900KKKU0GOF2 release-keys");
        property_set("ro.product.model", "SM-N900K");
        property_set("ro.product.name", "hltektt");
        property_set("ro.product.device", "hltektt");
    } else if (strstr(bootloader, "N900W8")) {
        /* hltecan */
        if (strstr(bootloader, "N900W8UB")) {
            /* hltecan/ub */
            property_set("ro.build.fingerprint", "samsung/hlteub/hltecan:5.0/LRX21V/N900W8UBU2DOI2:user/release-keys");
            property_set("ro.build.description", "hlteub-user 5.0 LRX21V N900W8UBU2DOI2 release-keys");
            property_set("ro.product.name", "hlteub");
        } else {
            /* hltecan/vl */
            property_set("ro.build.fingerprint", "samsung/hltevl/hltecan:5.0/LRX21V/N900W8VLU2DOH1:user/release-keys");
            property_set("ro.build.description", "hltevl-user 5.0 LRX21V N900W8VLU2DOH1 release-keys");
            property_set("ro.product.name", "hltevl");
        }
        property_set("ro.product.model", "SM-N900W8");
        property_set("ro.product.device", "hltecan");
    } else if (strstr(bootloader, "N900T")) {
        /* hltetmo */
        property_set("ro.build.fingerprint", "samsung/hltetmo/hltetmo:5.0/LRX21V/N900TUVUFOB6:user/release-keys");
        property_set("ro.build.description", "hltetmo-user 5.0 LRX21V N900TUVUFOB6 release-keys");
        property_set("ro.product.model", "SM-N900T");
        property_set("ro.product.name", "hltetmo");
        property_set("ro.product.device", "hltetmo");
    } else {
        /* hltexx */
        property_set("ro.build.fingerprint", "samsung/hltexx/hlte:5.0/LRX21V/N9005XXUGBOK6:user/release-keys");
        property_set("ro.build.description", "hltexx-user 5.0 LRX21V N9005XXUGBOK6 release-keys");
        property_set("ro.product.name", "hltexx");
        property_set("ro.product.model", "SM-N9005");
        property_set("ro.product.device", "hltexx");
    }
    
    get_serial();
    property_get("ro.product.device", device);
    strlcpy(devicename, device, sizeof(devicename));
    ERROR("Found bootloader id %s setting build properties for %s device\n", bootloader, devicename);
}
