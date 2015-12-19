test:
	-make purge
	-make build
	-make run

go:
	-make build
	-make run

build:
	g++ -c main.cpp
	g++ main.o -o main.exe -lportaudio -lsndfile -g

run:
	./main.exe

purge:
	rm main.exe
	rm main.o