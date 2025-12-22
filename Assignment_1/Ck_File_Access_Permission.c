/*
Program : Check File Access Permission
- Accept File Name and mode (Read, WRite, Execute)
- Use access() to check permission for current process.
- print "Access / Not Accessible" with reason.

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

    printf("Enter File Mode (Read -> R, Write -> W, Execute -> E ): ");
    scanf("%s", Mode);

    
    if(strcmp(Mode, "R") == 0)
    {
        fd = access(Arr, R_OK);             //Read Permission
    }
    else if(strcmp(Mode, "W") == 0)
    {
        fd = access(Arr, W_OK);             //Write Permission
    }
    else if(strcmp(Mode, "E") == 0)
    {
        fd = access(Arr, X_OK);             //Execute permission
    }
    else
    {
        printf("Invalid File Mode\n");
        return -1;
    }
    

    if(fd == -1)
    {
        printf("Not Accessible : %s\n",strerror(errno));
        return -1;
    }
    printf("Accessible : %s\n",strerror(errno));


    return 0;
}
