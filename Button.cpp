#include "Image.h"
#include "Font.h"
#include "Button.h"
#include <iostream>
using namespace std;
using namespace Al;

Al::Font Button::font;
Al::Image Button::background;

void Button::LoadResources()
{
    font.Load("gui/font.ttf", 20);
    background.Load("gui/button.png");
}

void Button::DestroyResources()
{
    background.Destroy();
    font.Destroy();
}

void Button::Create(const char *pathToImage, int posX, int posY)
{
    myImg.Load(pathToImage);
    x = posX;
    y = posY;
    w = myImg.Width();
    h = myImg.Height();

    click = NULL;
}

void Button::ProcessEvent(const ALLEGRO_EVENT &event)
{
    switch(event.type)
    {
        case ALLEGRO_EVENT_MOUSE_AXES:
            underCursor = UnderCursor(event.mouse.x, event.mouse.y);
            break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            if(underCursor && click)
                (*click)(event.mouse.button, this);
    }
}

void Button::Draw()
{
    Al::Colour colour = underCursor ? Al::Colour(255, 255, 255) : Al::Colour(dark, dark, dark);

    float scaleX = (float)w / background.Width(), scaleY = (float)h / background.Height();
    background.Draw(Al::DrawInfo(x, y) + Al::Scale(scaleX, scaleY) + colour);

    scaleX = (float)(w - 10) / myImg.Width();
    scaleY = (float)(h - 10) / myImg.Height();
    myImg.Draw(Al::DrawInfo(x + 5, y + 5) + Al::Scale(scaleX, scaleY) + colour);
}

void Button::Resize(int sizeX, int sizeY)
{
    w = sizeX;
    h = sizeY;
}

void Button::MoveTo(int posX, int posY)
{
    x = posX;
    y = posY;
}

void Button::Move(int dx, int dy)
{
    x += dx;
    y += dy;
}

void Button::Scale(float scaleX, float scaleY)
{
    w = w * scaleX;
    h = h * scaleY;
}

void Button::SetImage(Image &image)
{
    img = &image;
    if(w == 0 || h == 0)
    {
        w = img->Width() + 10;
        h = img->Height() + 10;
    }
}
