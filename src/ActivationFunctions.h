
//ReLU is generally used as the activation function
//for the hidden layers of the network
int ReLU(float x){
    if (x <= 0){
        return 0;
    }
    else{
        return x;
    }
}