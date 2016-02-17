#include "main.hpp"
#include "Sampler.hpp"
#include "Clip.hpp"
#include "Mixer.hpp"
#include "Synth.hpp"


static int patestCallback( const void *inputBuffer, void *outputBuffer,
						  unsigned long framesPerBuffer,
						  const PaStreamCallbackTimeInfo* timeInfo,
						  PaStreamCallbackFlags statusFlags,
						  void *userData ) {
	Mixer *mix = (Mixer*)userData;
	float* out = (float*)outputBuffer;
	unsigned long i;
	PaStreamCallbackResult finish = paContinue;
	(void) inputBuffer;
	(void) timeInfo;
	(void) statusFlags;

	for(i=0; i<framesPerBuffer;i++){
		//if(mix->cursor < mix->sampleables[0]->len){
			*out++ = mix->sample();//CH 1
			*out++ = mix->sample();//CH 2
		/*}else{
			*out++ = 0;
			finish = paAbort;
		}*/
	}
	return finish;
}

static void StreamFinished( void* userData ){
	printf( "Stream Completed.\n");
}

//*******************************************************************
int main(void)
{
	PaStreamParameters outputParameters;
	PaStream *stream;
	PaError err;
	int i;

	/* init */
	/*Clip clip1("res/alive01.wav", SAMPLE_RATE*NUM_SECONDS);
	Clip clip2("res/alive02.wav", SAMPLE_RATE*NUM_SECONDS);
	*/
	Sampler** samptable =
		(Sampler**)malloc(sizeof(Sampler*));
	//samptable[0] = &clip1;
	//samptable[1] = &clip2;*/
	Synth ss(2*SAMPLE_RATE*NUM_SECONDS, 0.1, 40.0);
	samptable[0] = &ss;
	Mixer mainMix(samptable, 1);//2);

	err = Pa_Initialize();
	if( err != paNoError ) goto error;

	outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
	if (outputParameters.device == paNoDevice) {
	fprintf(stderr,"Error: No default output device.\n");
	goto error;
	}
	outputParameters.channelCount = 2;       /* stereo output */
	outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
	outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;

	printf("PortAudio Test. SR = %d, Channels = %i\n",
		SAMPLE_RATE,outputParameters.channelCount);

	err = Pa_OpenStream(
			&stream,
			NULL, /* no input */
			&outputParameters,
			SAMPLE_RATE,
			FRAMES_PER_BUFFER,
			paClipOff,      /* we won't output out of range samples so don't bother clipping them */
			patestCallback,
			&mainMix );
	if( err != paNoError ) goto error;

	err = Pa_SetStreamFinishedCallback( stream, &StreamFinished );
	if( err != paNoError ) goto error;

	err = Pa_StartStream( stream );
	if( err != paNoError ) goto error;

	printf("Play for %d seconds.\n", NUM_SECONDS );
	Pa_Sleep( NUM_SECONDS * 1000 );

	err = Pa_StopStream( stream );
	if( err != paNoError ) goto error;

	err = Pa_CloseStream( stream );
	if( err != paNoError ) goto error;

	Pa_Terminate();
	printf("Test finished.\n");

	return err;
	error:
	Pa_Terminate();
	fprintf( stderr, "An error occured while using the portaudio stream\n" );
	fprintf( stderr, "Error number: %d\n", err );
	fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
	return err;
}