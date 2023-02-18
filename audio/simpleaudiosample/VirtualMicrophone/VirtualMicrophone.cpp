#include "pch.h"
#include "Public.h"
#include <Windows.h>
#include <stdio.h>
#include "Cfgmgr32.h"

int main(array<System::String ^> ^args)
{
    printf("VirtualMicrophone\n");

    HANDLE hFile = NULL;
    char szTemp[256] = { 0 };
    DWORD dwReturn;
    DWORD err;
    
    CONFIGRET cr = CR_SUCCESS;
    PWSTR DeviceInterfaceList = NULL;
    ULONG DeviceInterfaceListLength = 0;

    do {
        cr = CM_Get_Device_Interface_List_Size(&DeviceInterfaceListLength,
            (LPGUID)&GUID_DEVINTERFACE_VIRTUAL_MIC_IO,
            NULL,
            CM_GET_DEVICE_INTERFACE_LIST_ALL_DEVICES);

        if (cr != CR_SUCCESS)
        {
            break;
        }

        if (DeviceInterfaceList != NULL) {
            HeapFree(GetProcessHeap(),
                0,
                DeviceInterfaceList);
        }

        DeviceInterfaceList = (PWSTR)HeapAlloc(GetProcessHeap(),
            HEAP_ZERO_MEMORY,
            DeviceInterfaceListLength * sizeof(WCHAR));

        if (DeviceInterfaceList == NULL)
        {
            cr = CR_OUT_OF_MEMORY;
            break;
        }

        cr = CM_Get_Device_Interface_List((LPGUID)&GUID_DEVINTERFACE_VIRTUAL_MIC_IO,
            NULL,
            DeviceInterfaceList,
            DeviceInterfaceListLength,
            CM_GET_DEVICE_INTERFACE_LIST_ALL_DEVICES);
    } while (cr == CR_BUFFER_SMALL);

    if (cr != CR_SUCCESS)
    {
        err = GetLastError();
        printf("Failed to get device interface. (%d)\n", err);
        return 0;
    }

    PWSTR sz;
    sz = DeviceInterfaceList;
    while (*sz)
    {
        wprintf(L"%ws\n", sz);
        sz += 1 + wcslen(sz);
    }
    
    //   \\??\ROOT#UNKNOWN#0000#{b56ad849-3462-4715-8796-24b05c790bd7}\Wave
    
    hFile = CreateFile(DeviceInterfaceList, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL);
    if (hFile != NULL && hFile != INVALID_HANDLE_VALUE)
    {
        ZeroMemory(szTemp, sizeof(szTemp));
        DeviceIoControl(hFile, IOCTL_VIRTUAL_MIC_IO, "** Hello from User Mode Buffered I/O", sizeof("** Hello from User Mode Buffered I/O"), szTemp, sizeof(szTemp), &dwReturn, NULL);
        printf(szTemp);
        printf("\n");

        CloseHandle(hFile);
    }
    else
    {
        err = GetLastError();
        printf("CreateFile failed. (%d)\n", err);
    }

    return 0;
}
