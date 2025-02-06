#ifndef STRZALA_H_INCLUDED
#define STRZALA_H_INCLUDED

class Strzala
{
    Obiekt *fizObiekt;
    int ident;

    bool doWyrzucenia;

public:
    static Al::Image obraz;

    Strzala(Wektor2D p, Wektor2D v);

    bool Aktualizuj();

    void Rysuj();
};

#endif // STRZALA_H_INCLUDED
