#include "Globalne.h"
#include "Menu.h"
#include <iostream>
#include <fstream>

void Klik(int button, Al::Control *control)
{
    if(button != 1) return;

    Menu &menu = *reinterpret_cast<Menu*>(control->parent);
    for(int i = 0; i < menu.przyciski.size(); i++)
        if(&menu.przyciski[i] == control)
            menu.wybor = i;
}

void Klik2(int button, Al::Control *control)
{
    if(button != 1) return;

    Menu &menu = *reinterpret_cast<Menu*>(control->parent);
    menu.wybor = -1;
}

Menu::Menu()
{
    wybor = -2;
    przyciski.reserve(1000);
    for(int i = 0; i < nazwyLeweli.size(); i++)
    {
        //cerr << nazwyLeweli[i].first << endl;
        przyciski.push_back(Al::TextButton());
        przyciski.back().Create(nazwyLeweli[i].first);
        przyciski.back().parent = this;
        przyciski.back().click = Klik;
        przyciski.back().Scale(1.3f, 1.3f);
        przyciski.back().MoveTo(100, 200 + i * 50);
        //cerr << nazwyLeweli[i].first << endl;
    }
    for(int i = 0; i < przyciski.size(); i++)
        window->AddControl(&przyciski[i]);

    zakoncz.Create("Koniec");
    zakoncz.MoveTo(650, 520);
    zakoncz.Scale(1.5f, 1.5f);
    zakoncz.click = Klik2;
    zakoncz.parent = this;
    window->AddControl(&zakoncz);

    tlo.Load("dane/obrazki/menu.jpg");
    font.Load("dane/czcionka.ttf", 40);

    muza.Load("dane/dzwieki/menu.ogg");
    muza.Play(true);

    ifstream plik("dane/tytul.txt");
    getline(plik, tytul);
    window->SetTitle(tytul);
    plik.close();
}

Menu::~Menu()
{
    tlo.Destroy();
    muza.Destroy();
//    for(int i = 0; i < przyciski.size(); i++)
//        przyciski[i].Destroy();
}

int Menu::Wybor()
{
    int w = wybor;
    wybor = -2;
    return w;
}

void Menu::Rysuj()
{
    tlo.Draw(0, 0);
    font << tytul << Print(400, 50, al_map_rgb(0, 0, 0), Centre);
    window->Flip();
}
