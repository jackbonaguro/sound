#include "Sampleable.hpp"

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