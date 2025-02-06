#ifndef BUTTON_H
#define BUTTON_H

#include "Control.h"

namespace Al
{
    class Button : public Control
    {
        protected:
            Al::Image myImg;
            Al::Image *img;

            static const int dark = 230;

            bool underCursor;

            static Al::Image background;
            static Al::Font font;

        public:
            Button() { click = NULL; img = &myImg; w = h = 0; }

            Button(const char *pathToImage, int posX, int posY)
            {
                Button();
                Create(pathToImage, posX, posY);
            }

            ~Button()
            {
                myImg.Destroy();
            }

            void Create(const char *pathToImage, int posX, int posY);

            void SetImage(Image &image);

            void Resize(int sizeX, int sizeY);
            void Scale(float scaleX, float scaleY);

            void MoveTo(int posX, int posY);
            void Move(int dx, int dy);

            void Draw();

            void ProcessEvent(const ALLEGRO_EVENT &event);

            static void LoadResources();
            static void DestroyResources();
    };
};


#endif // BUTTON_H
