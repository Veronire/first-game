#include "Globalne.h"
#include "Fizyka.h"
#include "Gra.h"
#include <iostream>
#include <fstream>
#include <allegro5/allegro_primitives.h>
using namespace std;

Gra::Gra()
{
    przegrana.Load("dane/obrazki/dialog_przegrana.png");
    pauza.Load("dane/obrazki/dialog_pauza.png");
    level=1;
    font.Load("dane/czcionka.ttf", 25);
    //Awansuj();
}

Gra::~Gra()
{
    przegrana.Destroy();
    pauza.Destroy();
    bohater.Niszcz();
    font.Destroy();
    muzyka.Destroy();
}

string Gra::intToStr(int n)
{
     string tmp;
     if(n < 0) {
          tmp = "-";
          n = -n;
     }
     if(n > 9)
          tmp += intToStr(n / 10);
     tmp += n % 10 + 48;
     return tmp;
}

void Gra::Rysuj()
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    if(stanGry == Wstep)
        for(int i = 0; i < wstep.size(); i++)
            font << wstep[i] << Print(400, 30 + i * 30, al_map_rgb(255, 255, 255), Centre);
    else
    {
        lewel.Rysuj();

        bohater.Rysuj();
        for(int i = 0; i < bohater.Zycia(); i++)
            Serduszko::obraz.Draw(Al::DrawInfo(30.f + Serduszko::obraz.Width() / 2.f * i, 30.f) + Al::Scale(0.5f, 0.5f));
        if(strzelanie)
        {
            Wektor2D p = bohater.ObiektFizyczny().p + bohater.ObiektFizyczny().w / 2.f - Wektor2D(kameraX, kameraY + 9);
            al_draw_line(p.x, p.y, p.x - bohater.NaciagStrzaly().x, p.y - bohater.NaciagStrzaly().y, al_map_rgb(0, 0, 0), 1);
        }
        if(stanGry == Przegrana)
            przegrana.Draw((window->GetWidth() - przegrana.Width()) / 2, (window->GetHeight() - przegrana.Height()) / 2);
        else if(stanGry == Pauza)
            pauza.Draw((window->GetWidth() - pauza.Width()) / 2, (window->GetHeight() - pauza.Height()) / 2);
        else if(stanGry == Koniec)
            al_draw_filled_rectangle(0, 0, window->GetWidth(), window->GetHeight(), al_map_rgba(0, 0, 0, licznik));
    }

    window->Flip();
}

void Gra::LadujLewel(int nr, bool robicWstep)
{
    level = nr;
    const char *nazwa = nazwyLeweli[nr].second.c_str();
    al_clear_to_color(al_map_rgb(0, 0, 0));
    font << "Ładowanie, proszę czekać..." << Print(400, 290, al_map_rgb(255, 255, 155), Centre);
    window->Flip();

    bohater.Niszcz();
    lewel.Laduj(nazwa);
    bohater.Tworz("dane/obrazki/bohater", 4, 50, 6);
    bohater.Ustaw(lewel.PozBohatera());
    Przeciwnik::bohater = &bohater.ObiektFizyczny();
    strzelanie = false;
    nazwaLewelu = nazwa;
    licznik = -1;

    string str = "dane/lewele/", tmp;
    str += nazwa;
    ifstream plik((str + "/wstep.txt").c_str());
    wstep.clear();
    if(!plik.fail())
        while(true)
        {
            getline(plik, tmp);
            wstep.push_back(tmp);
            if(plik.eof()) break;
        }
    else cerr << "nie udało się otworzyć " << str + "wstep.txt" << endl;
    wstep.push_back("");
    wstep.push_back("Naciśnij dowolny klawisz");
    plik.close();

    muzyka.Load((str + "/muza.ogg").c_str());

    stanGry = robicWstep ? Wstep : Rozgrywka;
    if(stanGry == Rozgrywka) muzyka.Play(true);

    while(!window->NoEvents()) window->GetEvent();
    window->GrabMouse();
}

bool Gra::Awansuj(){
	if(level >= nazwyLeweli.size() - 1)
		return false;
	LadujLewel(level + 1);
	return true;
}

