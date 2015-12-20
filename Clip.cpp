#include "Clip.hpp"

Clip::Clip(char* filename, int ilen){
	this->len = ilen;
	this->readwav(filename);
}

void Clip::readwav(char* filename){
	SNDFILE* file;
	SF_INFO info;
	info.frames = 44100*180;
	info. samplerate = 44100;
	info.channels = 2;
	info.format = SF_FORMAT_WAV;
	file = sf_open(filename,
		SFM_READ, &info);

	if(file == NULL){
		printf(sf_strerror(file));
	}

	data = (float*)malloc(info.frames * info.channels * sizeof(float));

	sf_count_t numframes = sf_readf_float(file, data,
		len);

	sf_close(file);

	cursor = 0;
	len = (int)numframes;
}

float Clip::sample(){
	return data[cursor++];
}