CXX=clang++
LDFLAGS=-lglew -framework OpenGL -framework GLUT -framework Cocoa

all: ogl3

textfile.o: textfile.cpp textfile.h
	$(CXX) -c -o textfile.o textfile.cpp

ogl3: textfile.o ogl3.cpp 
	clang++ -o ogl3 $(LDFLAGS) textfile.o ogl3.cpp  
