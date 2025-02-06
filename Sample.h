#ifndef SAMPLE_H
#define SAMPLE_H

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

namespace Al
{
    class Sample
    {
        private:
            ALLEGRO_SAMPLE *sample;

            ALLEGRO_SAMPLE_ID id;
            bool started;

        public:
            Sample() { started = false; sample = NULL; }
            Sample(const char *file);

            void Load(const char *file);

            void Destroy();

            void Play(bool loop, float volume = 1.f, float speed = 1.f);
            void Stop();

            static void StopAll();

            operator bool() { return sample != NULL; }
    };
};


#endif // SAMPLE_H
