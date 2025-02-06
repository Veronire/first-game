#include "Image.h"
#include <iostream>

using namespace Al;

bool operator ==(ALLEGRO_COLOR a, ALLEGRO_COLOR b)
{
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

Image::Image(const char *file)
{
    Load(file);
}

Image::Image(int width, int height)
{
    Create(width, height);
}

bool Image::Load(const char *file)
{
    if(bmp) Destroy();
    bmp = al_load_bitmap(file);
    if(!bmp)
    {
        cerr << "Nie udalo sie zaladowac obrazka z " << file << endl;
        return false;
    }
    return true;
}

bool Image::Create(int width, int height)
{
    if(bmp) Destroy();
    bmp = al_create_bitmap(width, height);
    if(!bmp)
    {
        cerr << "Nie udalo sie stworzyc obrazka" << endl;
        return false;
    }
    return true;
}

void Image::Destroy()
{
    if(bmp) al_destroy_bitmap(bmp);
    bmp = NULL;
}

void Image::Save(const char *file)
{
    if(bmp) al_save_bitmap(file, bmp);
}

void Image::SetAsTheTarget()
{
    if(bmp) al_set_target_bitmap(bmp);
}

int Image::Width()
{
    if(!bmp) return 0;
    return al_get_bitmap_width(bmp);
}

int Image::Height()
{
    if(!bmp) return 0;
    return al_get_bitmap_height(bmp);
}

Image Image::Duplicate()
{
    if(!bmp) return Image();
    Image img;
    img.bmp = al_clone_bitmap(bmp);
    return img;
}

Image Image::GetRegion(int x, int y, int w, int h)
{
    if(!bmp) return Image();
    Image img;
    img.bmp = al_create_sub_bitmap(bmp, x, y, w, h);
    return img;
}

ALLEGRO_COLOR Image::GetPixel(int x, int y)
{
    if(!bmp) return al_map_rgb(0, 0, 0);
    return al_get_pixel(bmp, x, y);
}

void Image::PutPixel(int x, int y, ALLEGRO_COLOR colour)
{
    if(!bmp) return;
    _al_put_pixel(bmp, x, y, colour);
}

void Image::Draw(DrawInfo info)
{
    if(!bmp) return;
    //cerr << this << " " << bmp << endl;
    int flags = 0;
    if(info.flipY) flags = ALLEGRO_FLIP_HORIZONTAL;
    if(info.flipX) flags |= ALLEGRO_FLIP_VERTICAL;
    al_draw_tinted_scaled_rotated_bitmap(bmp, info.col, info.cx, info.cy, info.px, info.py, info.sx, info.sy, info.ang, flags);
}

void Image::Draw(float x, float y)
{
    if(!bmp) return;
    al_draw_bitmap(bmp, x, y, NULL);
}
