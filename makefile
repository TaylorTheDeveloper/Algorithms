all: sorts

sorts: sortdriver.o
	g++ sortdriver.o -o sorts -Wall -pedantic -g

%.o: %.c
	g++ -c $< -o $@

clean:
	rm -f *.o
	rm -f sorts
