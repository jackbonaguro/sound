#include "main.hpp"
#include "Sampler.hpp"
#include "Mixer.hpp"

Mixer::Mixer(Sampler** isamplers, int isize){
	this->size = isize;
	this->samplers =
		(Sampler**)malloc(this->size * sizeof(Sampler));
	for(int i=0; i<this->size; i++){
		this->samplers[i] = isamplers[i];
	}
}

float Mixer::sample(){
	float val = 0;
	for(int i=0; i<this->size; i++){
		val += (this->samplers[i])->sample();//Add all samples
	}
	val /= this->size;//Headroom
	return val;
}