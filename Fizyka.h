#ifndef FIZYKA_H
#define FIZYKA_H

#include "Obiekt.h"
#include <queue>
#include <vector>
using namespace std;


class Fiz
{
    Fiz();

    vector<pair<bool, Obiekt> > obiekty;
    queue<int> wolne;
    int n; //najmniejszy nie uzyty identyfikator

    float g; //grawitacja
    float w; //wspolczynnik, przez ktory mnozymy predkosc

    void DodajGranice();

public:
    static Fiz& Get()
    {
        static Fiz fizyka;
        return fizyka;
    }

    Obiekt& operator [](int k) { return obiekty[k].second; }

    int Dodaj(Obiekt o) ;
    void Usun(int k);

    void Resetuj();

    void UstawGrawitacje(float G) { g = G; }
    float Grawitacja() { return g; }

    float Wspolczynnik() { return w; }

    void Aktualizuj();
};

#define Fizyka Fiz::Get()

#endif // FIZYKA_H
