#include <Windows.h>
#include "utils.h"

#define BUF_SIZE 256
LPSTR szMapName = "MyFileMappingObject";

int main(void)
{
    HANDLE hMapFile;
    LPVOID lpMapAddress;
    BOOL bRet;

    hMapFile = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,                 /* read/write access */
        FALSE,                               /* do not inherit the name */
        szMapName);                          /* name of mapping object */
    DIE(hMapFile == NULL, "CreateFileMapping");

    lpMapAddress = MapViewOfFile(
        hMapFile,        /* handle to map object */
        FILE_MAP_ALL_ACCESS,    /* read/write permission */
        0,            /* offset (high-order) */
        0,            /* offset (low-order) */
        0);
    DIE(lpMapAddress == NULL, "MapViewOfFile");

    printf("Message in shm is: <%s>\n", (char *) lpMapAddress);
    fflush(stdout);

    bRet = UnmapViewOfFile(lpMapAddress);
    DIE(bRet == FALSE, "UnmapViewOfFile");

    bRet = CloseHandle(hMapFile);
    DIE(bRet == FALSE, "CloseHandle");

    return 0;
}
