#include "Window.h"
#include <iostream>

using namespace Al;

Window::Window(int width, int height, string title, bool fullscreen, bool resizable)
{
    Create(width, height, title, fullscreen, resizable);
}

void Window::Create(int width, int height, string title, bool fullscreen, bool resizable)
{
    SetFullscreen(fullscreen);
    if(resizable) SetResizable();

    display = al_create_display(width, height);
    if(!display) cerr << "Nie udało się stworzyć okna" << endl;

    SetTitle(title);

    al_install_keyboard();
    al_install_mouse();

    timer = al_create_timer(1.0 / 30);

    hiddenGUI = false;

    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_keyboard_event_source());

    for(int i = 0; i < ALLEGRO_KEY_MAX; i++) keys[i] = false;
    mouseX = mouseY = 0;

    al_start_timer(timer);
}

Window::~Window()
{
    Destroy();
}

void Window::Destroy()
{
    if(display) al_destroy_display(display);
    if(timer) al_destroy_timer(timer);
    if(queue) al_destroy_event_queue(queue);
    display = NULL;
    timer = NULL;
    queue = NULL;
}

int Window::GetWidth()
{
    return al_get_display_width(display);
}

int Window::GetHeight()
{
    return al_get_display_height(display);
}

void Window::SetSize(int width, int height)
{
    al_resize_display(display, width, height);
}

void Window::SetTitle(string title)
{
    al_set_window_title(display, title.c_str());
}

void Window::SetFullscreen(bool fullscreen)
{
    al_set_new_display_flags(fullscreen ? ALLEGRO_FULLSCREEN_WINDOW : ALLEGRO_WINDOWED);
}

void Window::SetResizable()
{
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
}

void Window::Flip()
{
    if(!hiddenGUI)
        for(int i = 0; i < controls.size(); i++)
            controls[i]->Draw();

    al_flip_display();
}

void Window::SetAsTheTarget()
{
    al_set_target_backbuffer(display);
}

ALLEGRO_BITMAP* Window::GetBackbuffer()
{
    return al_get_backbuffer(display);
}

ALLEGRO_EVENT Window::GetEvent()
{
    ALLEGRO_EVENT event;
    al_wait_for_event(queue, &event);
    if(event.type == ALLEGRO_EVENT_KEY_DOWN) keys[event.keyboard.keycode] = true;
    else if(event.type == ALLEGRO_EVENT_KEY_UP) keys[event.keyboard.keycode] = false;
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        mouseX = event.mouse.x;
        mouseY = event.mouse.y;
    }

    if(!hiddenGUI)
        for(int i = 0; i < controls.size(); i++)
            controls[i]->ProcessEvent(event);

    return event;
}

bool Window::NoEvents()
{
    return al_is_event_queue_empty(queue);
}

bool Window::Key(unsigned code)
{
    if(code < ALLEGRO_KEY_MAX) return keys[code];
    else return false;
}

ALLEGRO_DISPLAY* Window::GetDisplay()
{
    return display;
}

void Window::AddControl(Control *control)
{
    controls.push_back(control);
}

void Window::SetTimer(int ticksPerSecond)
{
    if(timer) al_destroy_timer(timer);

    if(ticksPerSecond)
    {
        timer = al_create_timer(1.f / ticksPerSecond);
        al_start_timer(timer);
    }
}

void Window::HideGUI(bool hide)
{
    hiddenGUI = hide;
}

int Window::MouseX()
{
    return mouseX;
}

int Window::MouseY()
{
    return mouseY;
}

void Window::GrabMouse()
{
    al_grab_mouse(display);
}

void Window::UngrabMouse()
{
    al_ungrab_mouse();
}
