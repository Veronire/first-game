#ifndef CONTROL_H
#define CONTROL_H

namespace Al
{
    class Control
    {
        protected:
            int x, y;

            int w, h;

            bool UnderCursor(int mouseX, int mouseY)
            {
                return x <= mouseX && x + w >= mouseX && y <= mouseY && y + h >= mouseY;
            }

        public:
            virtual void Draw() = 0;

            virtual void ProcessEvent(const ALLEGRO_EVENT &event) = 0;

            void (*click)(int button, Control *control);

            void *parent;

            virtual ~Control() { }
    };
};

#endif // CONTROL_H
