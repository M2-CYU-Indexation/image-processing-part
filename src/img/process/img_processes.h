#ifndef __IMG_PROCESSES_H__
#define __IMG_PROCESSES_H__

#include "NRC/nrc.h"

#include "img/model/ImageInfos.h"
#include "img/model/geometry.h"

/**
 * Fill the array variable with the image data provided.
 * The array is expected to be of size 255.
 */
void fillHistogram(byte** pixels, ImageInfos* infos, long *array);

/**
 * Fill the array variable with only zeroes.
 * The array is expected to be of size 255.
 */
void fillHistogramZeroes(long *array);

double matrixAverage(byte** matrix, ImageInfos* infos);

/**
 * Find the average color in a greyscale pixel matrix.
 */
int averageColorGreyscale(byte** pixels, ImageInfos* infos, double* redRatio, double* greenRatio, double* blueRatio);

int averageColor(rgb8** pixels, ImageInfos* infos, double* redRatio, double* greenRatio, double* blueRatio);

int rgbToInt(char r, char g, char b);

void intToRbg(int val, char *r, char *g, char *b);

byte** rgbImageToGreyscale(rgb8** pixels, ImageInfos* infos);

/**
 * Compute the gradient norm of the image and retrieve wanted informations.
 */
void gradientNormRelated(byte** pixels, ImageInfos* infos, double* gradientNormAverage, Rect* outlinesBox, Position* outlinesBarycenter, long* nbOutlines);

// ==== FREE ====
void freeGreyscale(byte** pixels, ImageInfos* infos);
void freeRGB(rgb8** pixels, ImageInfos* infos);

#endif // __IMG_PROCESSES_H__