/*
 * ceramic-core.ino -  core functionality for ceramic synth.
 * Elijah Beard (2026)
 */
#include <MozziGuts.h>
#include <Oscil.h>
#include <tables/sin2048_int8.h>
#include "song.h"

#define NUM_VOICES 12

struct Voice {
  Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> osc;
  int note;
  bool active;
};

Voice voices[NUM_VOICES] = {
  {Oscil<SIN2048_NUM_CELLS, AUDIO_RATE>(SIN2048_DATA), -1, false},
  {Oscil<SIN2048_NUM_CELLS, AUDIO_RATE>(SIN2048_DATA), -1, false},
  {Oscil<SIN2048_NUM_CELLS, AUDIO_RATE>(SIN2048_DATA), -1, false},
  {Oscil<SIN2048_NUM_CELLS, AUDIO_RATE>(SIN2048_DATA), -1, false},
  {Oscil<SIN2048_NUM_CELLS, AUDIO_RATE>(SIN2048_DATA), -1, false},
  {Oscil<SIN2048_NUM_CELLS, AUDIO_RATE>(SIN2048_DATA), -1, false},
  {Oscil<SIN2048_NUM_CELLS, AUDIO_RATE>(SIN2048_DATA), -1, false},
  {Oscil<SIN2048_NUM_CELLS, AUDIO_RATE>(SIN2048_DATA), -1, false},
  {Oscil<SIN2048_NUM_CELLS, AUDIO_RATE>(SIN2048_DATA), -1, false},
  {Oscil<SIN2048_NUM_CELLS, AUDIO_RATE>(SIN2048_DATA), -1, false},
  {Oscil<SIN2048_NUM_CELLS, AUDIO_RATE>(SIN2048_DATA), -1, false},
  {Oscil<SIN2048_NUM_CELLS, AUDIO_RATE>(SIN2048_DATA), -1, false}
};

byte voiceNote[NUM_VOICES];
bool active[NUM_VOICES];

float midiToFreq(byte n){
  return 440.0 * pow(2,(n-69)/12.0);
}

void noteOn(int note) {
  for(int i=0;i<NUM_VOICES;i++){
    if(!voices[i].active){
      voices[i].note = note;
      voices[i].osc.setFreq(midiToFreq(note));
      voices[i].active = true;
      return;
    }
  }
}

void noteOff(int note) {
  for(int i=0;i<NUM_VOICES;i++){
    if(voices[i].active && voices[i].note == note){
      voices[i].active = false;
    }
  }
}

uint16_t eventIndex = 0;
uint32_t nextEventTime = 0;

void updateControl(){

  uint32_t now = millis() / 4;

  while(eventIndex < SONG_LENGTH && now >= nextEventTime){

    PackedEvent e;
    memcpy_P(&e,&song[eventIndex],sizeof(PackedEvent));

    byte note = e.event & 0x7F;

    if(e.event & 0x80)
      noteOn(note);
    else
      noteOff(note);

    nextEventTime += e.delta;

    eventIndex++;
  }
}

AudioOutput_t updateAudio(){

  int mix=0;

  for(int i=0;i<NUM_VOICES;i++){
    if(voices[i].active){
      mix += voices[i].osc.next();
    }
  }

  mix /= NUM_VOICES;

  return MonoOutput::from8Bit(mix);
}

void setup(){

  for(int i=0;i<NUM_VOICES;i++)
    active[i] = false;

  nextEventTime = millis();

  startMozzi();
}

void loop(){
  audioHook();
}