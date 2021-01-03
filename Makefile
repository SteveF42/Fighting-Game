all: compile link

run:
	./main

compile:
	g++ -c *.cpp ./Characters/*.cpp ./Characters/moves/*.cpp

link:
	g++ *.o -o main.exe

clean: 
	rm *.o main.exe