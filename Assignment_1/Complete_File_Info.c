/*
Program : Display Complete File Information
- Accept File Name and Display file metadat using stat()
- Size , iNode , Permission, Hard Link, Owner Uid/gid, File Type, last access/modify time

*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include <sys/stat.h>

int main()
{
    struct stat sobj;
    char Arr[50];

    printf("Enter File Name : ");
    scanf("%s", Arr);

    if(stat(Arr, &sobj) == -1)
    {
        perror("Stat failed");
        return -1;
    }
    printf("File : %s\n",Arr);
    printf("-------------------------\n");
    printf("File Size               : %ld\n", sobj.st_size);
    printf("Inode No                : %ld\n", sobj.st_ino);
    printf("Permissions             : %o\n", sobj.st_mode);
    printf("Hard Link               : \t%ld\n", sobj.st_nlink);
    printf("Owner uid               : \t\t%d\n", sobj.st_uid);
    printf("Owner gid               : \t%d\n", sobj.st_gid);
    printf("Last modify time        : %ld\n", sobj.st_mtime);
    printf("Last Status Change time : %ld\n", sobj.st_ctime);


    return 0;
}