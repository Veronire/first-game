#include "Font.h"
#include "Image.h"
#include "TextButton.h"
#include <iostream>

using namespace Al;

void TextButton::Create(string text)
{
    //cerr << text << endl;
    int width = font.GetTextWidth(text) + 20;
    Resize(width, 30);
    MoveTo(0, 0);

    myImg.Create(width, 30);
    myImg.SetAsTheTarget();
    background.Draw(Al::DrawInfo(0, 0) + Al::Scale((float)width / background.Width(), 30.f / background.Height()));
    font << text << Print(5.f, 5.f);

    al_set_target_backbuffer(al_get_current_display());
    //cerr << text << endl;
}
