#include "Globalne.h"
#include "Fizyka.h"
#include "Czlowiek.h"
#include "Serduszko.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <set>
using namespace std;

void Czlowiek::WybierzObrazek(int st, int kier)
{
    if(st == stan && kier == kierunek) return;
    stan = st;
    kierunek = kier;
    obrazki[st + Max * kier].Reset();
    if(stan == Bieg || stan == Cofanie) bieg.Play(true, 1.f, 1.f);
}

bool Czlowiek::RuchWLewo()
{
    if((szlaban & 1) || stan >= Atak) return false;
    if(fizObiekt->wLocie)
    {
        WybierzObrazek(stan, Lewo);
        fizObiekt->v.x -= predkosc / 3.f;
        return false;
    }
    else
    {
        fizObiekt->v.x -= predkosc;
        WybierzObrazek(Bieg, Lewo);
        bezruch = false;
        return true;
    }
}

bool Czlowiek::RuchWPrawo()
{
    if((szlaban & 2) || stan >= Atak) return false;
    if(fizObiekt->wLocie)
    {
        WybierzObrazek(stan, Prawo);
        fizObiekt->v.x += predkosc / 3.f;
        return false;
    }
    else
    {
        fizObiekt->v.x += predkosc;
        WybierzObrazek(Bieg, Prawo);
        bezruch = false;
        return true;
    }
}

void Czlowiek::Skok()
{
    if(stan >= Atak || stan == Cofanie) return;
    if(fizObiekt->wLocie) return;
    fizObiekt->v.y -= 900.f / fizObiekt->m;
    fizObiekt->v.x *= 1.5f;
}

void Czlowiek::CofajWLewo()
{
    int kier = kierunek;
    if(RuchWLewo() && kier != kierunek) WybierzObrazek(Cofanie, Prawo);
}

void Czlowiek::CofajWPrawo()
{
    int kier = kierunek;
    if(RuchWPrawo() && kier != kierunek) WybierzObrazek(Cofanie, Lewo);
}

void Czlowiek::Rysuj()
{
    if(HP <= 0)
    {
        if(gasniecie > 0)
        {
            if(kierunek == Prawo)
            {
                Al::DrawInfo info = lukInfo[12];
                info.px += fizObiekt->p.x - kameraX;
                info.py += fizObiekt->p.y - kameraY;
                lukPrawy.Draw(info + Al::Colour(255, 255, 255, gasniecie));
            }
            trup[kierunek].Draw(Al::DrawInfo(fizObiekt->p.x - kameraX, fizObiekt->p.y - kameraY) + Al::Colour(255, 255, 255, gasniecie));
            if(kierunek == Lewo)
            {
                Al::DrawInfo info = lukInfo[12];
                info.cx = lukLewy.Width() - info.cx;
                info.px += fizObiekt->p.x - kameraX - 3.f;
                info.py += fizObiekt->p.y - kameraY;
                info.ang -= M_PI / 2.f;
                lukLewy.Draw(info + Al::Colour(255, 255, 255, gasniecie));
            }
        }
    }
    else if(stan < Atak)
    {
        if(kierunek == Prawo)
        {
            Al::DrawInfo info = lukInfo[stan + obrazki[stan + kierunek * Max].GetFrame()];
            if(stan == Cofanie) info = lukInfo[stan + 4 + obrazki[stan + kierunek * Max].GetFrame()];
            info.px += fizObiekt->p.x - kameraX;
            info.py += fizObiekt->p.y - kameraY;
            lukPrawy.Draw(info);
        }
        obrazki[stan + kierunek * Max].Draw(fizObiekt->p.x - kameraX, fizObiekt->p.y - kameraY);
        if(kierunek == Lewo)
        {
            Al::DrawInfo info = lukInfo[stan + obrazki[stan + kierunek * Max].GetFrame()];
            if(stan == Cofanie) info = lukInfo[stan + 4 + obrazki[stan + kierunek * Max].GetFrame()];
            info.cx = lukLewy.Width() - info.cx;
            info.px += fizObiekt->p.x - kameraX - 3.f;
            info.py += fizObiekt->p.y - kameraY;
            info.ang -= M_PI / 2.f;
            lukLewy.Draw(info);
        }
    }
    else if(stan == Strzelanie)
    {
        Wektor2D p = fizObiekt->p - Wektor2D(kameraX, kameraY + 11), v = naciagStrzaly;
        if(v.x == 0.f) v.x = 0.000001f;
        float kat = atan(v.y / v.x);
        if(kierunek == Prawo)
        {
            lewaReka[1].Draw(Al::DrawInfo(p.x + 15, p.y + 26) + Al::Centre(15, 26) + Al::Rotation(kat));
            glowa[1].Draw(Al::DrawInfo(p.x + 21, p.y + 22) + Al::Centre(21, 22) + Al::Rotation(kat));
            cialo[1].Draw(Al::DrawInfo(p.x, p.y));
            prawaReka[1].Draw(Al::DrawInfo(p.x + 15, p.y + 26) + Al::Centre(15, 26) + Al::Rotation(kat));
        }
        else
        {
            prawaReka[0].Draw(Al::DrawInfo(p.x + 24, p.y + 26) + Al::Centre(24, 26) + Al::Rotation(kat));
            glowa[0].Draw(Al::DrawInfo(p.x + 21, p.y + 22) + Al::Centre(21, 22) + Al::Rotation(kat));
            cialo[0].Draw(Al::DrawInfo(p.x, p.y));
            lewaReka[0].Draw(Al::DrawInfo(p.x + 24, p.y + 26) + Al::Centre(24 + 25, 26) + Al::Rotation(kat));
        }
    }
    else
        obrazki[Bezruch + kierunek * Max].Draw(fizObiekt->p.x - kameraX, fizObiekt->p.y - kameraY);
    for(int i = 0; i < strzaly.size(); i++)
        strzaly[i].Rysuj();
}

