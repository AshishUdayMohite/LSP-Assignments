#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

int main()
{
    char dirName[256];
    char fileName[256];
    DIR *dp;
    struct dirent *entry;
    int found = 0;
    char fullPath[PATH_MAX];
    char absPath[PATH_MAX];

    printf("Enter Directory Name : ");
    scanf("%255s", dirName);

    printf("Enter File Name : ");
    scanf("%255s", fileName);

    dp = opendir(dirName);
    if (dp == NULL)
    {
        perror("Unable to open directory");
        return 1;
    }

    while ((entry = readdir(dp)) != NULL)
    {
        if (strcmp(entry->d_name, fileName) == 0)
        {
            snprintf(fullPath, sizeof(fullPath), "%s/%s", dirName, fileName);

            if (realpath(fullPath, absPath) != NULL)
            {
                printf("File FOUND!\n");
                printf("Absolute Path: %s\n", absPath);
            }
            else
            {
                perror("realpath error");
            }

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("File NOT found in directory\n");
    }

    closedir(dp);
    return 0;
}
