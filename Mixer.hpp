class Mixer: public Sampler{
public:
	int size;
	Sampler** samplers;
	Mixer(Sampler**,int);
	virtual void mix();
};