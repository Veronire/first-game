#ifndef GRA_H
#define GRA_H

#define MAKS_LEWEL 3
#include "Lewel.h"

class Gra
{
    Lewel lewel;
    int level;

    Czlowiek bohater;
    bool strzelanie;

    Al::Image przegrana;
    Al::Image pauza;

    int licznik;

    string nazwaLewelu;

    Al::Font font;

    vector<string> wstep;

    Al::Sample muzyka;

public:
    Gra();
    ~Gra();

    void LadujLewel(int nr, bool robicWstep = true);
    bool Awansuj();
    string intToStr(int n);
    void Rysuj();

    int SprawdzEvent(ALLEGRO_EVENT event); //jak zwraca true, to trzeba konczyc
};

#endif // GRA_H
