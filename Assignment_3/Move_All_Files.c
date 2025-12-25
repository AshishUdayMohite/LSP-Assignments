#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

int CopyFile(const char *src, const char *dest)
{
    int fdSrc, fdDest;
    char buffer[BUFFER_SIZE];
    ssize_t bytes;

    fdSrc = open(src, O_RDONLY);
    if (fdSrc < 0)
        return -1;

    fdDest = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fdDest < 0)
    {
        close(fdSrc);
        return -1;
    }

    while ((bytes = read(fdSrc, buffer, BUFFER_SIZE)) > 0)
    {
        write(fdDest, buffer, bytes);
    }

    close(fdSrc);
    close(fdDest);

    return 0;
}

int main()
{
    char srcDir[256], destDir[256];
    DIR *dp;
    struct dirent *entry;
    struct stat sbSrc, sbFile;
    int count = 0;

    printf("Enter Source Directory : ");
    scanf("%s", srcDir);

    printf("Enter Destination Directory : ");
    scanf("%s", destDir);

    dp = opendir(srcDir);
    if (dp == NULL)
    {
        perror("Unable to open source directory");
        return -1;
    }

    stat(srcDir, &sbSrc);

    while ((entry = readdir(dp)) != NULL)
    {
        char srcPath[512], destPath[512];

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(srcPath, sizeof(srcPath), "%s/%s", srcDir, entry->d_name);
        snprintf(destPath, sizeof(destPath), "%s/%s", destDir, entry->d_name);

        if (stat(srcPath, &sbFile) == -1)
            continue;

        
        if (S_ISREG(sbFile.st_mode))
        {
            if (rename(srcPath, destPath) == 0)
            {
                count++;
            }
            else
            {
                if (errno == EXDEV)
                {
                    if (CopyFile(srcPath, destPath) == 0)
                    {
                        unlink(srcPath);
                        count++;
                    }
                }
            }
        }
    }

    closedir(dp);

    printf("Total files moved: %d\n", count);

    return 0;
}
