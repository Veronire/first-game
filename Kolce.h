#ifndef KOLCE_H
#define KOLCE_H

#include "Platforma.h"

class Kolce : public Platforma
{
    bool wysuniete;

    float pozY;

    static const float tol = 8.f;

public:
    static Al::Image obraz;
    static Al::Image wysunietyObraz;
    static Al::Sample skrzypniecie;

    Kolce();

    Kolce(float x, float y, float szer);

    void Aktualizuj();

    void Rysuj();
};

#endif // KOLCE_H
