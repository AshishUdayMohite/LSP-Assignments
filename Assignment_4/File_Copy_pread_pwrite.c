/*
File Copy Using pread & pwrite

Problem Statement :
-> Copy a file using pread() and pwrite() without changing the file offset.

Input :
-> Source_file destination_file offset.

Op :
-> Copied file identical to source.

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
    void CopyFileUntil(int fd_Src, int fd_Dest, int Offset);
    char cS_file[256];
    char cD_file[256];
    
    int fdSrc = 0,fdDest = 0,iOffset = 0 ;

    printf("Enter Source file name : ");
    scanf("%255s",cS_file);

    printf("Enter Destination file name :");
    scanf("%255s",cD_file);

    printf("Enter Offset :");
    scanf("%d",&iOffset);

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

    

    CopyFileUntil(fdSrc,fdDest,iOffset);

    close(fdSrc);
    close(fdDest);

    return 0;
}

void CopyFileUntil(int fd_Src, int fd_Dest, int Offset)
{
    //printf("%s ->> %s\n",fileName,destName);
    int iReadByteCount=0;
    int iWriteByteCount=0;
    char cData[BLOCK_SIZE];
    // int fd=0;

    // fd = lseek(fd_Src,Offset,SEEK_SET);
    // if(fd==-1)
    // {
    //     printf("Error : %s\n",strerror(errno));
    // }

    iReadByteCount = pread(fd_Src, cData, BLOCK_SIZE,Offset);
    if(iReadByteCount==-1)
    {
        printf("Read Error : %s\n",strerror(errno));
    }

    iWriteByteCount = pwrite(fd_Dest, cData, iReadByteCount,Offset);

    if(iWriteByteCount == -1)
    {
        printf("Error : %s\n",strerror(errno));
    }
    else
    {
        printf("Success\n");
    }

}