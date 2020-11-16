#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "defines.h"
#include "button.h"
#include "prototypes.h"

#include <algorithm>
#include <random>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

using namespace std;

extern ALLEGRO_FONT *arial;

///Drawing the change size buttons and provides functionality for them
void draw_change_size_buttons(ALLEGRO_EVENT &ev, int mx, int my, bool mstate, button &enter, button &confirm, string &display_size, int &arr_size, bool &edit_size_state, bool &edit_search_state, vector <int> &arr){

    enter.draw(mx, my, mstate);
    confirm.draw(mx, my, mstate);

    //If the first button is clicked, the user can exit
    if (enter.isClicked && !edit_search_state){
        enter.text = "";
        edit_size_state = true;
    }

    //If confirm is clicked and a valid input is chosen, array size changes to size of input entered by user
    if (confirm.isClicked && edit_size_state && enter.text != ""){
        int n = stoi(enter.text);

        if (n < 2){
            enter.text = "Input too small";
        }
        else if (n > 500){
            enter.text = "Input too large";
        }
        else {
            arr_size = n;
            create_array(arr, arr_size);
            edit_size_state = false;
        }
    }

    al_draw_filled_rounded_rectangle(1015, 15, 1235, 55, ROUND, ROUND, BLUE);
    al_draw_text(arial, BLACK, 1125, 25, ALLEGRO_ALIGN_CENTRE, "Size of Array  (2 - 500)");

}

///Creating array of a desired size and shuffles it randomly
void create_array(vector <int> &arr, int arr_size){

    arr.clear();

    for (int i=1; i<=arr_size; i++){
        arr.push_back(i);
    }
    random_shuffle(arr.begin(), arr.end());
}

///Resetting everything to its original state (Used when randomizing and entering a new array size)
void reset_all(vector <int> &arr, bool &start_state, bool &draw_state, bool &binary_state, bool &isSorted, int &i, int &j, int &comparisons, int &swaps, int &arrSize, float &time){

    random_shuffle(arr.begin(), arr.end());
    start_state = true;
    draw_state = false;
    binary_state = false;
    isSorted = false;
    i = 0;
    j = 0;
    comparisons = 0;
    time = 0;
    swaps = 0;
    arrSize = 0;
}

///Drawing change in speed buttons that dictate how fast the sort is displayed
void draw_speed_buttons(int mx, int my, bool mstate, button &add, button &subtract, int &speed){
    string s = to_string(speed);

    add.draw(mx, my, mstate);
    subtract.draw(mx, my, mstate);

    al_draw_filled_rounded_rectangle(1015, 150, 1235, 190, ROUND, ROUND, BLUE);
    al_draw_text(arial, BLACK, 1125, 160, ALLEGRO_ALIGN_CENTRE, "Simulation Speed");

    al_draw_filled_rounded_rectangle(1110, 195, 1140, 235, ROUND, ROUND, BLUE);
    al_draw_text(arial, BLACK, 1125, 204, ALLEGRO_ALIGN_CENTRE, s.c_str());

    //If either button is clicked, speed is added or subtracted accordingly
    if (add.isClicked && speed <= 4){
        speed++;
    }
    else if (subtract.isClicked && speed > 0){
        speed--;
    }
}

///Cycling through each type of sort when the change button is clicked (bubble, selection, quick)
void draw_change_sort_button(int mx, int my, bool mstate, button &change, int &sort_type, string &name){

    change.draw(mx, my, mstate);

    if (change.isClicked){
        sort_type++;
        sort_type %= 3;
    }

    switch (sort_type){
    case 0:
        name = "Bubble Sort";
        break;
    case 1:
        name = "Selection Sort";
        break;
    case 2:
        name = "Quick Sort";
        break;

    }
    al_draw_filled_rounded_rectangle(1128, 240, 1235, 280, ROUND, ROUND, BLUE);
    al_draw_text(arial, BLACK, 1181, 250, ALLEGRO_ALIGN_CENTRE, name.c_str());
}


///Functionality for solve button (calls whichever solve type is entered)
void draw_solve_button(int mx, int my, bool mstate, button &solve, int mode, bool &draw_state, bool &start_state, bool &isSorted, vector <int> &arr, vector <vector<int>> &steps, vector <int> &pivots,
                       int &comparisons, int &swaps, int &arrSize, float &time){

    solve.draw(mx, my, mstate);

    //selected sort is executed if solve has been clicked and the array is not sorted
    if (solve.isClicked && start_state){
        arrSize = 0;
        steps.clear();
        pivots.clear();
        start_state = false;
        draw_state = true;

        //Calls bubble sort
        if (mode == 0){
            const clock_t begin_time = clock();
            bubbleSort(arr, steps, comparisons, swaps);
            time = float( clock () - begin_time ) / CLOCKS_PER_SEC;
            isSorted = true;

        }
        //Calls selection sort
        else if (mode == 1){
            const clock_t begin_time = clock();
            selectionSort(arr, steps, comparisons, swaps);
            time = float( clock () - begin_time ) / CLOCKS_PER_SEC;
            isSorted = true;

            //Measuring the memory size of the array (how much extra memory merge sort uses)
            for (int i=0; i<arr.size()-1; i++){
                arrSize += sizeof(arr[i]);
            }
        }

        //Calls quick sort
        else{
            const clock_t begin_time = clock();
            quickSort(arr, 0, arr.size()-1, steps, pivots, comparisons, swaps);
            time = float( clock () - begin_time ) / CLOCKS_PER_SEC;
            isSorted = true;

        }
    }
}

///Functionality to change the number to be searched
void draw_binary_search_buttons(int mx, int my, bool mstate, int &search_num, int &j, bool &edit_search_state, bool &edit_size_state, bool &binary_state, button &change_input, button &confirm_input){

    al_draw_filled_rounded_rectangle(1015, 330, 1235, 370, ROUND, ROUND, BLUE);
    al_draw_text(arial, BLACK, 1125, 340, ALLEGRO_ALIGN_CENTRE, "Enter Search Number");

    change_input.draw(mx, my, mstate);
    confirm_input.draw(mx, my, mstate);

    if (change_input.isClicked && !edit_size_state){
        change_input.text = "";
        edit_search_state = true;
    }

    if (confirm_input.isClicked && edit_search_state){
        j = 0;
        binary_state = false;
        int n = stoi(change_input.text);
        search_num = n;
        edit_search_state = false;
    }

}

