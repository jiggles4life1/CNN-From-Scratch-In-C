#ifndef NNLayer
#define NNLayer

struct Layer{
    //the inputs from the previous layer
    //struct Matrix *inputs;
    struct Matrix *weights;
    struct Matrix *biases;
    struct Matrix *outputs;

    int numberOfNeurons;

};



//REMEMBER: #nuerons = size of output (input of next layer)
struct Layer* newLayer(int numberOfInputs, int numberOfNuerons);

void forward(struct Layer *layer, struct Matrix *inputs);



#endif