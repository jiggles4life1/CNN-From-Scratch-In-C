#ifndef Number
#define Number

struct Image{
    unsigned char mat[28][28];
    unsigned short label;
};

void readImage(unsigned char *buffer, struct Image *image, int startOfImage);

void setLabelOfImage(unsigned char *labels, struct Image *image, int curLabel);
void printImage(struct Image *image);


#endif