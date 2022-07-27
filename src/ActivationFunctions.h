#ifndef AllActivationFunctions
#define AllActivationFunctions
//ReLU is generally used as the activation function
//for the hidden layers of the network
double ReLU(double x);


double exponentiation(double x);

double naturalLog(double x);

double loss(struct Matrix *layerOutput, int imageNumber, short label);

#endif