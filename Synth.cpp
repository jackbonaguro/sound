#include "main.hpp"
#include "Sampler.hpp"
#include "Synth.hpp"

Synth::Synth(int ilen, float iamp, float ifreq) {
	len = ilen;
	cursor = 0;
	data = (float*)malloc(len*sizeof(float));

	amp = iamp;
	//Hz -> Cycles / sample
	freq = ifreq / SAMPLE_RATE;
	phase = 0;

	generate();
}

void Synth::generate() {
	for(int i = 0; i < len; i+=2){
		data[i] = amp * sin(2*M_PI*(phase));
		data[i+1] = amp * sin(2*M_PI*(phase));
		if (phase >= 2*M_PI){
			phase -= 2*M_PI;
		}
		phase += freq;
	}
}