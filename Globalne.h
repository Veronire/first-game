#ifndef GLOBALNE_H
#define GLOBALNE_H

#include "Allegro.h"
#include <vector>
#include <string>
#include <utility>
using namespace std;

enum Stan
{
    Wstep,
    Rozgrywka,
    Przegrana,
    Pauza,
    Koniec
};

extern float swiatX, swiatY; //rozmiary swiata gry
extern float kameraX, kameraY;
extern Stan stanGry;
extern vector<pair<string, string> > nazwyLeweli;

extern Al::Window *window;

#define FOREACH(i, m) for(i = m.begin(); i != m.end(); i++) if(i->first)

#endif // GLOBALNE_H
