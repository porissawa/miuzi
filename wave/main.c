#include "wav.h"

int main() {
    FILE *fp = fopen("build/output.wav", "wb");
    if (!fp) return 1;

    wavWriteHeader(fp);
    wavWriteSine(fp);
    fclose(fp);

    return 0;
}