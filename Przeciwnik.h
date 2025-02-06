#ifndef PRZECIWNIK_H
#define PRZECIWNIK_H

#include "Czlowiek.h"

class Przeciwnik : public Czlowiek
{
    protected:
        Wektor2D strzal;

        bool strzelanie;

        int licznik;

        bool WymierzStrzale();
        float SprawdzKat(float kat);

        bool tchorzliwy;
        bool ucieczka;

        Al::Sample panika;

    public:
        static Obiekt* bohater;

        Przeciwnik() { stworzony = false; }
        Przeciwnik(bool tchorz, char *folderZObrazkami, int liczbaKlatek, int odstep, int mksHP, float masa = 50.f, float szybkosc = 3.f);

        void Niszcz();

        void Tworz(bool tchorz, char *folderZObrazkami, int liczbaKlatek, int odstep, int mksHP, float masa = 50.f, float szybkosc = 3.f);

        void Aktualizuj();
};

#endif // PRZECIWNIK_H