int Gra::SprawdzEvent(ALLEGRO_EVENT event)
{
    switch(event.type)
    {
        case ALLEGRO_EVENT_TIMER:
            if(stanGry == Rozgrywka)
            {
                if(window->Key(ALLEGRO_KEY_A)) bohater.RuchWLewo();
                if(window->Key(ALLEGRO_KEY_D)) bohater.RuchWPrawo();
                Fizyka.Aktualizuj();

                if(licznik < 0 && !bohater.Aktualizuj()) licznik = 2;

                Wektor2D p = bohater.ObiektFizyczny().p, w = bohater.ObiektFizyczny().w;


                //Sprawdzenie czy dotarlismy do mety
                Obiekt m = lewel.Meta();
                if(min(p.x + w.x, m.p.x + m.w.x) > max(p.x, m.p.x) &&
                   min(p.y + w.y, m.p.y + m.w.y) > max(p.y, m.p.y))
                   {
                       stanGry = Koniec;
                       licznik = 1;
                   }

                //Przesuwanie kamery
                const float prog = 340.f;
               if(p.x - kameraX < prog) kameraX = max(p.x - prog, 0.f);
                else if(p.x + w.x - kameraX > window->GetWidth() - prog)
                    kameraX = min(p.x + w.x - window->GetWidth() + prog, swiatX - window->GetWidth());
                if(p.y - kameraY < prog / 2.f)
                {
                    kameraY = max(p.y - prog / 2.f, 0.f);
                    //cerr << "za wysoko" << endl;
                }
                else if(p.y + w.y - kameraY > window->GetHeight() - prog / 2.f)
                {
                    kameraY = min(p.y + w.y - window->GetHeight() + prog / 2.f, swiatY - window->GetHeight());
                    //cerr << (p.y + w.y - window->GetHeight() + prog) << endl;
                }

                lewel.Aktualizuj();
                if(licznik-- == 0)
                {
                    stanGry = Przegrana;
                    window->UngrabMouse();
                }
            }
            else if(stanGry == Koniec)
            {
                licznik += 4;
                if(licznik > 255) return 1;
            }
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE: return -1;
        case ALLEGRO_EVENT_KEY_DOWN:
            if(stanGry == Wstep)
            {
                stanGry = Rozgrywka;
                muzyka.Play(true);
            }
            else switch(event.keyboard.keycode)
            {
                case ALLEGRO_KEY_ESCAPE:
                    if(stanGry == Pauza) return -1;
                    else if(stanGry == Rozgrywka)
                    {
                        stanGry = Pauza;
                        window->UngrabMouse();
                    }
                    break;
                case ALLEGRO_KEY_SPACE:
                    if(stanGry == Rozgrywka) bohater.Skok();
                    else if(stanGry == Pauza)
                    {
                        stanGry = Rozgrywka;
                        window->GrabMouse();
                    }
                    else if(stanGry == Przegrana)
                        LadujLewel(level, false);
                    break;
                /*case ALLEGRO_KEY_Q:
                    if(stanGry == Rozgrywka)
                        bohater.Atakuj(Czlowiek::Noz);
                    break;
                case ALLEGRO_KEY_W:
                    if(stanGry == Rozgrywka)
                        bohater.Atakuj(Czlowiek::Magia);
                    break;
                case ALLEGRO_KEY_E:
                    if(stanGry == Rozgrywka)
                        bohater.Atakuj(Czlowiek::Kopniak);
                    break;*/
                case ALLEGRO_KEY_BACKSPACE:
                    if(stanGry == Rozgrywka)
                    bohater.HP = 0;
                    break;
            }
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            if(stanGry == Rozgrywka)
                strzelanie = bohater.NalozStrzale();
            break;
        case ALLEGRO_EVENT_MOUSE_AXES:
            if(strzelanie)
                if(stanGry == Rozgrywka)
                    bohater.NaciagajStrzale(event.mouse.dx, event.mouse.dy);
                else
                {
                    bohater.PuscStrzale();
                    strzelanie = false;
                }
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            if(strzelanie)
            {
                bohater.PuscStrzale();
                strzelanie = false;
            }
    }
    return 0;
}
