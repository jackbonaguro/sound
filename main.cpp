#include <stdio.h>
#include <math.h>
#include <PortAudio/portaudio.h>
#include <sndfile.hh>

#ifdef WIN32
#include <windows.h>

#if PA_USE_ASIO
#include "pa_asio.h"
#endif
#endif

#define NUM_SECONDS   (180)
#define SAMPLE_RATE   (44100)
#define FRAMES_PER_BUFFER  (64)

#ifndef M_PI
#define M_PI  (3.14159265)
#endif

#define TABLE_SIZE   (200)

class paTestData
{
	public:
	float* data;
	unsigned long cursor, frames;
};

float freq;
static int patestCallback( const void *inputBuffer, void *outputBuffer,
						  unsigned long framesPerBuffer,
						  const PaStreamCallbackTimeInfo* timeInfo,
						  PaStreamCallbackFlags statusFlags,
						  void *userData ) {
	paTestData *testdata = (paTestData*)userData;
	float* out = (float*)outputBuffer;
	unsigned long i;
	int finished = paContinue;
	(void) inputBuffer;
	(void) timeInfo;
	(void) statusFlags;

	for(i=0; i<framesPerBuffer; i++){
		if(testdata->cursor < testdata->frames){
			*out++ = testdata->data[testdata->cursor++];//CH 1
			*out++ = testdata->data[testdata->cursor++];//Ch 2
		}else{
			out[i] = 0;
			return 1;
		}
	}
	return 0;
	/*float *out = (float*)outputBuffer;
    unsigned int i;
    (void) inputBuffer; /* Prevent unused variable warning. */
    
    /*for( i=0; i<framesPerBuffer; i++ )
    {
        *out++ = data->left_phase;  /* left */
        /**out++ = data->right_phase;  /* right */
        /* Generate simple sawtooth phaser that ranges between -1.0 and 1.0. */
        /*data->left_phase += freq + lfo.left_phase;
        data->right_phase += freq + lfo.right_phase;
        /* When signal reaches top, drop back down. */
        /*if( data->left_phase >= 1.0f ) data->left_phase -= 2.0f;
        if( data->right_phase >= 1.0f ) data->right_phase -= 2.0f;

        lfo.left_phase += 0.001;
        lfo.right_phase += 0.0008;
        if( lfo.left_phase >= 0.1f ) lfo.left_phase -= 0.2f;
        if( lfo.right_phase >= 0.2f ) lfo.right_phase -= 0.4f;
    }
	return paContinue;*/
}

paTestData* readwav(char* filename){
	SNDFILE* file;
	SF_INFO info;
	info.frames = SAMPLE_RATE*NUM_SECONDS;
	info. samplerate = SAMPLE_RATE;
	info.channels = 2;
	info.format = SF_FORMAT_WAV;
	file = sf_open(filename,
		SFM_READ, &info);

	if(file == NULL){
		printf(sf_strerror(file));
	}

	paTestData* testdata = (paTestData*)malloc(sizeof(paTestData));
	testdata->data = (float*)malloc(info.frames * info.channels * sizeof(float));

	sf_count_t framestoread = sf_readf_float(file, testdata->data,
		info.frames);

	sf_close(file);

	testdata->cursor = 0;
	testdata->frames = (unsigned long)framestoread;

	return testdata;
}

/*
* This routine is called by portaudio when playback is done.
*/
static void StreamFinished( void* userData )
{
 paTestData *data = (paTestData *) userData;
 printf( "Stream Completed.\n");
}

/*******************************************************************/
int main(void)
{
	PaStreamParameters outputParameters;
	PaStream *stream;
	PaError err;
	paTestData *testdata;
	int i;

	/* initialise */
	freq = 65.406 * 2 / SAMPLE_RATE;

	testdata = readwav("res/alive02.wav");

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

	printf("PortAudio Test. SR = %d, Channels = %d\n",
		SAMPLE_RATE,outputParameters.channelCount);

	err = Pa_OpenStream(
			&stream,
			NULL, /* no input */
			&outputParameters,
			SAMPLE_RATE,
			FRAMES_PER_BUFFER,
			paClipOff,      /* we won't output out of range samples so don't bother clipping them */
			patestCallback,
			testdata );
	if( err != paNoError ) goto error;

	//sprintf( data.message, "No Message" );
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