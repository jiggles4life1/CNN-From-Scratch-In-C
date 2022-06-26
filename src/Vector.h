//right now th

struct Vector{  
    double *vec;
    int size;
};


void initVector(int size, struct Vector *vec);

double dot(struct Vector *vecOne, struct Vector *vecTwo);

void printVector(struct Vector *vec);

void freeVector(struct Vector *vec);