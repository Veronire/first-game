#include "Fizyka.h"
#include "Globalne.h"
#include <cmath>
#include <algorithm>
#include <iostream>

int Kolizja(const Obiekt &o1, const Obiekt &o2)
{
    /*Zwraca liczbę z poustawianymi flagami
        1 - kolizja z lewej od o1
        2 - kolizja z prawej od o1
        4 - kolizja z gory od o1
        8 - kolizja z dolu od o1
    */
    int wynik = 0;
    int wPion = 0, wPoz = 0;

    Wektor2D p = o1.p + o1.v - o2.v;

    float a = min(p.x + o1.w.x, o2.p.x + o2.w.x) - max(p.x, o2.p.x),
        b = min(p.y + o1.w.y, o2.p.y + o2.w.y) - max(p.y, o2.p.y);

    if(p.x < o2.p.x + o2.w.x + 0.11f && o1.p.x + 0.11f > o2.p.x + o2.w.x) wPoz |= Lewo;
    else if(p.x + o1.w.x + 0.11f > o2.p.x && o1.p.x + o1.w.x < o2.p.x + 0.11f) wPoz |= Prawo;
    if(p.y < o2.p.y + o2.w.y + 0.11f && o1.p.y + 0.11f > o2.p.y + o2.w.y) wPion |= Gora;
    else if(p.y + o1.w.y + 0.11f > o2.p.y && o1.p.y + o1.w.y < o2.p.y + 0.11f) wPion |= Dol;

    if(b > 0.f || wPion)
        wynik = wPoz;
    if((a > 0.f || wPoz) && wPion && (!wynik || a > b))
        wynik = wPion;

    if(a > 0.f && b > 0.f && wynik == 0 && o1.kol == 15 && o2.kol == 15)
    {
        Wektor2D w = p + o1.w / 2.f - (o2.p + o2.w / 2.f);
        if(w.x < 0.f) wPoz |= Prawo;
        else if(w.y > 0.f) wPoz |= Lewo;
        if(w.y < 0.f) wPion |= Dol;
        else if(w.y > 0.f) wPion |= Gora;

        if(fabs(w.x) > fabs(w.y)) wynik = wPoz;
        else wynik = wPion;
    }

    return wynik;
}

float sgn(float f)
{
    if(f > 0) return 1.f;
    if(f < 0) return -1.f;
    return 0.f;
}

Fiz::Fiz()
{
    n = 0;
    g = 3.f;
    w = 1.f;
    obiekty.reserve(10000);
    DodajGranice();
}

int Fiz::Dodaj(Obiekt o)
{
    int n;
    if(wolne.empty())
    {
        n = obiekty.size();
        obiekty.push_back(make_pair(true, Obiekt()));
    }
    else
    {
        n = wolne.front();
        wolne.pop();
    }

    obiekty[n] = make_pair(true, o);
    return n;
}

void Fiz::Usun(int k)
{
    if(k >= obiekty.size() || obiekty[k].first == false) return;
    obiekty[k].first = false;
    wolne.push(k);
}

void Fiz::Resetuj()
{
     cerr << "reset" << endl;
    obiekty.clear();
    obiekty.reserve(10000);
    while(!wolne.empty()) wolne.pop();
    n = 0;
    DodajGranice();
}

void Fiz::DodajGranice()
{
    Obiekt gora("Gorna granica");
    Obiekt dol("Dolna granica");
    Obiekt lewo("Lewa granica");
    Obiekt prawo("Prawa granica");
    gora.staly = dol.staly = lewo.staly = prawo.staly = true;
    gora.p.x = dol.p.x = -1000.f;
    gora.w = dol.w = Wektor2D(swiatX + 2000.f, 1.f);
    lewo.p.y = prawo.p.y = -1000.f;
    lewo.w = prawo.w = Wektor2D(1.f, swiatY + 2000.f);
    dol.p.y = swiatY + 100.f;
    prawo.p.x = swiatX;
    gora.kol = 0;
    dol.kol = Gora;
    lewo.kol = Prawo;
    prawo.kol = Lewo;
    //Dodaj(gora);
    Dodaj(dol);
    Dodaj(lewo);
    Dodaj(prawo);
}

bool PorownajLewyBok(Obiekt *a, Obiekt *b)
{
    return a->p.x < b->p.x;
}

bool PorownajPrawyBok(Obiekt *a, Obiekt *b)
{
    return a->p.x + a->w.x > b->p.x + b->w.x;
}

bool PorownajSzczyt(Obiekt *a, Obiekt *b)
{
    return a->p.y < b->p.y;
}

bool PorownajSpod(Obiekt *a, Obiekt *b)
{
    return a->p.y + a->w.y > b->p.y + b->w.y;
}

