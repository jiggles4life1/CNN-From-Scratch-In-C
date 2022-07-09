#ifndef ConvolutionalLayer
#define ConvolutionalLayer

struct ConvLayer{
    int numberOfFilters;
    struct Matrix **filters;
    int filterSize;
    int stride;
};

struct ConvLayer *newConvLayer(int numberOfFilters, int filterSize, int stride);

void printFilters(struct ConvLayer *layer);

struct Matrix *convolution(struct Matrix *image, struct Matrix *filter, struct ConvLayer *layer);

struct Matrix *maxPool(struct Matrix *m, int poolSize);

#endif