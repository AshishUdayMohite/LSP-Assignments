/*
Program : Find Largest File in Directory
- Accept Directory name
- Find and print
    - Largest file name
    - Its size
- consider only regular files

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

int iLargestSize = 0;
char cLargestFile[256] = "";

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

    printf("Largest File: %s\n", cLargestFile);
    printf("Size of Largest File: %d bytes\n", iLargestSize);
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
                //printf("Size : %ld bytes\n", sobj.st_size);

                if(sobj.st_size > iLargestSize)
                {
                    iLargestSize = sobj.st_size;
                    strcpy(cLargestFile, ldirent->d_name);
                }
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

