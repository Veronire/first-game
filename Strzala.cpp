#include "Globalne.h"
#include "Fizyka.h"
#include "Strzala.h"
#include <cmath>
#include <iostream>

Al::Image Strzala::obraz;

Strzala::Strzala(Wektor2D p, Wektor2D v)
{
    Obiekt obiekt("strzała");
    obiekt.m = 0.5f;
    obiekt.v = v;
    obiekt.op = 0.01f;
    obiekt.w = Wektor2D(obraz.Width(), obraz.Height());
    obiekt.p = p - obiekt.w / 2.f;
    obiekt.t = 0.2f;
    obiekt.kol = 0;
    ident = Fizyka.Dodaj(obiekt);
    fizObiekt = &Fizyka[ident];

    doWyrzucenia = false;
}

bool Strzala::Aktualizuj()
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < fizObiekt->kolizje[i].size(); j++)
            if(fizObiekt->kolizje[i][j]->nazwa != fizObiekt->nazwa && fizObiekt->kolizje[i][j]->kol & (1 << (i / 2 * 2 + 1 - i % 2)))
            {
                Fizyka.Usun(ident);
                doWyrzucenia = true;
                return false;
            }

    return true;
}

void Strzala::Rysuj()
{
    if(doWyrzucenia) return;
    Wektor2D v = fizObiekt->v;
    if(v.x == 0.f) v.x = 0.000001f;
    float kat = atan(v.y / v.x);
    if(v.x < 0.f)
        kat += M_PI;

    Wektor2D w = fizObiekt->w / 2.f, p = fizObiekt->p + w;
    obraz.Draw(Al::DrawInfo(p.x - kameraX, p.y - kameraY) + Al::Centre(w.x, w.y) + Al::Rotation(kat));
}
