#include "file_stat.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int isDir(char* path)
{
    struct stat fileStats;
    if(stat(path, &fileStats) != 0)
    {
        perror("Cannot see stats of file");
        exit(1);
    }

    return S_ISDIR(fileStats.st_mode);
}

int isFile(char* path)
{
    struct stat fileStats;
    if(stat(path, &fileStats) != 0)
    {
        perror("Cannot see stats of file");
        exit(1);
    }
    return S_ISREG(fileStats.st_mode);
}

char* findExtension(char* path)
{
    return strrchr(path, '.');
}
