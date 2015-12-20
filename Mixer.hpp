class Mixer: public Sampleable{
public:
	int size;
	Sampleable** sampleables;
	Mixer(Sampleable**,int);
	virtual float sample();
};