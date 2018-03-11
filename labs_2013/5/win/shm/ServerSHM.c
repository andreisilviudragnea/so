#include <Windows.h>
#include "utils.h"

#define BUF_SIZE 256
LPSTR szMapName = "MyFileMappingObject";
LPSTR szMsg = "Testing shared memory on windows";


int main(void)
{
    HANDLE hMapFile;
    LPVOID lpMapAddress;
    BOOL bRet;

    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,         /* use swap, not a particular file */
        NULL,                      /* default security */
        PAGE_READWRITE,                  /* read/write access */
        0,                          /* maximum object size (high-order DWORD) */
        1024,                      /* maximum object size (low-order DWORD) */
        szMapName);                  /* name of mapping object */
    DIE(hMapFile == NULL, "CreateFileMapping");

    lpMapAddress = MapViewOfFile(
        hMapFile,          /* handle to map object */
        FILE_MAP_ALL_ACCESS,  /* read/write permission */
        0,              /* offset (high-order) */
        0,              /* offset (low-order) */
        0);
    DIE(lpMapAddress == NULL, "MapViewOfFile");

    ZeroMemory(lpMapAddress, strlen(szMsg) + 1);
    CopyMemory(lpMapAddress, szMsg, strlen(szMsg));

    Sleep(5000);

    bRet = UnmapViewOfFile(lpMapAddress);
    DIE(bRet == FALSE, "UnmapViewOfFile");

    bRet = CloseHandle(hMapFile);
    DIE(bRet == FALSE, "CloseHandle");

    return 0;
}
