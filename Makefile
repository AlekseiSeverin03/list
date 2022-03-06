

step_1: main 
	gcc -c file_operations.cpp list.cpp graph_dump.cpp main.cpp 
	gcc file_operations.o list.o graph_dump.o main.o -o main
	./main
	rm *.o
	dot dump.dot -Tpng -odump.png
	open dump.png


all: step_1
