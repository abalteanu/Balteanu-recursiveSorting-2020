#include <iostream>
#include <vector>
#include "button.h"
#include "prototypes.h"
#include "defines.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

#include <random>

using namespace std;

///For formatting text
void edit_text(ALLEGRO_EVENT &ev, button &b){
    char num = intInput(ev);
    if (num != '\0'){
        //Delete character
        if (b.text.size() != 0 && num == '-'){
            b.text.erase(b.text.size() - 1);
        }
        //Otherwise appends character to temp string
        else if (b.text.size() < 4 && num != '-'){
            b.text += num;
        }
    }
}

///For user input
char intInput(ALLEGRO_EVENT &ev) {
    char input;
    if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
        if (ev.keyboard.keycode >= ALLEGRO_KEY_0 && ev.keyboard.keycode <= ALLEGRO_KEY_9){
            input = char('0' + (ev.keyboard.keycode - ALLEGRO_KEY_0));
            return input;
        }
        else if (ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
            return '-';
        }
    }
    return '\0';
}
