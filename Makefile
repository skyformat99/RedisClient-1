REDIS_SRC=src/


CXX=g++

all:
	$(CXX)  $(REDIS_SRC)connection.cc $(REDIS_SRC)redis.cc  main.cc -o redis -std=c++11

redis: main.o redis.o connection.o 
	$(CXX) -o redis main.o connection.o redis.o   -std=c++11
	
connection.o:$(REDIS_SRC)connection.cc $(REDIS_SRC)connection.h $(REDIS_SRC)response.h 
	$(CXX) -c $(REDIS_SRC)connection.cc -std=c++11

redis.o:$(REDIS_SRC)redis.cc $(REDIS_SRC)redis.h
	$(CXX) -c $(REDIS_SRC)redis.cc -std=c++11

main.o:$(REDIS_SRC)redis.h main.cc
	$(CXX) -c main.cc -std=c++11

clean:
	rm *.o
