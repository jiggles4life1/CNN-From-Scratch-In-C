#ifndef NNLayer
#define NNLayer

struct Layer{
    //the inputs from the previous layer
    //struct Matrix *inputs;
    struct Matrix *weights;
    struct Matrix *biases;
    struct Matrix *outputs;



    int numberOfNeurons;

    //we need to know this becuase output layer will use softmax
    //activation instead of ReLU
    //1 if it is output layer
    //0 if it is not output layer
    int isOutputLayer;
};



//REMEMBER: #nuerons = size of output (input of next layer)
struct Layer* newLayer(int numberOfInputs, int numberOfNuerons, int isOutputLayer);

void forward(struct Layer *layer, struct Matrix *inputs);

void callActivationFunction();

//batch size will be the width of the labels matrix
struct Matrix *calculateLoss(struct Layer *layer, struct Matrix *labels);


#endif