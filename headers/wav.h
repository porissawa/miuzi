#ifndef wave_wav_h
#define wave_wav_h

#include "common.h"

#define SAMPLE_MAX 32767
#define DURATION 5
#define SR 44100
#define NCHANNELS 1
#define NSAMPLES (NCHANNELS * DURATION * SR)

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef int16_t sample_t;

typedef int8_t fourcc[4];

typedef struct {
    fourcc id; //"RIFF"
    uint32_t size;
    fourcc type; //"WAVE"
} riffHdr;

typedef struct {
    fourcc id; // "fmt "
    uint32_t size;
    uint16_t fmt_tag; // 0x1 for LPCM, 0x3 for IEEE float PCM, 0x6 A-law, 0x7 u-law
    uint16_t channels; // 1 for mono, 2 for stereo
    uint32_t samples_per_sec; // sampling rate 1/T, where T is sampling period in seconds
    uint32_t bytes_per_sec; // channels x samples_per_sec x bits_per_sample / 8
    // number of bytes of a single sample of audio across multiple channels.
    uint16_t block_align; // channels x bits_per_sample / 8
    uint16_t bits_per_sample; // bit depth. If depth D <= 8 range is [0, 2^D - 1], if D > 8 [-2^(D-1), 2^(D-1) - 1]
} fmtCk;

typedef struct {
    fourcc id; // "data"
    uint32_t size;
} dataHdr;

typedef struct {
    riffHdr riff;
    fmtCk fmt;
    dataHdr data;
} wavHdr;

void wavWriteHeader(FILE *fp);
void wavWriteSine(FILE *fp);
void wavReadFile(const char *fileBuffer);

#endif
