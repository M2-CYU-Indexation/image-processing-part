
#include <stdio.h>
#include <fts.h>
#include <errno.h>
#include <string.h>

#include "input/input.h"
#include "img/img_infos.h"
#include "file/file_stat.h"

int compareFiles(const FTSENT** one, const FTSENT** two)
{
    return (strcmp((*one)->fts_name, (*two)->fts_name));
}

void processFile(char* inputPath, char* outputPath)
{
    ImgDescriptors infos;
    int resFillInfos = fillDescriptors(inputPath, &infos);
    if (resFillInfos != 0)
    {
        fprintf(stderr, "Error code %d raised when filling informations\n", resFillInfos);
    }
}

void processFolder(char* inputPath, char* outputPath)
{
    // fts_open expects a list of paths
    char* toOpen[] = {inputPath, NULL};
    FTS* filesystem = fts_open(toOpen, FTS_COMFOLLOW | FTS_NOCHDIR, &compareFiles);
    if (filesystem == NULL)
    {
        fprintf(stderr, "The folder is empty");
        return;
    }

    // Loop through all files in folder
    int fileCounter = 0;
    FTSENT *parent = NULL, *child = NULL;
    while ((parent = fts_read(filesystem)) != NULL)
    {
        child = fts_children(filesystem, 0);
        // If errno != 0, it is likely to be a permission denied
        if (errno != 0)
        {
            fprintf(stderr, "Cannot handle file %s", child->fts_path);
            perror("");
        }

        while (child != NULL)
        {
            char* dirPath = child->fts_path;
            char* basename = child->fts_name;
            // Create the filename from the dirpath and basename
            char path[4096] = {0};
            strcat(path, dirPath);
            strcat(path, basename);

            printf("%s\n", path);
            
            if (isFile(path))
            {
                fileCounter++;
                printf("Process file n°%d : \"%s\"\n", fileCounter, path);
                processFile(path, outputPath);
            }

            child = child->fts_link;
        }
    }
    printf("End of folder processing\n");
    fts_close(filesystem);
}

int main(int argc, char  *argv[])
{
    Input input;

    printf("%d\n", isFile("/home/aldric-vs/COURS/M2/S9/Indexation/PpmsPgms/archive10pgm/arbre2.pgm"));

    int respRetrieve = retrieveInput(argc, argv, &input);
    if (respRetrieve != 0)
    {
        fprintf(stderr, "Error while retrieving the inputs : error code %d\n", respRetrieve);
        return 1;
    }

    if (!isDir(input.outputPath))
    {
        fprintf(stderr, "Output path is not a folder");
    }

    char* inputPath = input.inputPath;
    if(isDir(inputPath))
    {
        printf("Process folder \"%s\"\n", inputPath);
        processFolder(inputPath, input.outputPath);
    }
    else
    {
        printf("Process file \"%s\"\n", inputPath);
        processFile(inputPath, input.outputPath);
    }

    return 0;
}
