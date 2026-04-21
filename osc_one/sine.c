#include <stdio.h>
#include <math.h>
#include <jack/jack.h>

#define PI_F 3.14159265f

typedef jack_default_audio_sample_t sample_t;

static jack_client_t *client = NULL;
static jack_port_t *port_in = NULL, *port_out = NULL;

static int on_process(jack_nframes_t nframes, void *arg) {
    const sample_t *in;
    sample_t *out;
    jack_nframes_t i;

    in  = jack_port_get_buffer(port_in,  nframes);
    out = jack_port_get_buffer(port_out, nframes);

    for (i = 0; i < nframes; ++i) {
        out[i] = sinf(2*PI_F*in[i]);
    }

    return 0;
}

static void jack_init(void) {
    // Open Jack client
    client = jack_client_open("sine", JackNoStartServer, NULL);

    // register process callback
    jack_set_process_callback(client, on_process, NULL);

    // register input and output audio port
    port_in  = jack_port_register(client, "phs", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
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

    // Idle main thread
    getchar();

    jack_finish();
}