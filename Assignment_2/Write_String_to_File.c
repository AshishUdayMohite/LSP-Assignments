/*
Program : Write String to File
- Accept File name and a string from user 
- write string using write()(sppend mode by default).
- print number of Bytes written

*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>

int main()
{
    int fd;
    char Arr[10];
    char buffer[50];
    ssize_t iCount;

    printf("Enter File Name : ");
    scanf("%9s", Arr);

    printf("Add String to Write : ");
    scanf("%49s", buffer);

    fd = open(Arr, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if(fd < 0)
    {
        printf("Error : %s\n", strerror(errno));
        return -1;
    }

    iCount = write(fd, buffer, strlen(buffer));

    if(iCount == -1)
    {
        perror("write");
    }
    else
    {
        printf("%ld bytes written successfully\n", iCount);
    }

    close(fd);
    return 0;
}