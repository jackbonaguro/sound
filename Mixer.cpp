#include "main.hpp"
#include "Sampler.hpp"
#include "Mixer.hpp"

Mixer::Mixer(Sampler** isamplers, int isize){
	size = isize;
	samplers = (Sampler**)malloc(size*sizeof(Sampler));
	int min = -1;
	for(int i=0; i<this->size; i++){
		samplers[i] = isamplers[i];
		min = (min > samplers[i]->len || min == -1)
			? samplers[i]->len : min;
	}

	len = min;
	cursor = 0;
	data = (float*)malloc(len*sizeof(float));

	mix();
}

void Mixer::mix(){
	for(int i=0; i<len; i++){
		data[i] = 0;
		for(int j=0; j<size; j++){
			data[i] += samplers[j]->data[i];//Add all samples
		}
		data[i] /= size;//Headroom
	}
}