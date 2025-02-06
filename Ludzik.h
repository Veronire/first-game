#ifndef LUDZIK_H
#define LUDZIK_H

#include "Obiekt.h"

class Ludzik
{
    Object ob;
    int obIdent; //identyfikator obiektu
	 int zycie;
    int hp;

    Al::AnimatedImage obrazek;

    static const float marsz = 10.f;

public:
    void Tworz();

    void Rysuj();

    bool Aktualizuj(); //zwraca false, jak ludzik sie zabije
};

#endif // LUDZIK_H
