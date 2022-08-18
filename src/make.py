import os
os.system("gcc -Wall -c test.c Matrix.c Layer.c Image.c ImageLoader.c ConvLayer.c ActivationFunctions.c MaxPool.c")
os.system("gcc test.o Matrix.o Layer.o Image.o ImageLoader.o ConvLayer.o ActivationFunctions.o MaxPool.o")
