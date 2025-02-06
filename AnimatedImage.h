#ifndef ANIMATEDIMAGE_H
#define ANIMATEDIMAGE_H

#include "Image.h"
#include <vector>
using namespace std;

namespace Al
{
    class AnimatedImage : public Image
    {
        vector<Image> frames;

        int counter;

        int tmStep;

    public:
        AnimatedImage() { bmp = NULL; }
        AnimatedImage(const char *file, int framesNumber, int timeStep);

        bool Load(const char *file, int framesNumber, int timeStep);

        void SetImage(Image image, int framesNumber, int timeStep);

        void Update() { counter++; }
        void Reset() { counter = 0; }

        int GetFrame() { return counter / tmStep % frames.size(); }

        void Draw(float x, float y);
        void Draw(DrawInfo info);

        int Width();

        void Destroy();
    };
}


#endif // ANIMATEDIMAGE_H
