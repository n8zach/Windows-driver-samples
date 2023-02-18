#pragma once

#include "guiddef.h"
#include "initguid.h"

/*++

Module Name:

    public.h

Abstract:

    This module contains the common declarations shared by driver
    and user applications.

Environment:

    user and kernel

--*/


#define IOCTL_VIRTUAL_MIC_IO     CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_BUFFERED, FILE_READ_DATA | FILE_WRITE_DATA)

//
// Define an Interface Guid so that apps can find the device and talk to it.
//
DEFINE_GUID(GUID_DEVINTERFACE_VIRTUAL_MIC_IO,
    0xb56ad849, 0x3462, 0x4715, 0x87, 0x96, 0x24, 0xb0, 0x5c, 0x79, 0x0b, 0xd7);
// {b56ad849-3462-4715-8796-24b05c790bd7}
