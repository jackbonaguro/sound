#include "main.hpp"
#include "Mixer.hpp"

Mixer::Mixer(Sampleable** isampleables, int isize){
	this->size = isize;
	this->sampleables =
		(Sampleable**)malloc(this->size * sizeof(Sampleable));
	for(int i=0; i<this->size; i++){
		this->sampleables[i] = isampleables[i];
	}
}

float Mixer::sample(){
	float val = 0;
	for(int i=0; i<this->size; i++){
		val += (this->sampleables[i])->sample();//Add all samples
	}
	val /= this->size;//Headroom
	return val;
}