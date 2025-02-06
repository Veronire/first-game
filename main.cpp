#include "Globalne.h"
#include "Fizyka.h"
#include "Gra.h"
#include "Menu.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

float swiatX = 0.f, swiatY = 0.f; //rozmiary swiata gry
float kameraX = 0.f, kameraY = 0.f;
Stan stanGry;

Al::Window *window;
vector<pair<string, string> > nazwyLeweli;

void Init()
{
    al_init();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(200);
}

bool Wczytaj(istream &plik, string &s)
{
    while(!plik.eof())
    {
        getline(plik, s);
        if(s != "") return true;
    }
    return false;
}

void LadujLewele()
{
    ifstream plik("dane/lewele.txt");
    string tmp1, tmp2;
    while(!plik.eof())
    {
        if(!Wczytaj(plik, tmp1) || !Wczytaj(plik, tmp2)) break;
        nazwyLeweli.push_back(make_pair(tmp1, tmp2));
    }
    plik.close();
}

int main()
{
    Init();
    LadujLewele();
    Al::Window window(800, 600, "Gra");
    ::window = &window;
    int lewel=1;
    Kolce::obraz.Load("dane/obrazki/schowane_kolce.png");
    Kolce::wysunietyObraz.Load("dane/obrazki/wysuniete_kolce.png");
    Kolce::skrzypniecie.Load("dane/dzwieki/skrzypniecie.wav");
    Skrzynka::obraz.Load("dane/obrazki/skrzynka.png");
    Serduszko::obraz.Load("dane/obrazki/serduszko.png");
    Strzala::obraz.Load("dane/obrazki/strzala.png");
    Al::Button::LoadResources();

    Gra gra;
    Menu menu;
    menu.Rysuj();

    bool rysuj = false;
    bool gramy = false;

    while(true)
    {
        ALLEGRO_EVENT event = window.GetEvent();
        if(event.type == ALLEGRO_EVENT_TIMER) rysuj = true;
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) break;
        if(gramy)
        {
            int stan = gra.SprawdzEvent(event);
            if(stan == 1)
            {
                Al::Sample::StopAll();
                if(!gra.Awansuj())
                {
                    gramy = false;
                    window.HideGUI(false);
                    menu.GrajMuzyke();
                }
            }
            else if(stan == -1)
            {
                Al::Sample::StopAll();
                gramy = false;
                window.UngrabMouse();
                window.HideGUI(false);
                menu.GrajMuzyke();
            }
            if(rysuj && window.NoEvents()) gra.Rysuj();
        }
        else
        {
            int wybor = menu.Wybor();
            if(wybor > -1)
            {
                gramy = true;
                window.HideGUI(true);
                Al::Sample::StopAll();
                gra.LadujLewel(wybor);
            }
            else if(wybor == -1) break;

            if(window.NoEvents()) menu.Rysuj();
        }
    }

    Platforma::obraz.Destroy();
    Kolce::obraz.Destroy();
    Kolce::wysunietyObraz.Destroy();
    Kolce::skrzypniecie.Destroy();
    Skrzynka::obraz.Destroy();
    Serduszko::obraz.Destroy();
    Strzala::obraz.Destroy();
    Al::Button::DestroyResources();
}
