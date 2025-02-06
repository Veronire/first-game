#include "Sample.h"
#include <iostream>
using namespace std;

using namespace Al;

Sample::Sample(const char *file)
{
    sample = NULL;
    started = false;
    Load(file);
}

void Sample::Load(const char *file)
{
    Stop();
    if(sample) Destroy();
    sample = al_load_sample(file);
    if(!sample) cerr << "Unable to load a sound from " << file << endl;
}

void Sample::Destroy()
{
    if(sample) al_destroy_sample(sample);
    sample = NULL;
}

void Sample::Play(bool loop, float volume, float speed)
{
    if(sample)
    {
        Stop();
        al_play_sample(sample, volume, 0.f, speed, loop ? ALLEGRO_PLAYMODE_LOOP : ALLEGRO_PLAYMODE_ONCE, &id);
        started = true;
    }
}

void Sample::Stop()
{
    if(started) al_stop_sample(&id);
    started = false;
}

void Sample::StopAll()
{
    al_stop_samples();
}
