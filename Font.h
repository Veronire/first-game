#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>
#include <sstream>
using namespace std;

enum
{
    Left, Right, Centre
};

struct Print
{
	float px, py;

	ALLEGRO_COLOR col;

	int aln;

	Print(float x, float y, ALLEGRO_COLOR color = al_map_rgb(255, 255, 255), int align = Left) :
        px(x), py(y), col(color), aln(align) { }
};

namespace Al
{
    class Font
    {
        ALLEGRO_FONT *font;
        ostringstream text;

    public:
        Font() { font = NULL; }
        Font(string file, int size);

        ~Font();

        void Load(string file, int size);

        void Destroy();

        int GetTextWidth(string txt);

        Font& operator<<(string s);
        Font& operator<<(const char *s);
        Font& operator<<(char s);
        Font& operator<<(int s);
        Font& operator<<(double s);
        Font& operator<<(Print p);
    };
}


#endif // FONT_H_INCLUDED
