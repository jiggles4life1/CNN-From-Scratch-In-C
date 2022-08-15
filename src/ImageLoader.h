#ifndef imageloader
#define imageloader

struct Image *getNImages(int n);

struct Matrix ***convertImageBatchToConLayerFormat(struct Image *images, int batchSize);

struct Matrix *getOneHotEncodingOfLabels(struct Image *images, int batchSize);

short *getRawLabels(struct Image *images, int batchSize);

void freeImageBatch(struct Image *imageArray, struct Matrix ***convLayerInput, int batchSize, int mapsPerImage);


void freeConvLayerInputBatch(struct Matrix ***input, int batchSize);


#endif