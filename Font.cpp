#include "Font.h"
#include <iostream>

using namespace Al;

Font::Font(string file, int size)
{
    Load(file, size);
}

void Font::Load(string file, int size)
{
    font = al_load_font(file.c_str(), size, NULL);
    if(!font) cerr << "Nie udalo sie zaladowac czcionki z " << file << endl;
}

Font::~Font()
{
    Destroy();
}

void Font::Destroy()
{
    if(font)
        al_destroy_font(font);
    font = NULL;
}

Font& Font::operator<<(string s)
{
	text << s;
	return *this;
}

Font& Font::operator<<(const char *s)
{
	text << s;
	return *this;
}

Font& Font::operator<<(char s)
{
	text << s;
	return *this;
}

Font& Font::operator<<(int s)
{
	text << s;
	return *this;
}

Font& Font::operator<<(double s)
{
	text << s;
	return *this;
}

Font&  Font::operator<<(Print p)
{
    int align = 0;
    if(p.aln == Left) align = ALLEGRO_ALIGN_LEFT;
    else if(p.aln == Right) align = ALLEGRO_ALIGN_RIGHT;
    else if(p.aln == Centre) align = ALLEGRO_ALIGN_CENTRE;
	al_draw_text(font, p.col, p.px, p.py, align, text.str().c_str());
	text.str("");
	return *this;
}

int Font::GetTextWidth(string txt)
{
    return al_get_text_width(font, txt.c_str());
}
