/*
Program : Open File in Given Mode
- Accept File Name and mode (R,W,RW,A) from user
- Convert mode to flags (O_RDONLY, O_WRONLY,O_RDWR,O_APPEND | O_CREAT).
- Open File accordingly and display fd.

*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

int main()
{
    int fd = 0;
    char Mode[3];     // Can store "R", "W", "RW", "A"
    char Arr[50];

    printf("Enter File Name : ");
    scanf("%s", Arr);

    printf("Enter File Mode (R, W, RW, A): ");
    scanf("%s", Mode);

    if(strcmp(Mode, "R") == 0)
    {
        fd = open(Arr, O_RDONLY);
    }
    else if(strcmp(Mode, "W") == 0)
    {
        fd = open(Arr, O_WRONLY | O_CREAT, 0777);
    }
    else if(strcmp(Mode, "RW") == 0)
    {
        fd = open(Arr, O_RDWR | O_CREAT, 0777);
    }
    else if(strcmp(Mode, "A") == 0)
    {
        fd = open(Arr, O_WRONLY | O_APPEND | O_CREAT, 0777);
    }
    else
    {
        printf("Invalid File Mode\n");
        return -1;
    }

    if(fd == -1)
    {
        perror("Could not open file");
        return -1;
    }

    printf("File opened successfully with fd : %d\n", fd);

    return 0;
}
