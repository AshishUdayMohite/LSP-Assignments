#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

int main()
{
    char dirName[256];
    DIR *dp;
    struct dirent *entry;
    struct stat sb;
    int count = 0;

    printf("Enter Directory Name : ");
    scanf("%s", dirName);

    dp = opendir(dirName);
    if (dp == NULL)
    {
        perror("Unable to open directory");
        return -1;
    }

    while ((entry = readdir(dp)) != NULL)
    {
        char filePath[512];

        
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(filePath, sizeof(filePath),
                 "%s/%s", dirName, entry->d_name);

        if (stat(filePath, &sb) == -1)
            continue;

        /
        if (S_ISREG(sb.st_mode) && sb.st_size == 0)
        {
            if (unlink(filePath) == 0)
            {
                printf("Deleted: %s\n", entry->d_name);
                count++;
            }
            else
            {
                perror("Delete failed");
            }
        }
    }

    closedir(dp);

    printf("\nTotal empty files deleted: %d\n", count);

    return 0;
}
