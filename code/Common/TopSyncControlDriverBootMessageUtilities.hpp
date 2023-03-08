/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $Workfile: TopSyncControlDriverBootMessageUtilities.hpp $
 * $Revision: 3 $
 * $Date: 4/10/07 17:42 $
 */

/**
 * \file ToPSyncControlDriverMessageBootUtilities.hpp
 * This is a utility class for constructing boot control messages.
 */

#ifndef TOPSYNC_CONTROL_DRIVER_BOOT_MESSAGE_UTILITIES_HPP
#define TOPSYNC_CONTROL_DRIVER_BOOT_MESSAGE_UTILITIES_HPP

#include "General.h"
#include "TopSyncControlDriverBootMessages.h"
#include "ToPSyncInterfaceTypes.h"

#include <string>

using namespace Semtech;
using namespace std;

namespace Semtech
{
    class BootMessageUtilities
    {
        public:
            static string* CreateGetToPSyncPartNumberMsg(void);
            static string* CreateSetToPSyncSystemStateMsg(ToPSyncSystemState systemState);
            static string* CreateGetToPSyncSystemStateMsg(void);
            static string* CreateGetEthernetMacAddressMsg(uint8 portNumber);
            static string* CreateGetHardwareVersionMsg(void);
            static string* CreateGetSetsHardwareVersionMsg(void);
            static string* CreateGetSoftwareVersionMsg(void);
            static string* CreateGetSetsSoftwareVersionMsg(void);
            static string* CreateGetAppSoftwareVersionMsg(void);		
            static string* CreateUpgradeFirmwareMsg(const uint32 encryptionKey[]);
			static string* CreateUpgradeFirmwareFifoModeMsg(uint32 fwLen, uint32 fwCrc);
			static string* CreateVerifyUpgradeFirmwareFifoModeMsg(void);
            static string* CreateFirmwareBurstMsg(const uint8* burstData, uint16 burstSize, uint16 burstNumber);
			static string* CreateFirmwareCrcMsg(const uint32 crc);

        private:
            static uint32 mSecurityKey;

    };
}

#endif
