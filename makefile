CC = g++
CFLAGS = -Wall -pedantic -std=c++11

tester: RushHour.cc RushHourTester.cc
	g++ -o tester RushHour.cc RushHourTester.cc $(CFLAGS)

clean:
	rm tester
