#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Matrix.h"
#include "ActivationFunctions.h"
//The size of mat is the max size the matrix can be


void printMatrix(struct Matrix *matrix){
    printf("\n");
    //printf("LabelOfImage: %hu\n", matrix->label);
    //print out the matrice in the format of
    for(int i = 0; i < matrix->width; i++){
        printf("----");
    } 
    for(int i = 0; i < matrix->height; i++){
        printf("\n|");
        for(int j = 0; j < matrix->width; j++){
            if(matrix->mat[i][j] >= 0 ){
                printf("%f,  ", matrix->mat[i][j]);
            }
            else{
                printf("%f, ", matrix->mat[i][j]);
            }
        }
        printf("|\n");
    }
        for(int i = 0; i < matrix->width; i++){
        printf("----");
    } 

    printf("\n");
}

void initMatrixWithZeros(struct Matrix *matrix){
    for(int i = 0; i < matrix->height; i++){
        for(int j = 0; j < matrix->width; j++){
            matrix->mat[i][j] = 0;
        }
    }
}



struct Matrix *muliplyMatrices(struct Matrix *m1, struct Matrix *m2){
    //matrices can only be multiplied if the #rows and #columns are equal to one another respectively
    //struct Matrix result;
    //result.width = m1->height;
    //result.height = m2->width;

    struct Matrix *result = newMatrix(m1->height, m2->width);

    int checkOne = (m1->height == m2-> width);
    int checkTwo = (m1->width == m2->height);

    if(!(checkOne || checkTwo)){
        printf("SHAPE ERROR: multiply matrices");
        return result;
    }

    for(int i = 0; i < result->height; i++){
        for(int j = 0; j < result->width; j++){
            double total = 0; 
            for(int k = 0; k < m1->width; k++){
                //printf("\n\n %d \n ", m1->width);
                total += (m1->mat[i][k] * m2->mat[k][j]);
            }
            result->mat[i][j] = total;
        }
    }
    return result;



}

void initMatrixValuesRandomlyBetweenOneAndOne(struct Matrix *m){
    static int i = 0;

    srand(time(NULL) + i);
    double x = ((double)rand()/(double)(RAND_MAX)) * 2.0;
    x -= 1;
    for(int i = 0; i < m->height; i++){
        for(int j = 0; j < m->width; j++){
                double x = ((double)rand()/(double)(RAND_MAX)) * 2.0;
                x -= 1;
                m->mat[i][j] = x;
        }
    }
    i++;


}

void initMatrixValuesRandomlyBetweenZeroAndOne(struct Matrix *m){
    static int i = 0;

    srand(time(NULL) + i);
    double x = ((double)rand()/(double)(RAND_MAX));
    x -= 1;
    for(int i = 0; i < m->height; i++){
        for(int j = 0; j < m->width; j++){
                double x = ((double)rand()/(double)(RAND_MAX)) - 0.5;
                //x -= 1;
                m->mat[i][j] = x;
        }
    }
    i++;


}

struct Matrix *transposeMatrix(struct Matrix *m){
    struct Matrix *n = newMatrix(m->width, m->height);

    for(int i = 0; i < m->height; i++){
        for(int j = 0; j < m->width; j++){
            n->mat[j][i] = m->mat[i][j];
        }
    }
    return n;
}


void setShape(struct Matrix *m, int height, int width){
    m->height = height;
    m->width = width;
}


struct Matrix* newMatrix(int height, int width){
    struct Matrix *m = malloc(sizeof(struct Matrix));
    m->height = height;
    m->width = width;
    m->mat = malloc(sizeof(double*) * height);
    for(int i = 0; i < height; i++){
        m->mat[i] = malloc(sizeof(double) * width);
    }
    return m;
}


void addVectorToEachRow(struct Matrix *m, struct Matrix *v){
    if(m->width != v->width){
        printf("ERROR: matrix width and vector width != (addVectorToEachRow()");
        return;
    }
    for(int i = 0; i < m->height; i++){
        for (int j = 0; j < m->width; j++){
            m->mat[i][j] += v->mat[0][j];
        }
    }
}

void initMatrixWithOnes(struct Matrix *m){
        for(int i = 0; i < m->height; i++){
        for(int j = 0; j < m->width; j++){
            m->mat[i][j] = 1.0;
        }
    }
}


double sum(struct Matrix *m){
    double total = 0.0;
    for(int i = 0; i < m->height; i++){
        for(int j = 0; j < m->width; j++){
            total += m->mat[i][j];
        }
    }
    return total;
}


