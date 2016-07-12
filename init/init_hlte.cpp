/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <stdio.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

#include "init_msm8974.h"

void gsm_properties()
{
    property_set("ro.telephony.default_network", "9");
    property_set("telephony.lteOnGsmDevice", "1");
}

#define ISMATCH(a, b) (!strncmp((a), (b), PROP_VALUE_MAX))

void init_target_properties()
{
    char platform[PROP_VALUE_MAX];
    char bootloader[PROP_VALUE_MAX];
    char device[PROP_VALUE_MAX];
    char devicename[PROP_VALUE_MAX];
    int rc;

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

    property_get("ro.product.device", device);
    strlcpy(devicename, device, sizeof(devicename));
    ERROR("Found bootloader id %s setting build properties for %s device\n", bootloader, devicename);
}
