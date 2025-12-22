/*
Program : Open File
- Accept File Name from user and open it using open()
- print : success message + returned file descriptor
- Handle error using perror()

*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>

int main()
{
    int fd = 0;
    char Arr[10];

    printf("Enter File Name : ");
    scanf("%s",Arr);

    fd = open(Arr,O_RDWR);

    if(fd == -1)
    {
        perror("Could Not open file");    
        return -1;
    }
    else
    {
        printf("File gets succesfully opened with fd : %d\n",fd);
    }

    return 0;
}
