#include "main.hpp"

class Clip: public Sampleable{
public:
	float* data;
	int cursor, len;
	Clip(char*,int);
	virtual float sample();
	virtual void readwav(char*);
};