/*
Program : List All Files From Directory
- Accept Directory name
- using opendir() / readdir() to print only names (skip . and ..)

*/

// #include<stdio.h>
// #include<unistd.h>
// #include<fcntl.h>
// #include<string.h>
// #include<errno.h>
// #include<sys/types.h>
// #include<dirent.h>
// #include<sys/stat.h>

// #define BORDER printf("-----------------------\n");
// typedef struct dirent DIRENT;



// int main()
// {
//     //Function Decleration 

//     void PrintDirectory_Info(DIRENT *);

//     int fd;
//     char Arr[256];
//     DIR * Current_D;
//     DIRENT * Cur_Dir_Info;

//     printf("Enter Directory Name : ");
//     scanf("%9s", Arr);

//     Current_D =opendir(Arr);

//     if(NULL == Current_D)
//     {
//         printf("Error : %s\n",strerror(errno));
//         return -1;
//     }
//     // printf("Success\n");

//     errno =0;  // Set Errno to Zero Before Calling Readdir

//     // printf("Success\n");

//     while ((Cur_Dir_Info = readdir(Current_D)) != NULL)
//     {
//         PrintDirectory_Info(Cur_Dir_Info);
//     }
//     BORDER

//     return 0;
// }

// //Helper Functions
// void PrintDirectory_Info(DIRENT * ldirent)
// {
    
//     struct stat sobj;
    
//    /* struct dirent 
//    {
//         ino_t          d_ino;       // Inode number 
//         off_t          d_off;       // Not an offset; see below 
//         unsigned short d_reclen;    // Length of this record 
//         unsigned char  d_type;      // Type of file; not supporte by all filesystem types 
//         char           d_name[256]; // Null-terminated filename 
//     };
//     */
//    if(( strcmp(ldirent->d_name,".")) && ( strcmp(ldirent->d_name,"..") ))
//    {
//         BORDER
//         // printf("Inode Number  : %ld\n",ldirent->d_ino);
//         // printf("Offset Number : %ld\n",ldirent->d_off);
//         // printf("Record Length : %d\n",ldirent->d_reclen);
//         // printf("Type of File  : %d\n",ldirent->d_type);
//         printf("File Name     : %s\n",ldirent->d_name);

  
//         if(stat(ldirent->d_name, &sobj)==0)
//         {
//             if (S_ISREG(sobj.st_mode))
//                 printf("Type : Regular File\n");

//             else if (S_ISDIR(sobj.st_mode))
//                 printf("Type : Directory\n");
//             else
//                 printf("Type : Other\n");
//         }
//    }      
// }


/*
Program : List All Files From Directory
- Accept Directory name
- Using opendir() / readdir()
- Print file names (skip . and ..)
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

#define BORDER printf("-----------------------\n");

typedef struct dirent DIRENT;

/* Function Declaration */
void PrintDirectory_Info(char *dirname, DIRENT *);

int main()
{
    char Arr[256];
    DIR *Current_D = NULL;
    DIRENT *Cur_Dir_Info = NULL;

    printf("Enter Directory Name : ");
    scanf("%255s", Arr);

    Current_D = opendir(Arr);
    if (Current_D == NULL)
    {
        printf("Error : %s\n", strerror(errno));
        return -1;
    }

    errno = 0;

    while ((Cur_Dir_Info = readdir(Current_D)) != NULL)
    {
        PrintDirectory_Info(Arr, Cur_Dir_Info);
    }

    BORDER
    closedir(Current_D);

    return 0;
}

/* Helper Function */
void PrintDirectory_Info(char *dirname, DIRENT *ldirent)
{
    struct stat sobj;
    char path[512];

    /* Skip . and .. */
    if (strcmp(ldirent->d_name, ".") != 0 &&
        strcmp(ldirent->d_name, "..") != 0)
    {
        BORDER
        printf("File Name : %s\n", ldirent->d_name);

        /* Create full path */
        snprintf(path, sizeof(path), "%s/%s", dirname, ldirent->d_name);

        if (stat(path, &sobj) == 0)
        {
            if (S_ISREG(sobj.st_mode))
            {
                printf("Type : Regular File\n");
            }
            else if (S_ISDIR(sobj.st_mode))
            {
                printf("Type : Directory\n");
            }
            else
            {
                printf("Type : Other\n");
            }
        }
        else
        {
            perror("stat failed");
        }
    }
}

