#ifndef LEWEL_H
#define LEWEL_H

#include "Kolce.h"
#include "Serduszko.h"
#include "Skrzynka.h"
#include "Przeciwnik.h"
#include <string>
using namespace std;

class Lewel
{
    vector<Platforma> platformy;
    vector<Kolce> kolce;
    vector<Skrzynka> skrzynki;
    vector<Serduszko> serduszka;
    vector<Przeciwnik> przeciwnicy;

    Al::Image tlo;

    Wektor2D bohater;

    Obiekt meta;

    string nazwa;

public:
    Obiekt Meta() { return meta; }

    Wektor2D PozBohatera();

    void Laduj(const char *nazwa);

    void Rysuj();

    void Aktualizuj();

    ~Lewel();
};

#endif // LEWEL_H
