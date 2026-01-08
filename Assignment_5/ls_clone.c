#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>   
#include <unistd.h>
#include <string.h>
#include <errno.h>


void ls_clone(const char *dirpath, DIR *dirp);
void print_permissions(mode_t mode);

int main()
{
    char cPath[256];
    DIR * dp = NULL;

    

    printf("Enter File Path : \n");
    scanf("%255s",cPath);

    dp = opendir(cPath);
    if(dp == NULL)
    {
        perror("opendir failed");
    }
    else
    {
        printf("Directory is open successfully \n");
    }

    ls_clone(cPath, dp);


    return 0;
}

// void ls_clone(DIR *dirp)
// {
//     struct dirent *entry = NULL;

//     while ((entry = readdir(dirp)) != NULL)
//     {
//         printf("File Name : %s\n", entry->d_name);

//         if((entry->d_type) == DT_REG)
//         {
//             printf("Type : Regular File \n");
//         }
//         else if((entry->d_type) == DT_DIR)
//         {
//             printf("Type : Directory \n");
//         }
//         else if((entry->d_type) == DT_LNK)
//         {
//             printf("Type : Symbolic Link \n");
//         }
//         else
//         {
//             printf("Type : Other\n");
//         }

//         //printf("Type : %d\n",entry->d_type);
        
//         stat(dirp);
//         printf("Size : %d\n",entry->st_size);
//         printf("Permissions : ");
//         printf("Last Modified time :");
//         printf("**************************** \n");


        

//     }
// }
void print_permissions(mode_t mode)
{
    char perm[10];

    perm[0] = (mode & S_IRUSR) ? 'r' : '-';
    perm[1] = (mode & S_IWUSR) ? 'w' : '-';
    perm[2] = (mode & S_IXUSR) ? 'x' : '-';

    perm[3] = (mode & S_IRGRP) ? 'r' : '-';
    perm[4] = (mode & S_IWGRP) ? 'w' : '-';
    perm[5] = (mode & S_IXGRP) ? 'x' : '-';

    perm[6] = (mode & S_IROTH) ? 'r' : '-';
    perm[7] = (mode & S_IWOTH) ? 'w' : '-';
    perm[8] = (mode & S_IXOTH) ? 'x' : '-';

    perm[9] = '\0';

    printf("Permissions : %s\n", perm);
}


void ls_clone(const char *dirpath, DIR *dirp)
{
    struct dirent *entry = NULL;
    struct stat sb;
    char path[1024];

    while ((entry = readdir(dirp)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        /* Create FULL path */
        snprintf(path, sizeof(path), "%s/%s", dirpath, entry->d_name);

        printf("File Name : %s\n", entry->d_name);
        printf("Full Path : %s\n", path);

        if (stat(path, &sb) == 0)
        {
            if (S_ISREG(sb.st_mode))
                printf("Type : Regular File\n");
            else if (S_ISDIR(sb.st_mode))
                printf("Type : Directory\n");
            else if (S_ISLNK(sb.st_mode))
                printf("Type : Symbolic Link\n");
            else
                printf("Type : Other\n");

            printf("Size : %ld bytes\n", sb.st_size);
            printf("Permissions : %o\n", sb.st_mode & 0777);
            print_permissions(sb.st_mode);
            printf("Last Modified Time : %ld\n", sb.st_mtime);
        }
        else
        {
            perror("stat failed");
        }

        printf("****************************\n");
    }
}

