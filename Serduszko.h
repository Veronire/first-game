#ifndef SERDUSZKO_H
#define SERDUSZKO_H

class Serduszko
{
    Obiekt *fizObiekt;

    int ident;
    bool wykorzystano;

public:
    Serduszko() { fizObiekt = NULL; }

    Serduszko(float x, float y)
    {
        Tworz(x, y);
    }

    void Tworz(float x, float y);
    void Rysuj();
    void Aktualizuj();

	Obiekt& ObiektFizyczny() { return *fizObiekt; }

    static Al::Image obraz;
};

#endif // SKRZYNKA_H
