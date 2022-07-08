import os
os.system("gcc -Wall -c test.c Matrix.c Layer.c Image.c ImageLoader.c")
os.system("gcc test.o Matrix.o Layer.o Image.o ImageLoader.o")
