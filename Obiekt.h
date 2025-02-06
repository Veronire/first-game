#ifndef OBIEKT_H
#define OBIEKT_H

#include <string>
#include <queue>
using namespace std;

enum
{
    Lewo = 1,
    Prawo = 2,
    Gora = 4,
    Dol = 8,
};

struct Wektor2D //w formie (przesuniecie x, przesuniecie y)
{
    float x, y;

    Wektor2D() { x = y = 0.f; }
    Wektor2D(float X, float Y) { x = X; y = Y; }

    Wektor2D operator +(Wektor2D v) const { return Wektor2D(x + v.x, y + v.y); }
    Wektor2D operator -(Wektor2D v) const { return Wektor2D(x - v.x, y - v.y); }

    void operator +=(Wektor2D v) { *this = *this + v; }
    void operator -=(Wektor2D v) { *this = *this - v; }

    Wektor2D operator -() const { return Wektor2D(-x, -y); }

    Wektor2D operator *(float w) const { return Wektor2D(x * w, y * w); }
    Wektor2D operator /(float w) const { return Wektor2D(x / w, y / w); }

    void operator *=(float w) { *this = *this * w; }
    void operator /=(float w) { *this = *this / w; }
};

struct Obiekt
{
    Wektor2D p; //pozycja

    Wektor2D w; //wymiary

    Wektor2D v; //predkosc

    float m; //masa

    float sp; //wspolczynnik sprezystosci - wplywa na to jak sie odbijamy - przedzial [0, 1]

    float t; //wspolczynnik tarcia - przedzial [0, 1]

    float op; //opor powietrza

    bool staly; //czy obiekt moze sie ruszac

    int kol;

    string nazwa;

    bool wLocie;

    vector<Obiekt*> kolizje[4];

    void *wlasciciel;

    Obiekt()
    {
        t = op = 0.f;
        sp = m = 1.f;
        wLocie = staly = false;
        kol = 15;
    }

    Obiekt(string Nazwa)
    {
        *this = Obiekt();
        nazwa = Nazwa;
    }
};

int Kolizja(const Obiekt &o1, const Obiekt &o2); //więcej informacji w definicji funkcji

#endif // OBIEKT_H
