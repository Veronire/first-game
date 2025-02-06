#ifndef WINDOW_H
#define WINDOW_H

#include <allegro5/allegro.h>
#include <string>
#include <vector>
#include "Control.h"
using namespace std;

namespace Al
{
    enum
    {
        Windowed,
        Fullscreen
    };

    class Window
    {
        ALLEGRO_DISPLAY *display;
        ALLEGRO_TIMER *timer;
        ALLEGRO_EVENT_QUEUE *queue;

        bool keys[ALLEGRO_KEY_MAX];

        vector<Control*> controls;

        bool hiddenGUI;

        int mouseX, mouseY;

    public:
        Window() { display = NULL; timer = NULL; queue = NULL; hiddenGUI = false; }

        Window(int width, int height, string title = "", bool foolscreen = false, bool resizable = false);
        void Create(int width, int height, string title = "", bool fullscreen = false, bool resizable = false);

        ~Window();
        void Destroy();

        int GetWidth();
        int GetHeight();

        void SetSize(int width, int height);
        void SetTitle(string title);
        void SetFullscreen(bool fullscreen);
        void SetResizable();

        void SetTimer(int ticksPerSecond); //0 = no timers

        void Flip();

        void SetAsTheTarget();

        ALLEGRO_EVENT GetEvent();
        bool NoEvents();
        bool Key(unsigned code);

        int MouseX();
        int MouseY();

        void AddControl(Control *control);

        void HideGUI(bool hide);

        ALLEGRO_BITMAP* GetBackbuffer();
        ALLEGRO_DISPLAY* GetDisplay();

        void GrabMouse();
        static void UngrabMouse();
    };
}

#endif // WINDOW_H
