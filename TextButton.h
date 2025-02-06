#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H

#include "Button.h"

namespace Al
{
    class TextButton : public Button
    {
        protected:
            string txt;

        public:
            TextButton()
            {
                Button();
            }

            TextButton(string text)
            {
                TextButton();
                Create(text);
            }

            void Create(string text);
    };
};

#endif // TEXTBUTTON_H
