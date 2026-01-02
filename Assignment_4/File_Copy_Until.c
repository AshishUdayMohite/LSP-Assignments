/*
File Copy Until

Problem Statement :
-> Write a Program that copies the contents of one file into another

Input :
-> Source file name and destination file name as command-line arguments.

Op :
-> Destination file containing an exact copy of source file

*/

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define BLOCK_SIZE 1024 
#define ALL_PERMISSION 0777 

//Funtion Decleration

int main()
{
    void CopyFileUntil(int fd_Src, int fd_Dest);
    char cS_file[256];
    char cD_file[256];
    
    int fdSrc = 0,fdDest = 0;

    printf("Enter Source file name : ");
    scanf("%255s",cS_file);

    printf("Enter Destination file name :");
    scanf("%255s",cD_file);

    //printf("%s\n%s\n",cS_file,cD_file);
    

    fdSrc=open(cS_file,O_RDONLY);

    if(fdSrc == -1)
    {
        printf("Source Error : %s\n",strerror(errno));
        return -1;
    }

    fdDest=open(cD_file,O_WRONLY);

    if(fdDest==-1)
    {
        printf("Destination Error : %s\n",strerror(errno));

        fdDest = creat(cD_file, ALL_PERMISSION);

        if(fdDest==-1)
        {
            printf("Error : %s",strerror(errno));
        }
        else
        {
            printf("File Created\n");
        }
    }

    

    CopyFileUntil(fdSrc,fdDest);

    close(fdSrc);
    close(fdDest);

    return 0;
}

void CopyFileUntil(int fd_Src, int fd_Dest)
{
    //printf("%s ->> %s\n",fileName,destName);
    int iReadByteCount=0;
    int iWriteByteCount=0;
    char cData[BLOCK_SIZE];

    while ((iReadByteCount = read(fd_Src, cData, BLOCK_SIZE)) != 0)
    {
        iWriteByteCount = write(fd_Dest, cData, iReadByteCount);

        if (iWriteByteCount == -1)
        {
            printf("Error : %s\n", strerror(errno));
        }
        else
        {
            printf("Success\n");
        }
    }
}