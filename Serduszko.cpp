#include "Globalne.h"
#include "Fizyka.h"
#include "Serduszko.h"

Al::Image Serduszko::obraz;

void Serduszko::Tworz(float x, float y)
{
	wykorzystano=false;
    Obiekt o("serduszko");
    o.p = Wektor2D(x, y);
    o.w = Wektor2D(obraz.Width(), obraz.Height());
    o.kol=0;
    o.staly = true;
    ident = Fizyka.Dodaj(o);
    fizObiekt = &Fizyka[ident];
}

void Serduszko::Rysuj()
{
	if (!wykorzystano)
        obraz.Draw(fizObiekt->p.x - kameraX, fizObiekt->p.y - kameraY);
}

void Serduszko::Aktualizuj()
{
    if(!wykorzystano)
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < fizObiekt->kolizje[i].size(); j++)
                if(fizObiekt->kolizje[i][j]->nazwa == "Czlowiek")
                {
                    wykorzystano = true;
                    Fizyka.Usun(ident);
                }
}
