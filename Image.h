#ifndef IMAGE_H
#define IMAGE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <string>
using namespace std;

namespace Al
{
    struct Position
    {
        float px, py;
        Position() { px = py = 0.f; }
        Position(float x, float y) : px(x), py(y) { }
    };

    struct Scale
    {
        float sx, sy;
        Scale() { sx = sy = 1.f; }
        Scale(float x, float y) : sx(x), sy(y) { }
    };

    struct Centre
    {
        float cx, cy;
        Centre() { cx = cy = 0.f; }
        Centre(float x, float y) : cx(x), cy(y) { }
    };

    struct Rotation
    {
        float ang;
        Rotation() { ang = 0.f; }
        Rotation(float angle) : ang(angle) { }
    };

    struct Colour
    {
        ALLEGRO_COLOR col;
        Colour() { col = al_map_rgb(255, 255, 255); }
        Colour(int r, int g, int b, int a = 255) : col(al_map_rgba(r, g, b, a)) { }
    };

    struct FlipX
    {
        bool flipX;
        FlipX(bool flip = false) : flipX(flip) { }
    };

    struct FlipY
    {
        bool flipY;
        FlipY(bool flip = false) : flipY(flip) { }
    };

    struct DrawInfo : Position, Scale, Centre, Rotation, Colour, FlipX, FlipY
    {
        DrawInfo() { }
        DrawInfo(float x, float y)
        {
            px = x; py = y;
        }

        DrawInfo& operator+(Position p)
        {
            px = p.px; py = p.py;
            return *this;
        }

        DrawInfo& operator+(Scale s)
        {
            sx = s.sx; sy = s.sy;
            return *this;
        }

        DrawInfo& operator+(Centre c)
        {
            cx = c.cx; cy = c.cy;
            return *this;
        }

        DrawInfo& operator+(Rotation rot)
        {
            ang = rot.ang;
            return *this;
        }

        DrawInfo& operator+(Colour c)
        {
            col = c.col;
            return *this;
        }

        DrawInfo& operator+(FlipX flip)
        {
            flipX = flip.flipX;
            return *this;
        }

        DrawInfo& operator+(FlipY flip)
        {
            flipY = flip.flipY;
            return *this;
        }
    };

    class Image
    {
    protected:
        ALLEGRO_BITMAP *bmp;

    public:
        Image() { bmp = NULL; }

        Image(ALLEGRO_BITMAP *bitmap) { bmp = bitmap; }
        Image(const char *file);
        Image(int width, int height);

        bool Load(const char *file);

        bool Create(int width, int height);

        void Destroy();

        void Save(const char *file);

        void SetAsTheTarget();

        int Width();

        int Height();

        Image Duplicate();
        Image GetRegion(int x, int y, int w, int h);

        ALLEGRO_COLOR GetPixel(int x, int y);
        void PutPixel(int x, int y, ALLEGRO_COLOR colour);

        void Draw(DrawInfo info);

        void Draw(float x, float y);

        operator bool()
        {
            return bmp != NULL;
        }

        ALLEGRO_BITMAP *GetBitmap()
        {
            return bmp;
        }
    };
}

bool operator ==(ALLEGRO_COLOR a, ALLEGRO_COLOR b);

#endif // IMAGE_H
