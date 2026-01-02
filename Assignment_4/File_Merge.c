/*
File Merge Utility

Problem Statement :
-> Merge multiple input files into single output file.

Input :
-> out_put_file file1 file2 file3

Op :
-> Combined file content in order.

*/

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define BLOCK_SIZE 1024 
#define ALL_PERMISSION 0777 

//Funtion Decleration

int main(int argc, char *argv[])
{
    void writeData(int fd_Src , int fd_Dest);
    char cD_file[256];  
    char cS_file[256];  
    int i = 0;
    int fdSrc = 0,fdDest = 0,iOffset = 0 ;

    if(argc<3)
    {
        printf("Please give Proper Command Line Arguments \n");
        printf("Command : ExeName Output_file  file 1 file2 file3 ...\n");
        return 0;
    }

    printf("Combined Files into : %s\n",argv[1]);
    

    fdDest=open(argv[1],O_WRONLY);

    if(fdDest==-1)
    {
        printf("Open File Error : %s\n",strerror(errno));

        fdDest = creat(argv[1], ALL_PERMISSION);

        if(fdDest==-1)
        {
            printf("Error : %s",strerror(errno));
        }
        else
        {
            printf("File Created\n");
        }
    }


    for(i=2;i<argc;i++)
    {
        fdSrc=0;
        printf("%s\n",argv[i]);
        printf("i : %d\n",i);

        fdSrc=open(argv[i],O_RDONLY);

        if(fdSrc ==-1)
        {
            printf("%s File error : %s \n",argv[i],strerror(errno));
            continue;    //if File does not exist then continue to next File.
        }
        writeData(fdSrc,fdDest);

        close(fdSrc);        
    }



    return 0;
}

void writeData(int fd_Src , int fd_Dest)
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

