class Sampler{
public:
	float* data;
	int cursor, len;
	Sampler();
	explicit Sampler(int);
	virtual float sample();
};
