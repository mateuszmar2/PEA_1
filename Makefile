all: run valgrind valgrindleak

run:
	clear
	g++ -o Main Main.cpp Towns.cpp Branch_and_Bound.cpp Brute_Force.cpp Dynamic_Programming.cpp -O2
	rlwrap ./Main

valgrind:
	clear
	g++ -g -o Main Main.cpp Towns.cpp Branch_and_Bound.cpp Brute_Force.cpp Dynamic_Programming.cpp -Wall
	valgrind --track-origins=yes ./Main

valgrindleak:
	clear
	g++ -g -o Main Main.cpp Towns.cpp Branch_and_Bound.cpp Brute_Force.cpp Dynamic_Programming.cpp -Wall
	valgrind --leak-check=full ./Main