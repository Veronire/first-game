#include "Globalne.h"
#include "Fizyka.h"
#include "Kolce.h"
#include <iostream>

Al::Image Kolce::wysunietyObraz;
Al::Image Kolce::obraz;
Al::Sample Kolce::skrzypniecie;

Kolce::Kolce()
{
    Platforma();
    pozY = 0.f;
    wysuniete = false;
}

Kolce::Kolce(float x, float y, float szer)
{
    y += wysunietyObraz.Height();
    Obiekt obiekt("schowane kolce");
    obiekt.p = Wektor2D(x + tol, y - 1.f);
    obiekt.w = Wektor2D(szer - tol * 2, 1.f);
    obiekt.staly = true;
    obiekt.kol = 0;
    obiekt.sp = 0.7f;
    obiekt.t = 0.7f;
    o = &Fizyka[Fizyka.Dodaj(obiekt)];

    klocki = (szer + obraz.Width() - 1.f) / obraz.Width();
    skala = szer / klocki / obraz.Width() * 1.04f;

    pozY = y - obraz.Height();
    wysuniete = false;
}

void Kolce::Aktualizuj()
{
    if(wysuniete) o->nazwa = "kolce";
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < o->kolizje[i].size(); j++)
            if(!o->kolizje[i][j]->staly && o->kolizje[i][j]->m >= 1.f)
                if(!wysuniete && o->p.y + o->w.y + 15.f >= o->kolizje[i][j]->p.y + o->kolizje[i][j]->w.y)
                {
                    o->p.y -= wysunietyObraz.Height() / 4;
                    o->w.y += wysunietyObraz.Height() / 4;
                    o->kolizje[i][j]->p.y = o->p.y - o->kolizje[i][j]->w.y;
                    o->kol = Gora;
                    pozY -= wysunietyObraz.Height() - obraz.Height();
                    wysuniete = true;
                    o->kolizje[i][j]->staly = true;
                    skrzypniecie.Play(false);
                }
                else if(i == 2)
                    o->kolizje[i][j]->staly = true;
}

void Kolce::Rysuj()
{
    float szer = o->w.x + tol * 2;
    if(wysuniete) for(int i = 0; i < klocki; i++)
        wysunietyObraz.Draw(Al::DrawInfo(o->p.x - tol - kameraX + szer / klocki * i, pozY - kameraY) + Al::Scale(skala, 1.f));

    else for(int i = 0; i < klocki; i++)
        obraz.Draw(Al::DrawInfo(o->p.x - tol - kameraX + szer / klocki * i, pozY - kameraY) + Al::Scale(skala, 1.f));
}
