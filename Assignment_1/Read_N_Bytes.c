/*
Program : Read N Bytes From File
- Accept File Name and number of bytes N
- Read exactly N bytes using read() and print on Console
- If File contains less than N, print only available bytes.

*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>

int main()
{
    int fd = 0;
    char Arr[10];
    char buffer[50];
    int iNo=0;

    printf("Enter File Name : ");
    scanf("%s",Arr);
    
    printf("Enter no of Bytes to Read : ");
    scanf("%d",&iNo);

    fd=open(Arr,O_RDONLY);

    if(fd < 0)
    {
        printf("Error : %s\n",strerror(errno));
        return -1;
    }

    printf ("File Successfully open with fd : %d\n",fd);

    read(fd,buffer,iNo);

    printf("%s\n",buffer);
    close(fd);

    return 0;
}
