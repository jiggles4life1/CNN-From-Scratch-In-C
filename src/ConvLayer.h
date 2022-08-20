#ifndef ConvolutionalLayer
#define ConvolutionalLayer

struct ConvLayer{
    int numberOfFilters;
    struct Matrix **filters;
    int filterSize;
    int stride;
    struct Matrix ***output;
    //we need to keep track of the output size so we know what the input
    //will be of the next layer
    //output is going to equal (batchSize * numberOfFilters)
    int outputSize;

    //the flattened output will be a matrices of (h=1, w=allOutputValuesOverAllMaps)
    struct Matrix *flattenedOutput;


    struct Matrix ***input;
    //input size is the size of the batch
    int inputSize;

    //we need this so we know how to loop through each image in the next layer
    int numberOfMapsPerImage;

    //we dont need to keep track of the size of the 
    //images themselves since they will have a 
    //height and width within the matrix struct
    //thus, we only need to keep track here of how many there are

    //this is for pooling. We need to store the size for backpropogation
    //since we implemented pooling as just a function of the conv layer and not
    //its own layer, we will store it here
    int poolSize;

    int prePoolHeight;
    int prePoolWidth;
    //AFTER much research and reading for an answer, I believe I have concluded
    //that the output that goes into the fully connected layer is the flattened
    //matrix of all of the feature maps (all the filtered matrices), so you flatten them
    //and then concatenate them together, and that is one input.
};

void printConvLayer(struct ConvLayer *layer);

struct ConvLayer *newConvLayer(int numberOfFilters, int filterSize, int stride,
     struct Matrix ***images, int batchSize, int numberOfMapsPerImage, int poolSize);

void printFilters(struct ConvLayer *layer);

struct Matrix *convolution(struct Matrix *image, struct Matrix *filter, struct ConvLayer *layer);

struct Matrix *maxPool(struct Matrix *m, int poolSize);

void forwardConvLayer(struct ConvLayer *layer, struct Matrix ***input);


//void flattenOutput(struct ConvLayer *layer);

void poolOutput(struct ConvLayer *layer, int poolSize);

struct Matrix *getConvLayerOutput(struct ConvLayer *layer);

void freeConvLayer(struct ConvLayer *layer);

//void normalizeConvLayerOutput(struct ConvLayer *layer);
void printConvLayerOutput(struct ConvLayer *layer);

//struct Matrix ***unflattenGradient(struct ConvLayer *layer, struct Matrix *gradient);

//void freeUnflattenedGradient(struct ConvLayer *layer, struct Matrix ***g);

//struct Matrix backPropMaxPool(struct ConvLayer *layer, struct Matrix *gradient);
struct Matrix ***backpropConvLayer(struct ConvLayer *layer, struct Matrix ***gradient, double learningRate);




#endif