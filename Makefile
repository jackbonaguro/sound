test:
	-make purge
	-make build
	-make run
	-make purge

go:
	-make build
	-make run

build:
	g++ -c Sampler.cpp Clip.cpp Mixer.cpp Synth.cpp main.cpp
	g++ Sampler.o Clip.o Mixer.o Synth.o main.o -o main.exe -lportaudio -lsndfile -g

run:
	./main.exe

purge:
	rm main.exe
	rm main.o

visualizer:
	-make purge
	g++ -c Sampler.cpp Synth.cpp Visualizer.cpp
	g++ Sampler.o Synth.o Visualizer.o -o main.exe -lportaudio -lsndfile -lSFML-Graphics -lSFML-Window -lSFML-System -g
	-make run
	-make purge