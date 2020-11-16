#include <iostream>
#include "button.h"
#include "defines.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro.h>
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT *arial;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_BITMAP  *background;
extern ALLEGRO_BITMAP *menuBackground;

using namespace std;


///Constructor that initializes colours and location for button
button::button(string t, int left, int right, int top, int bottom, ALLEGRO_COLOR c1, ALLEGRO_COLOR c2, ALLEGRO_COLOR c3){
    text = t;
    x1 = left;
    x2 = right;
    y1 = top;
    y2 = bottom;
    nrmlC = c1;
    hoverC = c2;
    clickC = c3;
}

///Draw function for button
void button::draw(int mx, int my, bool mstate){

    //If the cursor is on the button
    if (mx > x1 && mx < x2 && my > y1 && my < y2){
        //If the mouse is down, draw a certain shaded button
        if (mstate){
            al_draw_filled_rounded_rectangle(x1, y1, x2, y2, ROUND, ROUND, clickC);
            isClicked = false;
        }
        //click is registerd if mouse has clicked down then up and the cursor is still within button borders
        else if (prev_state && !mstate && mx > x1 && mx < x2 && my > y1 && my < y2){
            al_draw_filled_rounded_rectangle(x1, y1, x2, y2, ROUND, ROUND, clickC);
            isClicked = true;
        }
        //Otherwise, draw a shaded button to signal the mouse is hovering
        else {
            al_draw_filled_rounded_rectangle(x1, y1, x2, y2, ROUND, ROUND, hoverC);
            isClicked = false;
        }
    }
    //Draws default button (when cursor is not on button
    else{
        al_draw_filled_rounded_rectangle(x1, y1, x2, y2, ROUND, ROUND, nrmlC);
        isClicked = false;
    }
    prev_state = mstate;
    al_draw_text(arial, BLACK, (x1+x2)/2, (y1+y2)/2 - 10, ALLEGRO_ALIGN_CENTRE, text.c_str());

}
