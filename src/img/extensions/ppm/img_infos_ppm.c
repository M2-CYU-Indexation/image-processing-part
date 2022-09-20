#include "img_infos_ppm.h"

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "NRC/nrc.h"
#include "img/model/ImageInfos.h"
#include "img/process/img_processes.h"

void loadPPM(char* imagePath, rgb8*** image, ImageInfos *infos)
{
    *image = LoadPPM_rgb8matrix(
        imagePath, 
        &infos->nrl,
        &infos->nrh,
        &infos->ncl, 
        &infos->nch
    );
}

int fillDescriptors_PPM(char* imagePath, ImgDescriptors* desc)
{
    // Image
    rgb8** image;
    ImageInfos infos;
    loadPPM(imagePath, &image, &infos);
    desc->width = infos.nch - infos.ncl;
    desc->height = infos.nrh - infos.nrl;
    desc->isRGB = 0;
    fillColorHistograms(image, &infos, &desc->greyHistogram, &desc->redHistogram, &desc->greenHistogram, &desc->blueHistogram);
    desc->averageColor = averageColor(image, &infos, &desc->redRatio, &desc->greenRatio, &desc->blueRatio);
    byte** greyscale = rgbImageToGreyscale(image, &infos);
    SavePGM_bmatrix(greyscale, infos.nrl, infos.nrh, infos.ncl, infos.nch, "/home/aldric-vs/COURS/M2/S9/Indexation/tmp/OUI.pgm");
    gradientNormRelated(
        greyscale, 
        &infos, 
        &desc->gradientNormMean,
        &desc->outlinesBox,
        &desc->outlinesBarycenter,
        &desc->nbOutlines
    );

    freeGreyscale(greyscale, &infos);
    freeRGB(image, &infos);

    return 0;
}