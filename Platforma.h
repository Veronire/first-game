#ifndef PLATFORMA_H
#define PLATFORMA_H

class Platforma
{
protected:
    Obiekt *o;

    float skala;
    int klocki;
    float px;

public:
    static Al::Image obraz;

    Platforma()
    {
        skala = klocki = 0;
        o = NULL;
    }
    Platforma(float x, float y, float szer); //szerokosc

    void Rysuj();
};

#endif // PLATFORMA_H