bool Czlowiek::Aktualizuj()
{
    for(int i = 0; i < strzaly.size(); i++)
        if(!strzaly[i].Aktualizuj())
        {
            strzaly.erase(strzaly.begin() + i);
            i--;
        }

    if(HP <= 0)
    {
        if(gasniecie == 255)
        {
            bieg.Stop();
            umieranie.Play(false);
        }
        if(gasniecie > 0)
        {
            gasniecie -= 4;
            if(gasniecie < 0) Fizyka.Usun(fizIdent);
        }
        return false;
    }
    if (fizObiekt->wLocie)
    {
        WybierzObrazek(Lot, kierunek);
        bezruch = false;
    }

    szlaban = 0;

    if(bezruch && stan < Atak) WybierzObrazek(Bezruch, kierunek);
    if(stan < Atak) obrazki[stan + kierunek * Max].Update();
    if(stan != Bieg) bieg.Stop();
    else if(stan == Obrona)
    {
        czasObrony++;
        if(czasObrony > 90)
            WybierzObrazek(Bezruch, kierunek);
    }
    else if(stan == Atak)
    {
        czasDoCiosu--;
        if(czasDoCiosu <= 0)
        {
            cerr << "atakujemy" << endl;
            atakowany->PrzyjmijAtak();
            WybierzObrazek(Bezruch, kierunek);
        }
    }
    else if(stan == Kontratak || stan == Zbijanie)
    {
        czasDoNormalnosci--;
        if(czasDoNormalnosci <= 0)
            WybierzObrazek(Bezruch, kierunek);
    }

    set<Obiekt*> czarnaLista;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < fizObiekt->kolizje[i].size(); j++)
        {
            Obiekt &o = *fizObiekt->kolizje[i][j];

            if(i == 3 && (o.kol & Gora))
            {
                Wektor2D p = fizObiekt->p, w = fizObiekt->w;
                if((stan == Bezruch || stan == Cofanie) && min(p.x + w.x, o.p.x + o.w.x) - max(p.x, o.p.x) < w.x / 2.f)
                    if(p.x < o.p.x) CofajWPrawo();
                    else if(p.x > o.p.x) CofajWLewo();
            }

            if((o.nazwa == "kolce" && i == 3) || (o.nazwa == "schowane kolce" && fizObiekt->p.y + fizObiekt->w.y <= o.p.y + o.w.y + 15.f)
                                                   || o.nazwa == "Dolna granica")
                HP = 0;
            if(czarnaLista.find(&o) != czarnaLista.end()) continue;
            else if(o.nazwa == "strzała")
            {
                HP--;
                if(i < 2) fizObiekt->v.x += o.v.x / 3.f;
            }
            else if(o.nazwa == "serduszko")
                HP = min(maksHP, HP + 1);
            else if(i == 0 && o.nazwa == "Czlowiek")
                szlaban |= 1;
            else if(i == 1 && o.nazwa == "Czlowiek")
                szlaban |= 2;
            czarnaLista.insert(&o);
        }

    bezruch = true;
    return true;
}

