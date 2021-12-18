#include <janet.h>
#include <espeak-ng/speak_lib.h>

espeak_AUDIO_OUTPUT output = AUDIO_OUTPUT_SYNCH_PLAYBACK;
char *path = NULL;
const int buflength = 500, options = 0;
const unsigned int position = 0, position_type = 0, end_position = 0, flags = espeakCHARS_AUTO;
void* user_data;
unsigned int *identifier;

static Janet init(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 0);
    espeak_Initialize(output, buflength, path, options);
    espeak_SetVoiceByName("English");
    return janet_wrap_nil();
}

static Janet say(int32_t argc, Janet *argv)
{
  const char *text;
  janet_fixarity(argc, 1);
  text = janet_unwrap_string(argv[0]);
  espeak_Synth(text, buflength, position, position_type, end_position, flags, identifier, user_data);
  return janet_wrap_nil();
}

static const JanetReg cfuns[] = {
    {"init", init, "(espeak-ng/init)\n\nInitializes espeak-ng."},
    {"say", say, "(espeak-ng/say)\n\nSay something."},
    {NULL, NULL, NULL}
};

JANET_MODULE_ENTRY(JanetTable *env) {
    janet_cfuns(env, "espeak-ng", cfuns);
}
