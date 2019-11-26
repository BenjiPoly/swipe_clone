all : binary.o main_2.cpp
	g++ binary.o main_2.cpp -o main
binary.o: binary.cpp
	g++ -c binary.cpp
clean: 
	rm *.o
	
	