Czlowiek::Czlowiek(char *folderZObrazkami, int liczbaKlatek, int odstep, int mksHP, float masa, float szybkosc)
{
    stworzony = false;
    Tworz(folderZObrazkami, liczbaKlatek, odstep, mksHP, masa, szybkosc);
}

void Czlowiek::Niszcz()
{
    if(!stworzony) return;
    //stworzony = false;
    for(int i = 0; i < Max * 2; i++)
        obrazki[i].Destroy();
    for(int i = 0; i < 2; i++)
    {
        trup[i].Destroy();
        cialo[i].Destroy();
        glowa[i].Destroy();
        lewaReka[i].Destroy();
        prawaReka[i].Destroy();
    }
    lukLewy.Destroy();
    lukPrawy.Destroy();
    bieg.Destroy();
    strzal.Destroy();
    umieranie.Destroy();
    Fizyka.Usun(fizIdent);
}

void Czlowiek::Tworz(char *folderZObrazkami, int liczbaKlatek, int odstep, int mksHP, float masa, float szybkosc)
{
    //Niszcz();
    stworzony = true;

    string str(folderZObrazkami);
    str += '/';
    obrazki[Bezruch].Load((str + "bezruch_lewo.png").c_str(), 1, 1);
    obrazki[Bezruch + Max].Load((str + "bezruch_prawo.png").c_str(), 1, 1);
    obrazki[Lot].Load((str + "skok_lewo.png").c_str(), 1, 1);
    obrazki[Lot + Max].Load((str + "skok_prawo.png").c_str(), 1, 1);
    obrazki[Bieg].Load((str + "ruch_lewo.png").c_str(), 5, 3);
    obrazki[Bieg + Max].Load((str + "ruch_prawo.png").c_str(), 5, 3);
    obrazki[Cofanie].Load((str + "cofanie_lewo.png").c_str(), 5, 3);
    obrazki[Cofanie + Max].Load((str + "cofanie_prawo.png").c_str(), 5, 3);
    trup[0].Load((str + "trup_lewo.png").c_str());
    trup[1].Load((str + "trup_prawo.png").c_str());
    cialo[0].Load((str + "cialo_lewo.png").c_str());
    glowa[0].Load((str + "glowa_lewo.png").c_str());
    lewaReka[0].Load((str + "lewa_reka_lewo.png").c_str());
    prawaReka[0].Load((str + "prawa_reka_lewo.png").c_str());
    cialo[1].Load((str + "cialo_prawo.png").c_str());
    glowa[1].Load((str + "glowa_prawo.png").c_str());
    lewaReka[1].Load((str + "lewa_reka_prawo.png").c_str());
    prawaReka[1].Load((str + "prawa_reka_prawo.png").c_str());
    lukLewy.Load("dane/obrazki/luk_lewo.png");
    lukPrawy.Load("dane/obrazki/luk_prawo.png");
    stan = Bezruch;
    kierunek = Prawo;
    bezruch = true;
    szlaban = 0;
    gasniecie = 255;

    bieg.Load("dane/dzwieki/bieg.wav");
    strzal.Load("dane/dzwieki/strzala.wav");
    umieranie.Load("dane/dzwieki/umieranie.wav");

    Obiekt o("Czlowiek");
    o.w = Wektor2D(obrazki[Bezruch].Width(), obrazki[Bezruch].Height());
    o.m = masa;
    o.t = 0.7f;
    o.sp = 0.2f;
    o.op = 0.3f;
    o.wlasciciel = this;
    fizIdent = Fizyka.Dodaj(o);
    fizObiekt = &Fizyka[fizIdent];
    maksHP = mksHP;
    HP = (maksHP + 1) / 2;
    predkosc = szybkosc;
    strzaly.clear();

    ifstream plik("dane/obrazki/luk.txt");
    plik >> lukSrodek.cx >> lukSrodek.cy;
    for(int i = 0; i < 13; i++)
    {
        float px, py, kat;
        plik >> px >> py >> kat;
        kat *= M_PI / 180.f;
        lukInfo[i] + Al::Rotation(kat) + Al::Position(px, py) + lukSrodek;
    }
    plik.close();
}

