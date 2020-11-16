#include <iostream>
#include <vector>
#include "button.h"
#include "prototypes.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

using namespace std;
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT *arial;
extern ALLEGRO_EVENT_QUEUE *event_queue;

///This constructor initializes everything needed for allegro class
int startAllegro(const char title[], ALLEGRO_DISPLAY *&display, ALLEGRO_EVENT_QUEUE *&event_queue, ALLEGRO_TIMER *&timer, ALLEGRO_FONT *&font)
{

    initializeAllegro();
    createDisplay (title);
    checkSetup(display);

    al_install_mouse();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
 	al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

	al_flip_display();
	al_start_timer(timer);
    al_clear_to_color(BLACK);
}

///This function initializes allegro and other addons
void initializeAllegro()
{
    // Initialize Allegro
	al_init();

	al_init_font_addon();   //initialize font addon
    al_init_ttf_addon();    //initialize True Type Font addon

}

///This function creates the display and names the window
void createDisplay(const char title [])
{
    display = al_create_display(SCREEN_W, SCREEN_H);
    al_set_window_title(display, title);
}

///This function checks all initializations (display, keyboard, etc.) and creates a timer and an event queue
void checkSetup(ALLEGRO_DISPLAY *display)
{
    //checking initialization of allegro
    if(!al_init())
    {
      al_show_native_message_box(display, "Error", "Error", "Failed to initialize allegro!",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      //return -1;
    }

    //check display
	if (!display)
    {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
       	//return -1;
	}

   	// Initialize keyboard routines
	if (!al_install_keyboard())
    {
	    al_show_native_message_box(display, "Error", "Error", "failed to initialize the keyboard!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
     	//return -1;
   	}

   	// Initialize mouse
   	if (!al_install_mouse())
    {
	    al_show_native_message_box(display, "Error", "Error", "failed to initialize the mouse!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
     	//return -1;
   	}

	// Adding image processor
 	if (!al_init_image_addon())
    {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize image addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	//return -1;
	}

	// Setting up timer
	timer = al_create_timer(1.0 / 60);

   	if (!timer)
    {
   		al_show_native_message_box(display, "Error", "Error", "Failed to create timer!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        //return -1;
    }

    arial = al_load_ttf_font("C:/Windows/Fonts/arial.ttf", 16, 0);

    if (!arial)
    {
        al_show_native_message_box(display, "Error", "Error", "Could not load font 1.ttf",
                                    nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        //return -1;
    }

    // Initialize primative add on
 	if (!al_init_primitives_addon())
    {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize primatives addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	//return -1;
	}

	// set up event queue
	event_queue = al_create_event_queue();

	if (!event_queue)
    {
		al_show_native_message_box(display, "Error", "Error", "Failed to create event_queue!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
      	//return -1;
	}

}