struct Matrix *elementWiseMultiplication(struct Matrix *x, struct Matrix *y){
    if((x->height != y->height) || (x->width != y->width)){
        return NULL;
    }

    struct Matrix *m = newMatrix(x->height, x->width);
    for(int i = 0; i < x->width; i++){
        for(int j = 0; j < x->height; j++){
            m->mat[i][j] = (x->mat[i][j] * y->mat[i][j]);
        }
    }
    return m;

}

struct Matrix *flattenMatrix(struct Matrix *m){
    //we flatten it across the width because C access memory using row-major
    //so the operation will take less memory accesses if we flatten row-major wise
    int widthOfFlattenedMatrix = m->width * m->height;
    struct Matrix *n = newMatrix(1, widthOfFlattenedMatrix);
    int cur = 0;
    for(int i = 0; i < m->height; i++){
        for(int j = 0; j < m->width; j++){
            n->mat[0][cur] = m->mat[i][j];
            cur++;
        }
    }
    return n;

}


struct Matrix *exponentiateMatrix(struct Matrix *m){
    struct Matrix *newMat = newMatrix(m->height, m->width);
    for(int i = 0; i < m->height; i++){
        for(int j = 0; j < m->width; j++){
            newMat->mat[i][j] = exponentiation(m->mat[i][j]);
        }
    }

    return newMat;
}



struct Matrix *normalizeMatrixByRow(struct Matrix *m){
    struct Matrix *newMat = newMatrix(m->height, m->width);
    double normBase;
    for (int i = 0; i < m->height; i++){
        normBase = 0;
        //gets the sum of the row
        for(int j = 0; j < m->width; j++){
            normBase += m->mat[i][j];
        }

        for(int j = 0; j < m->width; j++){
            newMat->mat[i][j] = m->mat[i][j] / normBase;
        }
    }
    return newMat;
}


struct Matrix *normalizeMatrix(struct Matrix *m){
    struct Matrix *newMat = newMatrix(m->height, m->width);
    
    double normBase = sum(m);
    for (int i = 0; i < m->height; i++){
        for(int j = 0; j < m->width; j++){
            newMat->mat[i][j] = m->mat[i][j] / normBase;
        }
    }
    return newMat;
}

//beacuse for softmax we use exponentiation, this protects the values
//from being > 1, and potentially causing integer overflow issues
struct Matrix *subtractByMaxRowWise(struct Matrix *m){
    struct Matrix *newMat = newMatrix(m->height, m->width);

    double curMax;
    for(int i = 0; i < m->height; i++){
        curMax = 0;
        //find the max during 1st iteration
        for(int j = 0; j < m->width; j++){
            if (m->mat[i][j] > curMax){
                curMax = m->mat[i][j];
            }
        }
        //subtract each element during second iteration
        for(int j = 0; j < m->width; j++){
            m->mat[i][j] -= curMax;
            newMat->mat[i][j] = m->mat[i][j];
        }
    }

    return newMat;


}


//Matrices MUST be same height for this function to work
struct Matrix *concatenateMatricesRowWise(struct Matrix *x, struct Matrix *y, int setCur){
    //static int cur = 0;
    if(x->width <= 1){
        struct Matrix *m = newMatrix(y->height, y->width);
        for(int i = 0; i < y->height; i++){
            for(int j = 0; j < y->width; j++){
                m->mat[i][j] = y->mat[i][j];
            }
        }
        return m;
    }
    if (setCur){
        //cur = 0;
    }
    if(x->height != y->height){
        struct Matrix *nullptr;
        printf("ERROR: matrices are not same hieight in concatenateMatricesRowWise");
        return nullptr;

    }
    int cur = 0;
    struct Matrix *m = newMatrix(y->height , x->width + y->width);
    for(int i = 0; i < x->height; i++){
        for(int j = 0; j < x->width; j++){
            m->mat[i][cur] = x->mat[i][j];
            cur++;
        }
        for(int j = 0; j < y->width; j++){
            m->mat[i][cur] = y->mat[i][j];
            cur++;
        }
    }
    return m;
}

void fillIn(struct Matrix *x, struct Matrix *y, int setCur){
    static int cur = 0;
    if (setCur){
        cur = 0;
    }


    for(int i = 0; i < y->height; i++){
        for(int j = 0; j < y->width; j++){
            x->mat[i][cur] = y->mat[i][j];
            cur++;
            printf("\n cur = %d", cur);
        }
    }
}