void Czlowiek::Ustaw(Wektor2D pozycja)
{
    fizObiekt->p = pozycja;
}

bool Czlowiek::NalozStrzale()
{
    if(HP <= 0 || fizObiekt->wLocie || stan >= Atak) return false;
    naciagStrzaly = zmiana = Wektor2D();
    stan = Strzelanie;
    return true;
}

bool Czlowiek::NaciagajStrzale(float dx, float dy)
{
    if(HP <= 0 || stan != Strzelanie) return false;
    zmiana -= Wektor2D(dx, dy) / 3.5f;
    naciagStrzaly = zmiana;
    float f = sqrt(naciagStrzaly.x * naciagStrzaly.x + naciagStrzaly.y * naciagStrzaly.y);
    if(f == 0.f) f = 1.f;
    else f = maxNaciag / f;
    if(f < 1.f)
        naciagStrzaly *= f;
    if(naciagStrzaly.x > 0.f) kierunek = Prawo;
    else kierunek = Lewo;
}

void Czlowiek::PuscStrzale()
{
    strzaly.push_back(Strzala(fizObiekt->p + fizObiekt->w / 2.f, naciagStrzaly));
    WybierzObrazek(Bezruch, kierunek);
    strzal.Play(false, 1.f, 2.f);
    //cerr << fizObiekt->nazwa << " strzela: " << naciagStrzaly.x << " " << naciagStrzaly.y << endl;
}

void Czlowiek::Atakuj(int typ)
{
    if(typ == Kopniak)
        if(stan == Kontratak)
            czasDoCiosu = 15;
        else return;
    else czasDoCiosu = 30;
    stan = Atak;
    typAtaku = typ;

    for(int i = 0; i < fizObiekt->kolizje[kierunek].size(); i++)
        if(fizObiekt->kolizje[kierunek][i]->nazwa == "Czlowiek")
        {
            atakowany = reinterpret_cast<Czlowiek*>(fizObiekt->kolizje[kierunek][i]->wlasciciel);
            atakowany->PrzygotujSieDoAtaku();
            return;
        }

    WybierzObrazek(Bezruch, kierunek); //jesli nie udalo sie znalezc przeciwnika, ktorego mozna walnac to dajemy spokoj
}

void Czlowiek::PrzygotujSieDoAtaku()
{
    stan = Atakowany;
}

void Czlowiek::Bron()
{
    if(stan == Obrona) return;
    stan = Obrona;
    czasObrony = 0;
}

void Czlowiek::PrzyjmijAtak()
{
    if(stan != Obrona)
    {
        cerr << "Auć!" << endl;
        HP--;
        cerr << HP << endl;
        stan = Zbijanie;
        czasObrony = 30;
    }
    else if(czasObrony > 30)
    {
        stan = Zbijanie;
        czasObrony = 30;
    }
    else
    {
        stan = Kontratak;
        czasObrony = 15;
    }
}
