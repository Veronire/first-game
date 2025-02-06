#ifndef SKRZYNKA_H
#define SKRZYNKA_H

class Skrzynka
{
    Obiekt *fizObiekt;

public:
    Skrzynka() { fizObiekt = NULL; }

    Skrzynka(float x, float y, float szer, float wys, float masa)
    {
        Tworz(x, y, szer, wys, masa);
    }

    void Tworz(float x, float y, float szer, float wys, float masa);

    void Rysuj();


    static Al::Image obraz;
};

#endif // SKRZYNKA_H
