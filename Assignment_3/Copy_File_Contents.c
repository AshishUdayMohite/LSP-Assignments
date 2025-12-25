/*
Program : Copy File Contents ( Sourc to Destination )
- Accept Source file name & Destination file name
- Create Destination if not exists (O_CREAT | O_Trunc)
- Copy using buffer read() Write() loop
- preserve permissions (optional bonus using stat() + chmod() )
*/


#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

void CopyFileContents(char *Sour_File, char *Dest_File);

int main()
{
    char cSour_File[256];
    char cDest_File[256];

    printf("Enter Source File Name : ");
    scanf("%s", cSour_File);

    printf("Enter Destination File Name : ");
    scanf("%s", cDest_File);

    CopyFileContents(cSour_File, cDest_File);
    return 0;
}

//Helper Function
void CopyFileContents(char *Sour_File, char *Dest_File)
{
    int fdSrc, fdDest;
    char buffer[1024];
    int bytes;

    fdSrc = open(Sour_File, O_RDONLY);
    if (fdSrc == -1)
    {
        printf("Source Error: %s\n", strerror(errno));
        return;
    }

    fdDest = open(Dest_File, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fdDest == -1)
    {
        printf("Destination Error: %s\n", strerror(errno));
        close(fdSrc);
        return;
    }

    while ((bytes = read(fdSrc, buffer, sizeof(buffer))) > 0)
    {
        write(fdDest, buffer, bytes);
    }

    printf("File copied successfully\n");

    close(fdSrc);
    close(fdDest);
}
