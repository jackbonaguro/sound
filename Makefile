test:
	-make purge
	-make build
	-make run

go:
	-make build
	-make run

build:
	g++ -c Sampleable.cpp Clip.cpp Mixer.cpp main.cpp
	g++ Sampleable.o Clip.o Mixer.o main.o -o main.exe -lportaudio -lsndfile -g

run:
	./main.exe

purge:
	rm main.exe
	rm main.o