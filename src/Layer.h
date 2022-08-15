#ifndef NNLayer
#define NNLayer

struct Layer{
    //REMEMBER: the weights are stored row-major
    //otherwise we would have to transpose them anyways during the forward pass
    struct Matrix *weights;
    struct Matrix *biases;
    struct Matrix *outputs;

    //totals is the values of the matrices BEFORE the activation function
    //we need to store it so we can do the back propogation
    struct Matrix *totals;
    //input is a parameter of the forward function
    //again, we just store it for back propogation
    struct Matrix *inputs;



    int numberOfNeurons;

    //we need to know this becuase output layer will use softmax
    //activation instead of ReLU
    //1 if it is output layer
    //0 if it is not output layer
    int isOutputLayer;

    int hasBeenForwarded;
};



//REMEMBER: #nuerons = size of output (input of next layer)
struct Layer* newLayer(int numberOfInputs, int numberOfNuerons, int isOutputLayer);

void forward(struct Layer *layer, struct Matrix *inputs);

void callActivationFunction();

//batch size will be the width of the labels matrix
struct Matrix *calculateLoss(struct Layer *layer, struct Matrix *labels);

struct Matrix *backProp(struct Layer *layer, struct Matrix *labels, double learningRate, struct Matrix *loss);

//struct Matrix *calculateLossGradient(struct Matrix *m, int matrixRow, short label);

//expects the output layer to be passed in
//will get the index of the highest probably guess from the network
int getModelPrediction(struct Layer *layer);


#endif