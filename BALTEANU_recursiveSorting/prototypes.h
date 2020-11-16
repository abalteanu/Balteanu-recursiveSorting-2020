#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTYPES_H_INCLUDED

#include "defines.h"
#include "button.h"
#include <iostream>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>


using namespace std;

//allegro
int startAllegro(const char title[], ALLEGRO_DISPLAY *&display, ALLEGRO_EVENT_QUEUE *&event_queue, ALLEGRO_TIMER *&timer, ALLEGRO_FONT *&font);
void initializeAllegro();
void createDisplay (const char title[]);
void checkSetup(ALLEGRO_DISPLAY *display);

//bubble_sort
void bubbleSort(vector <int> &arr, vector <vector<int>> &steps, int &comparisons, int &swaps);
void swapElement(vector <int> &arr, int index1, int index2);

//selection_sort
void selectionSort(vector <int> &arr, vector <vector<int>> &steps, int &comparisons, int &swaps);

//quick_sort
void quickSort(vector <int> &arr, int l, int r, vector <vector<int>> &steps, vector <int> &pivots, int &comparisons, int &swaps);
int create_Partition(vector <int> &arr, int l, int r, vector <vector<int>> &steps, vector <int> &pivots, int &comparisons, int &swaps);

//draw_functions
void draw_sort(vector <int> arr);
void draw_pivot(vector <int> arr, int pivot);
void draw_binary_simulation (int j, vector <int> arr, vector <int> left, vector <int> middle, vector <int> right);
void checkIfFound(vector <int> &arr, int num, int index);
void draw_metrics(vector <int> arr, int comparisons, int swaps, int arrSize, int sort_mode, float &time);
string toString(float a);

//button_functions
void draw_change_size_buttons(ALLEGRO_EVENT &ev, int mx, int my, bool mstate, button &enter, button &confirm, string &display_size, int &arr_size, bool &edit_size_state, bool &edit_search_state, vector <int> &arr);
void create_array(vector <int> &arr, int arr_size);
void reset_all(vector <int> &arr, bool &start_state, bool &draw_state, bool &binary_state, bool &isSorted, int &i, int &j, int &comparisons, int &swaps, int &arrSize, float &time);
void draw_speed_buttons(int mx, int my, bool mstate, button &add, button &subtract, int &speed);
void draw_change_sort_button(int mx, int my, bool mstate, button &change, int &state, string &name);
void draw_solve_button(int mx, int my, bool mstate, button &solve, int mode, bool &draw_state, bool &start_state, bool &isSorted, vector <int> &arr, vector <vector<int>> &steps, vector <int> &pivots,
                       int &comparisons, int &swaps, int &arrSize, float &time);
void draw_binary_search_buttons(int mx, int my, bool mstate, int &search_num, int &j, bool &edit_search_state, bool &edit_size_state, bool &binary_state, button &change_input, button &confirm_input);


//binary_search
void binary_search_functionality(int mx, int my, bool mstate, int search_num, int &j, int &cnt, int &check, int &comparisons, int &swaps,  bool &binary_state, bool &draw_sort_state, float &time,
                                 bool &isSorted, button &simulate, vector <int> &arr, vector <int> &left, vector <int> &middle, vector <int> &right);
int binarySearch (vector <int> &arr, int l, int r, int x, int &comparisons, vector <int> &left, vector <int> &middle, vector <int> &right);

//text_editing
char intInput(ALLEGRO_EVENT &ev);
void edit_text(ALLEGRO_EVENT &ev, button &b);


#endif // PROTOTYPES_H_INCLUDED
