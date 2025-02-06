#ifndef MENU_H
#define MENU_H

void Klik(int button, Al::Control *control);

class Menu
{
    private:
        vector<Al::TextButton> przyciski;
        Al::TextButton zakoncz;

        Al::Image tlo;
        Al::Font font;
        Al::Sample muza;
        string tytul;

        int wybor;

    public:
        friend void Klik(int button, Al::Control *control);
        friend void Klik2(int button, Al::Control *control);

        Menu();

        ~Menu();

        int Wybor();

        void Rysuj();

        void GrajMuzyke() { muza.Play(true); }
};

#endif // MENU_H