void freeMatrix(struct Matrix *m){
    for(int i = 0; i < m->height; i++){
        free(m->mat[i]);
    }
    free(m->mat);
    free(m);
}


struct Matrix *concatenateMatricesColWise(struct Matrix *x, struct Matrix *y){
        //static int cur = 0;
    if(x->width <= 1){
        struct Matrix *m = newMatrix(y->height, y->width);
        for(int i = 0; i < y->height; i++){
            for(int j = 0; j < y->width; j++){
                m->mat[i][j] = y->mat[i][j];
            }
        }
        return m;
    }
    if(x->width != y->width){
        struct Matrix *nullptr;
        printf("ERROR: matrices are not same width in concatenateMatricesColWise");
        return nullptr;

    }
    int cur = 0;
    struct Matrix *m = newMatrix(y->height + x->height ,y->width);
    /*for(int i = 0; i < x->height; i++){
        for(int j = 0; j < x->width; j++){
            m->mat[i][cur] = x->mat[i][j];
            cur++;
        }
        for(int j = 0; j < y->width; j++){
            m->mat[i][cur] = y->mat[i][j];
            cur++;
        }
    }
    */
    for(int i = 0; i < x->height; i++){
        for(int j = 0; j < x->width; j++){
            m->mat[cur][j] = x->mat[i][j];
        }
        cur++;
    }
    for(int i = 0; i < y->height; i++){
        for(int j = 0; j < y->width; j++){
            m->mat[cur][j] = y->mat[i][j];
        }
        cur++;
    }
    return m;
}


struct Matrix *clipMatrixValues(struct Matrix *m, double min, double max){
    struct Matrix *n = newMatrix(m->height, m->width);

    for(int i = 0; i < n->height; i++){
        for(int j = 0; j < n->width; j++){
            double val;
            if(m->mat[i][j] < min){
                val = min;
            }
            else if(m->mat[i][j] > max){
                val = max;
            }
            else{
                val = m->mat[i][j];
            }


            n->mat[i][j] = val;
        }
    }

    return n;
}



struct Matrix *copyMatrix(struct Matrix *m){
    struct Matrix *n = newMatrix(m->height, m->width);

    for(int i = 0; i < m->height; i++){
        for(int j = 0; j < m->width; j++){
            n->mat[i][j] = m->mat[i][j];
        }
    }

    return n;
}


struct Matrix *multiplyByValue(struct Matrix *m, double value){
    struct Matrix *n = newMatrix(m->height, m->width);

    for(int i = 0; i < m->height; i++){
        for(int j = 0; j < m->width; j++){
            n->mat[i][j] = m->mat[i][j] * value;
        }
    }
    return n;
}


struct Matrix *elementWiseSubtraction(struct Matrix *m, struct Matrix *n){
    struct Matrix *x = newMatrix(m->height, m->width);

    if((m->height != n->height) || (m->width != n->width)){
        printf("\n\n shape error in elementWiseSubtraction\n\n");
        return x;
    }



    for(int i =0; i < m->height; i++){
        for(int j = 0; j < m->width; j++){
            x->mat[i][j] = m->mat[i][j] - n->mat[i][j];
        }
    }

    return x;
}


struct Matrix *normalizeImageTo255(struct Matrix *m){
    struct Matrix *n = newMatrix(m->height, m->width);
    for(int i = 0; i < m->height; i++){
        for(int j = 0; j < m->width; j++){
            //we divide by 255 becuase thats the max value possible in the image
            if(m->mat[i][j] == (double) 0){
                n->mat[i][j] = (double) 0 - 0.5;
            }
            else{
                n->mat[i][j] = m->mat[i][j] / 255;
                n->mat[i][j] -= 0.5;
            }
        }
    }
    return n;
}



void transformImage(struct Matrix *m){
    for(int i = 0; i < m->height; i++){
        for(int j = 0; j < m->width; j++){
            if (m->mat[i][j] != 0){
                m->mat[i][j] = m->mat[i][j] / 255;
            }
            m->mat[i][j] = m->mat[i][j] - 0.5;
        }
    }
}


struct Matrix *divideMatrixByValue(struct Matrix *m, double value){
    struct Matrix *n = newMatrix(m->height, m->width);

    for(int i = 0; i < n->height; i++){
        for(int j = 0; j < n->width; j++){
            n->mat[i][j] = m->mat[i][j] / value;
        }
    }

    return n;
}