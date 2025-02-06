#include "AnimatedImage.h"

using namespace Al;

AnimatedImage::AnimatedImage(const char *file, int framesNumber, int timeStep)
{
    Load(file, framesNumber, timeStep);
}

bool AnimatedImage::Load(const char *file, int framesNumber, int timeStep)
{
    if(!Image::Load(file)) return false;
    tmStep = timeStep;

    frames.resize(framesNumber);

    int sizeX = Image::Width() / framesNumber, sizeY = Height();
    for(int i = 0; i < framesNumber; i++)
        frames[i] = GetRegion(i * sizeX, 0, sizeX, sizeY);

    return true;
}

void AnimatedImage::SetImage(Image image, int framesNumber, int timeStep)
{
    if(!image) return;
    bmp = image.GetBitmap();
    tmStep = timeStep;

    frames.resize(framesNumber);

    int sizeX = Image::Width() / framesNumber, sizeY = Height();
    for(int i = 0; i < framesNumber; i++)
        frames[i] = GetRegion(i * sizeX, 0, sizeX, sizeY);
}

void AnimatedImage::Draw(float x, float y)
{
    if(bmp) frames[counter / tmStep % frames.size()].Draw(x, y);
}

void AnimatedImage::Draw(DrawInfo info)
{
    if(bmp) frames[counter / tmStep % frames.size()].Draw(info);
}

int AnimatedImage::Width()
{
    if(!bmp) return 0;
    return frames[0].Width();
}

void AnimatedImage::Destroy()
{
    frames.clear();
    Image::Destroy();
}
