queue_store.o: 
	g++  -c queue_store.cpp -pthread -std=c++11

main: main.cpp
	g++  main.cpp -o main -std=c++11 -pthread queue_store.o

clean:
	rm queue_store.o  main
