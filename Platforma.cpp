#include "Globalne.h"
#include "Fizyka.h"
#include "Platforma.h"
#include <iostream>
#include <cmath>

Al::Image Platforma::obraz;

Platforma::Platforma(float x, float y, float szer)
{
    Obiekt obiekt("platforma");
    obiekt.p = Wektor2D(x, y);
    obiekt.w = Wektor2D(szer, obraz.Height());
    obiekt.staly = true;
    obiekt.sp = 0.7f;
    obiekt.t = 0.7f;
    obiekt.kol = Gora;
    o = &Fizyka[Fizyka.Dodaj(obiekt)];
    px = x;

    klocki = (szer + obraz.Width() - 1.f) / obraz.Width();
    skala = szer / klocki / obraz.Width() * 1.04f;
}

void Platforma::Rysuj()
{
    for(int i = 0; i < klocki; i++)
        obraz.Draw(Al::DrawInfo(o->p.x - kameraX + o->w.x / klocki * i, o->p.y - kameraY) + Al::Scale(skala, 1.f));
}
