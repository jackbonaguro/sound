#include "main.hpp"
#include "Sampler.hpp"

Sampler::Sampler(){
	len = 0;
	cursor = 0;
	data = (float*)malloc(0);
}

Sampler::Sampler(int ilen){
	len = ilen;
	cursor = 0;
	data = (float*)malloc(len*sizeof(float));
}

float Sampler::sample(){
	if(cursor == len) {
		cursor = 0;
	}
	return data[cursor++];
}