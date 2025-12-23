/*
Program : Read Whole File
- Accept File Name and print Full content on console.
- Using a buffer loop (read() until 0).
- Show total bytes read.

*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<sys/stat.h>

int main()
{
    int fd = 0;
    char Arr[10];
    char buffer[50];
    int iRead=0;
    struct stat sobj;
    

    printf("Enter File Name : ");
    scanf("%s",Arr);
    

    
    fd=open(Arr,O_RDONLY);

    if(fd < 0)
    {
        printf("Error : %s\n",strerror(errno));
        return -1;
    }

    
    printf ("File Successfully open with fd : %d\n",fd);

    if (stat(Arr, &sobj)==-1)
    {
        perror("Empty File");
        return -1;
    }
    
    iRead=sobj.st_size;

    int iCount=0;
    read(fd,buffer,iRead);    
    /*for (int i=0; i <= iRead ;i++)
    {
        printf("%c\t%d\t ",buffer[i],iCount);
        iCount = iCount+1;
        
    }*/
   
    while (buffer[iCount]!='\0')
    {
        printf("%c\t ",buffer[iCount]);
        iCount++;
    }
    
    

    iRead=sobj.st_size;
    printf("\n%d : Total Number of Bytes Readed\n",iRead);
    close(fd);

    return 0;
}
