#ifndef CZLOWIEK_H
#define CZLOWIEK_H

#include "Strzala.h"
#include <vector>

class Czlowiek
{
    protected:
        enum
        {
            Lewo,
            Prawo
        };

        enum
        {
            Bezruch,
            Lot,
            Bieg,
            Cofanie,
            Atak,
            Atakowany,
            Obrona,
            Kontratak,
            Zbijanie,
            Strzelanie
        };

        static const int Max = 4;

        int fizIdent;

        Obiekt *fizObiekt;

        Al::AnimatedImage obrazki[Max * 2];
        Al::Image trup[2];
        Al::Image cialo[2];
        Al::Image glowa[2];
        Al::Image lewaReka[2];
        Al::Image prawaReka[2];

        Al::Image lukLewy, lukPrawy;
        Al::Centre lukSrodek;
        Al::DrawInfo lukInfo[13];

        Al::Sample bieg;
        Al::Sample strzal;
        Al::Sample umieranie;

        /*Al::Image czlek_stoi;
        Al::Image czlek_L1;
        Al::Image czlek_L2;
        Al::Image czlek_P1;
        Al::Image czlek_P2;
        Al::Image czlek_skacze;*/

        int kierunek;
        int stan;
        bool bezruch;
        int szlaban;
        int gasniecie;

        int czasDoCiosu;
        int czasObrony;
        int czasDoNormalnosci;
        int typAtaku;
        Czlowiek *atakowany;

        void WybierzObrazek(int st, int kier); //st - stan, kier - kierunek

        Wektor2D zmiana;
        Wektor2D naciagStrzaly;
        static const float maxNaciag = 60.f;

        vector<Strzala> strzaly;

        void CofajWLewo();
        void CofajWPrawo();

        bool stworzony;

    public:
        enum
        {
            Noz,
            Magia,
            Kopniak
        };

        float predkosc;

        int maksHP;

        int HP;

        bool RuchWLewo();
        bool RuchWPrawo();
        void Skok();

        bool NalozStrzale();
        bool NaciagajStrzale(float dx, float dy);
        void PuscStrzale();

        void Atakuj(int typ);
        void Bron();
        void PrzygotujSieDoAtaku();
        void PrzyjmijAtak();

        bool Aktualizuj();

        void Rysuj();

        Czlowiek() { stworzony = false; }
        //odstep - czas przypadajacy na jedna klatke
        Czlowiek(char *folderZObrazkami, int liczbaKlatek, int odstep, int mksHP, float masa = 50.f, float szybkosc = 3.f);

        void Niszcz();

        void Tworz(char *folderZObrazkami, int liczbaKlatek, int odstep, int mksHP, float masa = 50.f, float szybkosc = 3.f);

        void Ustaw(Wektor2D pozycja);

        int Zycia() { return HP; }

        Obiekt& ObiektFizyczny() { return *fizObiekt; }

        Wektor2D NaciagStrzaly() { return stan == Strzelanie ? naciagStrzaly : Wektor2D(); }
};

#endif // CZLOWIEK_H
