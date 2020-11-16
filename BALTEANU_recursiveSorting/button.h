#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro.h>

using namespace std;

///Button class
class button{
private:
    int x1, y1, x2, y2;

public:
    //Constructor with coordinates, name, and colours
    button(string t, int left, int right, int top, int bottom, ALLEGRO_COLOR c1, ALLEGRO_COLOR c2, ALLEGRO_COLOR c3);
    bool isClicked = false;
    string text;            //text on button
    ALLEGRO_COLOR nrmlC;  //colour of button (normal state, hover state and click state)
    ALLEGRO_COLOR hoverC;
    ALLEGRO_COLOR clickC;

    bool prev_state = false;    //for state of mouse
    void draw(int x, int y, bool mstate);
    ~button(){};
};

#endif // BUTTON_H_INCLUDED
