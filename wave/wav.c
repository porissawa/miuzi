#include "../headers/common.h"
#include "../headers/wav.h"

// Only works on little-endian machines
void wavWriteHeader(FILE *fp) {
    wavHdr hdr = {0};

    // RIFF HEADER
    memcpy(&hdr.riff.id, "RIFF", 4);
    hdr.riff.size = 36 + NSAMPLES * sizeof(sample_t);
    memcpy(&hdr.riff.type, "WAVE", 4);

    // FMT CHUNK
    memcpy(&hdr.fmt.id, "fmt ", 4);
    hdr.fmt.size = 16;
    hdr.fmt.fmt_tag = 1;
    hdr.fmt.channels = NCHANNELS;
    hdr.fmt.samples_per_sec = SR;
    hdr.fmt.bytes_per_sec = NCHANNELS * SR * sizeof(sample_t);
    hdr.fmt.block_align = NCHANNELS * sizeof(sample_t);
    hdr.fmt.bits_per_sample = 8 * sizeof(sample_t);

    // DATA HEADER
    memcpy(&hdr.data.id, "data", 4);
    hdr.data.size = NSAMPLES * sizeof(sample_t);

    fwrite(&hdr, sizeof(wavHdr), 1, fp);
}

void wavWriteSine(FILE *fp) {
    static sample_t buf[NSAMPLES];
    float gain = 0.2;

    for (size_t i = 0; i < NSAMPLES; ++i) {
        buf[i] = lrint(SAMPLE_MAX * gain * sin(2 * M_PI * 440 * i/SR));
    }

    fwrite(buf, sizeof(buf), 1, fp);

    if (sizeof(buf) % 2 == 1){
        char nil = 0;
        fwrite(&nil, 1, 1, fp);
    }
}
