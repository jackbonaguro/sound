#include <stdio.h>
#include <math.h>
#include <PortAudio/portaudio.h>
#include <sndfile.hh>

#ifdef WIN32
#include <windows.h>

#if PA_USE_ASIO
#include <PortAudio/pa_asio.h>
#endif
#endif

#define NUM_SECONDS   (180)
#define SAMPLE_RATE   (44100) //Hz
#define FRAMES_PER_BUFFER  (64)

#ifndef M_PI
#define M_PI 4*atan(1)
#endif