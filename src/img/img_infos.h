#ifndef __IMG_INFOS_H__
#define __IMG_INFOS_H__

#include "img/model/geometry.h"

/**
 * This struct contains all informations that we want to use as identifiers of our image.
 */
typedef struct img_descriptors_struct
{
    long width;
    long height;
    long greyHistogram[256];
    long redHistogram[256];
    long greenHistogram[256];
    long blueHistogram[256];
    double redRatio;
    double greenRatio;
    double blueRatio;
    int averageColor;
    double gradientNormMean;
    Rect outlinesBox;
    Position outlinesBarycenter;
    long nbOutlines;
    char isRGB;
} ImgDescriptors;

/**
 * Fill informations of the image depending on its content.
 * This returns 0 on success : another values must be 
 * considered as errors.
 */
int fillDescriptors(char* imagePath, ImgDescriptors* desc);

/**
 * Clean and delete all previously allocated memory in the given struct.
 * This does not free this struct itself.
 */
void disposeImgInfos(ImgDescriptors* imgDesc);

#endif // __IMG_INFOS_H__