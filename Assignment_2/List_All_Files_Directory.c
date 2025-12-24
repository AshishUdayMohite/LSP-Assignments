/*
Program : List All Files From Directory
- Accept Directory name
- using opendir() / readdir() to print only names (skip . and ..)

*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<dirent.h>

#define BORDER printf("-----------------------\n");
typedef struct dirent DIRENT;



int main()
{
    //Function Decleration 

    void PrintDirectory_Info(DIRENT *);

    int fd;
    char Arr[256];
    DIR * Current_D;
    DIRENT * Cur_Dir_Info;

    printf("Enter Directory Name : ");
    scanf("%9s", Arr);

    Current_D =opendir(Arr);

    if(NULL == Current_D)
    {
        printf("Error : %s\n",strerror(errno));
        return -1;
    }
    // printf("Success\n");

    errno =0;  // Set Errno to Zero Before Calling Readdir

    // printf("Success\n");

    while ((Cur_Dir_Info = readdir(Current_D)) != NULL)
    {
        PrintDirectory_Info(Cur_Dir_Info);
    }
    BORDER

    return 0;
}

//Helper Functions
void PrintDirectory_Info(DIRENT * ldirent)
{
   /* struct dirent 
   {
        ino_t          d_ino;       // Inode number 
        off_t          d_off;       // Not an offset; see below 
        unsigned short d_reclen;    // Length of this record 
        unsigned char  d_type;      // Type of file; not supporte by all filesystem types 
        char           d_name[256]; // Null-terminated filename 
    };
    */
   if(( strcmp(ldirent->d_name,".")) && ( strcmp(ldirent->d_name,"..") ))
   {
        BORDER
        // printf("Inode Number  : %ld\n",ldirent->d_ino);
        // printf("Offset Number : %ld\n",ldirent->d_off);
        // printf("Record Length : %d\n",ldirent->d_reclen);
        // printf("Type of File  : %d\n",ldirent->d_type);
        printf("File Name     : %s\n",ldirent->d_name);
        
   }      
}