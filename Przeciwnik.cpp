#include "Globalne.h"
#include "Fizyka.h"
#include "Przeciwnik.h"
#include <cmath>
#include <iostream>

int f(float x) //1 dla x >= 0, -1 dla x < 0
{
    if(x >= 0.f) return 1;
    return -1;
}

Obiekt* Przeciwnik::bohater;

Przeciwnik::Przeciwnik(bool tchorz, char *folderZObrazkami, int liczbaKlatek, int odstep, int mksHP, float masa, float szybkosc)
{
    stworzony = false;
    Tworz(tchorz, folderZObrazkami, liczbaKlatek, odstep, mksHP, masa, szybkosc);
}

void Przeciwnik::Niszcz()
{
    if(!stworzony) return;
    Czlowiek::Niszcz();
    if(tchorzliwy) panika.Destroy();
}

void Przeciwnik::Aktualizuj()
{
    if(!Czlowiek::Aktualizuj()) return;

    if(strzelanie)
    {
        float f = sqrt(strzal.x * strzal.x + strzal.y * strzal.y) / 15.f;
        if(f <= 1.f)
        {
            strzelanie = false;
            licznik = rand() % 30 + 45;
            NaciagajStrzale(strzal.x, strzal.y);
            PuscStrzale();
        }
        else
        {
            Wektor2D zmiana = strzal / f;
            strzal -= zmiana;
            NaciagajStrzale(zmiana.x, zmiana.y);
        }
    }
    else if(stan == Bezruch && licznik-- < 0 && fabs(bohater->p.x - fizObiekt->p.x) < 800.f && ucieczka == false)
    {
        if(WymierzStrzale())
        {
            NalozStrzale();
            NaciagajStrzale(f(strzal.x) * maxNaciag * 3.5f, 0.f);
            strzal.x -= f(strzal.x) * maxNaciag * 3.5f;
            strzelanie = true;
        }
    }

    if(HP < (maksHP + 1) / 2 && tchorzliwy)
    {
        if(!ucieczka) panika.Play(false);
        ucieczka = true;
        if(bohater->p.x > fizObiekt->p.x) RuchWLewo();
        else RuchWPrawo();
    }
}

void Przeciwnik::Tworz(bool tchorz, char *folderZObrazkami, int liczbaKlatek, int odstep, int mksHP, float masa, float szybkosc)
{
    Czlowiek::Tworz(folderZObrazkami, liczbaKlatek, odstep, mksHP, masa, szybkosc);
    strzelanie = false;
    licznik = rand() % 30 + 45;
    tchorzliwy = tchorz;
    ucieczka = false;
    if(tchorz) panika.Load("dane/dzwieki/panika.wav");
}

bool Przeciwnik::WymierzStrzale()
{
    float a, b, c, d;
    Wektor2D dt = fizObiekt->p + fizObiekt->w / 2.f - bohater->p - bohater->w / 2.f;
    if(dt.x < 0.f) a = M_PI / 2.f;
    else a = -M_PI / 2.f;
    b = a + M_PI;

    while(b - a > 0.0001f)
    {
        c = a + (b - a) / 3.f;
        d = a + (b - a) * 2.f / 3.f;
        float w1 = SprawdzKat(c), w2 = SprawdzKat(d);
        if(w1 < w2)
            a = c;
        else b = d;
    }

    a += (rand() % 100 - 50) / 2000.f;

    strzal = Wektor2D(cos(a), sin(a)) * maxNaciag * 3.5f;
    return true;
}

float Przeciwnik::SprawdzKat(float kat)
{
    float m = 0.5f, op = 0.01f, g = Fizyka.Grawitacja();
    Wektor2D d = fizObiekt->p - bohater->p, p, v = Wektor2D(cos(kat), sin(kat)) * maxNaciag;
    for(int i = 0; i < 1000; i++)
    {
        Wektor2D f(0.f, g * m);
        f -= v * op;
        v += f / m;
        p += v / 2.f;
        if(fabs(p.x) >= fabs(d.x))
            return p.y - d.y;
    }
    return -10000.f;
}