void Fiz::Aktualizuj()
{
    vector<pair<bool, Obiekt> >::iterator it;

    FOREACH(it, obiekty)
    {
        Obiekt &o = it->second;
        if(o.staly) continue;

        Wektor2D f(0.f, g * o.m);
        f -= o.v * o.op;
        o.v += f / o.m;
        o.wLocie = true;
    }

    FOREACH(it, obiekty)
    {
        Obiekt &o = it->second;

        for(int i = 0; i < 4; i++)
            o.kolizje[i].clear();

        vector<pair<bool, Obiekt> >::iterator it2;
        FOREACH(it2, obiekty)
        {
            if(it == it2) continue;
            Obiekt &o2 = it2->second;
            int kol = Kolizja(o, o2);
            if(kol & Lewo)
                o.kolizje[0].push_back(&o2);
            if(kol & Prawo)
                o.kolizje[1].push_back(&o2);
            if(kol & Gora)
                o.kolizje[2].push_back(&o2);
            if(kol & Dol)
                o.kolizje[3].push_back(&o2);
        }
    }

    FOREACH(it, obiekty)
    {
        Obiekt &o = it->second;
        if(o.staly) continue;

        o.p += o.v * w;
    }

    vector<pair<bool, Obiekt> > tmp = obiekty;

    FOREACH(it, obiekty)
    {
        Obiekt &o = it->second;
        if(o.staly) continue;

        if(o.kol & Lewo)
        {
            sort(o.kolizje[0].begin(), o.kolizje[0].end(), PorownajPrawyBok);
            for(int i = 0; i < o.kolizje[0].size(); i++)
                if(o.kolizje[0][i]->kol & Prawo)
                {
                    Obiekt &o2 = *o.kolizje[0][i];
                    o.p.x = o2.p.x + o2.w.x - 0.1f;
                    if(o2.staly)
                        o.v.x *= -o.sp * o2.sp;
                    else
                    {
                        o.v.x = 2 * o2.m * o2.v.x / (o.m + o2.m) + (o.m - o2.m) / (o.m + o2.m) * o2.v.x;
                        o.v.x *= o.sp * o2.sp;
                    }
                    //o.v.y -= o.v.y * o.t * o2.t;
                    o.kolizje[0].resize(i + 1);
                }
        }
        if(o.kol & Prawo)
        {
            sort(o.kolizje[1].begin(), o.kolizje[1].end(), PorownajLewyBok);
            for(int i = 0; i < o.kolizje[1].size(); i++)
                if(o.kolizje[1][i]->kol & Lewo)
                {
                    Obiekt &o2 = *o.kolizje[1][i];
                    o.p.x = o2.p.x - o.w.x + 0.1f;
                    if(o2.staly)
                        o.v.x *= -o.sp * o2.sp;
                    else
                    {
                        o.v.x = 2 * o2.m * o2.v.x / (o.m + o2.m) + (o.m - o2.m) / (o.m + o2.m) * o2.v.x;
                        o.v.x *= o.sp * o2.sp;
                    }
                    //o.v.y -= o.v.y * o.t * o2.t;
                    o.kolizje[1].resize(i + 1);
                }
        }
        if(o.kol & Gora)
        {
            sort(o.kolizje[2].begin(), o.kolizje[2].end(), PorownajSpod);
            for(int i = 0; i < o.kolizje[2].size(); i++)
                if(o.kolizje[2][i]->kol & Dol)
                {
                    Obiekt &o2 = *o.kolizje[2][i];
                    //o.p.y = o2.p.y + o2.w.y - 0.1f;
                    if(o2.staly)
                        o.v.y *= -o.sp * o2.sp;
                    else
                    {
                        o.v.y = 2 * o2.m * o2.v.y / (o.m + o2.m) + (o.m - o2.m) / (o.m + o2.m) * o2.v.y;
                        o.v.y *= o.sp * o2.sp;
                    }
                    o.v.x -= o.v.x * o.t * o2.t;
                    o.kolizje[2].resize(i + 1);
                }
        }
        if(o.kol & Dol)
        {
            sort(o.kolizje[3].begin(), o.kolizje[3].end(), PorownajSzczyt);
            for(int i = 0; i < o.kolizje[3].size(); i++)
                if(o.kolizje[3][i]->kol & Gora)
                {
                    Obiekt &o2 = *o.kolizje[3][i];
                    o.p.y = o2.p.y - o.w.y + 0.1f;
                    if(o2.staly)
                        o.v.y *= -o.sp * o2.sp;
                    else
                    {
                        o.v.y = 2 * o2.m * o2.v.y / (o.m + o2.m) + (o.m - o2.m) / (o.m + o2.m) * o2.v.y;
                        o.v.y *= o.sp * o2.sp;
                    }
                    o.v.x -= o.v.x * o.t * o2.t;
                    o.kolizje[3].resize(i + 1);
                    o.wLocie = false;
                }
        }
    }

    //obiekty = tmp;
}
