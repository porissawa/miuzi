// gcc sine_simple.c -o sine $(pkg-config --cflags --libs jack) -lm 
#include <stdio.h>
#include <math.h>
#include <jack/jack.h>

#define PI_F 3.14159265f

typedef jack_default_audio_sample_t sample_t;

static jack_client_t *client = NULL;
static jack_port_t *port_out = NULL;
static jack_nframes_t sr;

static int on_process(jack_nframes_t nframes, void *arg) {
    static jack_nframes_t tick = 0;
    sample_t *out;
    jack_nframes_t i;

    out = jack_port_get_buffer(port_out, nframes);

    for (i = 0; i < nframes; i++) {
        out[i] = sinf(2 * PI_F * 440 * tick++ / sr);
    }

    return 0;
}

static void jack_init(void) {
    // Open Jack client
    client = jack_client_open("sine", JackNoStartServer, NULL);

    // get current sample rate
    sr = jack_get_sample_rate(client);

    // register process callback
    jack_set_process_callback(client, on_process, NULL);

    // register output audio port
    port_out = jack_port_register(client, "out", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);

    // activate client
    jack_activate(client);
}

static void jack_finish(void) {
    jack_deactivate(client);
    jack_client_close(client);
}


int main(void) {
    jack_init();

    getchar();

    jack_finish();
}