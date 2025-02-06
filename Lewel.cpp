#include "Globalne.h"
#include "Fizyka.h"
#include "Lewel.h"
#include <sstream>
#include <fstream>
#include <iostream>

void Lewel::Laduj(const char *lewel)
{
    platformy.clear();
    kolce.clear();
    serduszka.clear();
    skrzynki.clear();
    for(int i = 0; i < przeciwnicy.size(); i++)
        przeciwnicy[i].Niszcz();
    przeciwnicy.clear();
    tlo.Destroy();

    kameraX = kameraY = 0;

    string folder = string("dane/lewele/") + lewel;
    tlo.Load((folder + "/tlo.jpg").c_str());

    Platforma::obraz.Load((folder + "/platforma.png").c_str());

    ifstream plik((folder + "/lewel.txt").c_str());
    string str;
    while(!plik.eof())
    {
        if(plik.peek() == '#') getline(plik, str, '\n');
        else
        {
            getline(plik, str, ';');
            istringstream stream(str);
            stream >> str;
            if(str == "nazwa")
            {
                stream >> str;
                if(str == "=")
                    getline(stream, nazwa);
            }
            else if(str == "rozmiar")
            {
                stream >> str;
                if(str == "=")
                    stream >> swiatX >> swiatY;
                Fizyka.Resetuj();
            }
            else if(str == "bohater")
            {
                stream >> str;
                if(str == "=")
                    stream >> bohater.x >> bohater.y;
            }
            else if(str == "platforma")
            {
                stream >> str;
                if(str == "=")
                {
                    while(!stream.eof())
                    {
                        float x, y, szerokosc;
                        stream >> x >> y >> szerokosc;
                        platformy.push_back(Platforma(x, y, szerokosc));
                    }
                }
            }
            else if(str == "kolce")
            {
                stream >> str;
                if(str == "=")
                {
                    while(!stream.eof())
                    {
                        float x, y, szerokosc;
                        stream >> x >> y >> szerokosc;
                        kolce.push_back(Kolce(x, y, szerokosc));
                    }
                }
            }
            else if(str == "skrzynka")
            {
                stream >> str;
                if(str == "=")
                {
                    while(!stream.eof())
                    {
                        float x, y, szer, wys, masa;
                        stream >> x >> y >> szer >> wys >> masa;
                        skrzynki.push_back(Skrzynka(x, y, szer, wys, masa));
                    }
                }
            }
            else if(str == "serduszko")
            {
                stream >> str;
                if(str == "=")
                {
                    while(!stream.eof())
                    {
                        float x, y;
                        stream >> x >> y;
                        serduszka.push_back(Serduszko(x, y));
                    }
                }
            }
            else if(str == "przeciwnik")
            {
                stream >> str;
                if(str == "=")
                {
                    while(!stream.eof())
                    {
                        float x, y;
                        stream >> x >> y;
                        przeciwnicy.push_back(Przeciwnik());
                        przeciwnicy.back().Tworz(false, "dane/obrazki/przeciwnik", 4, 50, 4);
                        przeciwnicy.back().Ustaw(Wektor2D(x, y));
                    }
                }
            }
            else if(str == "przeciwnik_tchorz")
            {
                stream >> str;
                if(str == "=")
                {
                    while(!stream.eof())
                    {
                        float x, y;
                        stream >> x >> y;
                        przeciwnicy.push_back(Przeciwnik());
                        przeciwnicy.back().Tworz(true, "dane/obrazki/przeciwnik", 4, 50, 8);
                        przeciwnicy.back().Ustaw(Wektor2D(x, y));
                    }
                }
            }
            else if(str == "meta")
            {
                stream >> str;
                if(str == "=")
                {
                    meta = Obiekt("meta");
                    meta.staly = true;
                    meta.kol = 0; //brak kolizji
                    stream >> meta.p.x >> meta.p.y >> meta.w.y;
                    meta.w.y -= meta.p.y;
                    meta.w.x = swiatX - meta.p.x;
                }
            }
        }
    }

    plik.close();
}

Lewel::~Lewel()
{
    tlo.Destroy();
    for(int i = 0; i < przeciwnicy.size(); i++)
        przeciwnicy[i].Niszcz();
}

Wektor2D Lewel::PozBohatera()
{
    return bohater;
}

void Lewel::Rysuj()
{
    tlo.Draw(-kameraX, -kameraY);
    for(int i = 0; i < platformy.size(); i++)
        platformy[i].Rysuj();
    for(int i = 0; i < kolce.size(); i++)
        kolce[i].Rysuj();
    for(int i = 0; i < skrzynki.size(); i++)
        skrzynki[i].Rysuj();
    for(int i = 0; i < serduszka.size(); i++)
        serduszka[i].Rysuj();
    for(int i = 0;i < przeciwnicy.size(); i++)
        przeciwnicy[i].Rysuj();
}

void Lewel::Aktualizuj()
{
    for(int i = 0; i < kolce.size(); i++)
        kolce[i].Aktualizuj();
    for(int i = 0; i < serduszka.size(); i++)
        serduszka[i].Aktualizuj();
    for(int i = 0; i < przeciwnicy.size(); i++)
        przeciwnicy[i].Aktualizuj();
}
