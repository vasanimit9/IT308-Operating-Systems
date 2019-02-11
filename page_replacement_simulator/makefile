all: engine.o vmsim vmgen vmstats

engine.o: engine.h engine.cpp
	g++ -c engine.cpp -w

vmsim: vmsim.o engine.o
	g++ -o vmsim engine.o vmsim.o

vmsim.o: engine.h vmsim.cpp
	g++ -c vmsim.cpp -w

vmgen: vmgen.cpp
	g++ -o vmgen vmgen.cpp

vmstats: vmstats.o engine.o
	g++ -o vmstats engine.o vmstats.o

vmstats.o: engine.h vmstats.cpp
	g++ -c vmstats.cpp -w

clean:
	rm vmsim vmgen vmstats engine.o vmsim.o vmstats.o
