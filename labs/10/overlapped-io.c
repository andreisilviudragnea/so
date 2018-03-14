#include "utils.h"
#include <stdlib.h>
#include <windows.h>

#define BUF_SIZE	(1024 * 1024) /* 1MB */

int main(int argc, char **argv)
{
    /* Make sure overlapped structure is clean */
    OVERLAPPED ov;
    ZeroMemory(&ov, sizeof(ov));

    /* Create manual-reset event */
    HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    DIE(hEvent == INVALID_HANDLE_VALUE, "CreateEvent");

    ov.hEvent = hEvent;

    HANDLE hFile = CreateFile(argv[1],
                       GENERIC_READ,	/* access mode */
                       FILE_SHARE_READ,	/* sharing option */
                       NULL,		/* security attributes */
                       OPEN_EXISTING,	/* open only if it exists */
                       FILE_FLAG_OVERLAPPED,/* file attributes */
                       NULL);		/* no template */
    DIE(hFile == INVALID_HANDLE_VALUE, "CreateFile");

    DWORD dwBytesRead;

    char *buffer = malloc(BUF_SIZE * sizeof(*buffer));
    DIE(buffer == NULL, "malloc");

    BOOL dwRet = ReadFile(hFile, buffer, BUF_SIZE, &dwBytesRead, &ov);
    if (dwRet == FALSE) {
        DWORD dwErr = GetLastError();

        switch (dwErr) {
        case ERROR_HANDLE_EOF:
            printf("End of File Reached\n");
            break;

        case ERROR_IO_PENDING:
            /* async io not ready */
            printf("Async IO not finished immediately\n");

            /* do some other work  in the meantime */
            Sleep(1);

            /* Wait for it to finish */
            GetOverlappedResult(ov.hEvent, &ov, &dwBytesRead, TRUE);
            printf("nRead = %ld\n", dwBytesRead);
            break;

        default:
            /* ReadFile failed */
            PrintLastError("ReadFile");
        }
    } else {
        printf("Async IO finished immediately\n");
        printf("nRead = %ld\n", dwBytesRead);
    }

    free(buffer);

    dwRet = CloseHandle(hFile);
    DIE(dwRet == FALSE, "CloseHandle");

    dwRet = CloseHandle(hEvent);
    DIE(dwRet == FALSE, "CloseHandle");

    return 0;
}
