#include <windows.h>
#include "utils.h"

LPSTR lpszSlotName = "\\\\.\\mailslot\\sample_mailslot";

int main(void)
{
    HANDLE hMailslot;
    BOOL bRet;
    DWORD cbWritten, dwRet;
    LPSTR lpszBuffer = "Testing Mailslot";

    /* Open Mailslot */
    hMailslot = CreateFile(
        lpszSlotName,
        GENERIC_WRITE,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    DIE(hMailslot == INVALID_HANDLE_VALUE, "CreateFile");

    /* Send message */
    bRet = WriteFile(
        hMailslot,
        lpszBuffer,
        (DWORD) lstrlen(lpszBuffer) + 1,
        &cbWritten,
        NULL);
    DIE(bRet == FALSE, "Write file to Mailslot");

    printf("Message successfully send\n");

    /* Close Mailslot */
    dwRet = CloseHandle(hMailslot);
    DIE (dwRet == FALSE, "CloseHandle");

    return 0;
}
