#include "../headers/common.h"
#include "../headers/wav.h"

void wavReadFile(const char *fileBuffer) {
    wavHdr hdr = {0};
    memcpy(&hdr, fileBuffer, sizeof(wavHdr));
    printf("riffHdr id: %s\n", hdr.riff.id);
    printf("sample rate: %d\n", hdr.fmt.samples_per_sec);
    printf("bits per sample: %d\n", hdr.fmt.bits_per_sample);
    printf("dataHdr size: %d\n", hdr.data.size);
}
