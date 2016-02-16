class Synth: public Sampler{
public:
	float amp, freq, phase;
	Synth(int, float, float);
	virtual void generate();
};