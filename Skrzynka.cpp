#include "Globalne.h"
#include "Fizyka.h"
#include "Skrzynka.h"

Al::Image Skrzynka::obraz;

void Skrzynka::Tworz(float x, float y, float szer, float wys, float masa)
{
    Obiekt o("skrzynka");
    o.p = Wektor2D(x, y);
    o.w = Wektor2D(szer, wys);
    o.m = masa;
    o.sp = 0.8f;
    o.t = 0.8f;
    o.op = 0.2f;
    fizObiekt = &Fizyka[Fizyka.Dodaj(o)];
}

void Skrzynka::Rysuj()
{
    float skalaX = fizObiekt->w.x / obraz.Width(), skalaY = fizObiekt->w.y / obraz.Height();
    obraz.Draw(Al::DrawInfo(fizObiekt->p.x - kameraX, fizObiekt->p.y - kameraY) + Al::Scale(skalaX, skalaY));
}
