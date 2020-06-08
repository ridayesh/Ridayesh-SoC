BASIC_ROUTE = ../../Code Files
INC = ../../SoC Other Files/Include
MyLibs = ../../SoC Other Files/Libs

all: glad.o ImageLoader.o Shader.o Sphere.o Planet.o

VPATH:../../SoC Other Files/Include
glad.o: glad.c
	gcc -c glad.c
ImageLoader.o: ImageLoader.cpp
	g++ -c ImageLoader.cpp
Shader.o: Shader.cpp
	g++ -c Shader.cpp
Planet.o: Planet.cpp
	g++ -c Planet.cpp