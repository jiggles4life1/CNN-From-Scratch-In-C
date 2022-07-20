#ifndef imageloader
#define imageloader

struct Image *getNImages(int n);

struct Matrix ***convertImageBatchToConLayerFormat(struct Image *images, int batchSize);

#endif