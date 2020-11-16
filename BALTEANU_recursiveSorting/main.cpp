/********************************************************************************
 *	Name:     Ana Balteanu                                                      *
 *	Date:     16/11/2020                                                        *
 *                                                                              *
 *	Description: Graphically displays sorting algorithms namely bubble sort,    *
 *               selection sort and quick sort (recursive). Also does binary    *
 *               search.                                                        *
 *                                                                              *
 *******************************************************************************/


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

#include <algorithm>
#include <random>
#include <time.h>


using namespace std;

ALLEGRO_TIMER *timer = nullptr;
ALLEGRO_DISPLAY *display = nullptr;
ALLEGRO_FONT *arial = nullptr;
ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
ALLEGRO_BITMAP *background = nullptr;
ALLEGRO_BITMAP* menuBackground = nullptr;

int main(){

    startAllegro("Sorting and Searching", display, event_queue, timer, arial);

    //Creation of buttons for menu
    string display_size = "";
    button change_size_button("500", 1015, 1140, 60, 100, BACK1, BACK2, BACK3);
    button confirm_size_button("Enter", 1145, 1235, 60, 100, BACK1, BACK2, BACK3);

    button randomize_button("Randomize", 1015, 1235, 105, 145, BACK1, BACK2, BACK3);

    string sort_name = "Bubble Sort";
    button change_sort("Change Sort", 1015, 1122, 240, 280, BACK1, BACK2, BACK3);

    button subtract_speed_button("Decrease", 1015, 1105, 195, 235, BACK1, BACK2, BACK3);
    button add_speed_button("Increase", 1145, 1235, 195, 235, BACK1, BACK2, BACK3);

    button simulate_sort_button("Simulate Sort", 1015, 1235, 285, 325, BACK1, BACK2, BACK3);
    button reset("Reset", 1015, 1235, 330, 370, BACK1, BACK2, BACK3);

    button change_search_button("100", 1015, 1140, 375, 415, BACK1, BACK2, BACK3);
    button confirm_search_button("Enter", 1145, 1235, 375, 415, BACK1, BACK2, BACK3);
    button simulate_binary_button("Binary Search", 1015, 1235, 420, 460, BACK1, BACK2, BACK3);

    //Mouse coordinates
    int mx, my;
    bool mstate = false;
    bool prev_state = false;

    //Vectors storingcurrent sorting algorithm
    vector <int> arr;
    vector <vector<int>> steps;
    vector <int> left_pointers;
    vector <int> middle_points;
    vector <int> right_pointers;
    vector <int> pivots;

    //Starting array of size 500
    for (int i=0; i<500; i++){
        arr.push_back(i);
    }
    random_shuffle(arr.begin(), arr.end());
    steps.push_back(arr);

    //Variables tracking metrics,
    int size_of_array = 2;
    int speed = 1;
    int comparisons = 0;
    int swaps = 0;
    int arrSize = 0;
    float time = 0;


    //Binary search track Initial search number and Binary_check is used to track the return of the binary_search algorithm (verify if num is found or not)
    int search_number = 100;
    int binary_check = 0;


    //Bool statements that direct the flow of the program
    //Used to determine in what state the program is in at a given moment and what should be drawn
    bool stop = false;
    int sort_state = 0;
    bool editor_state_size = false;
    bool editor_state_search = false;
    bool draw_sort_state = false;
    bool binary_state = false;
    bool pause_draw = false;
    bool start_state = true;
    bool isSorted = false;

    //Counters
    int sort_counter = 0;
    int binary_counter = 0;
    int button_counter = 0;
    int i = 0;
    int j = 0;

    ///Main loop
    while (!stop){

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            stop = true;
        }

        //Calculating mouse coordinates
        if (ev.mouse.x > 0 && ev.mouse.x < 1250) mx = ev.mouse.x;
        if (ev.mouse.y > 0 && ev.mouse.y < 600) my = ev.mouse.y;
        if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) mstate = true;
        if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) mstate = false;


        if (ev.type == ALLEGRO_EVENT_TIMER){

            //Counter for sorting display: calculates speed
            sort_counter++;
            sort_counter %= 7 - speed;

            //Binary search display counter: displays at one frame per second
            binary_counter++;
            binary_counter %= 100;

            //Separate button counter (buttons displayed at a slower frame rate than sorting algoritms
            button_counter++;
            button_counter %= 100;

            //Checks if speed is zero and pauses accordingly

            if (speed == 0){
                pause_draw = true;
            }
            else {
                pause_draw = false;
            }


            //Displaying buttons
            if (button_counter % 2 == 0){

                al_clear_to_color(BLACK);

                //Draws all menu buttons and gives them functionality
                draw_change_size_buttons(ev, mx, my, mstate, change_size_button, confirm_size_button,
                                         display_size, size_of_array, editor_state_size, editor_state_search, arr);

                randomize_button.draw(mx, my, mstate);
                if (confirm_size_button.isClicked || randomize_button.isClicked){
                    reset_all(arr, start_state, draw_sort_state, binary_state, isSorted, i, j, comparisons, swaps, arrSize, time);
                }

                //all button functions check if they are clicked inside function
                draw_speed_buttons(mx, my, mstate, add_speed_button, subtract_speed_button, speed);

                draw_change_sort_button(mx, my, mstate, change_sort, sort_state, sort_name);

                draw_solve_button(mx, my, mstate, simulate_sort_button, sort_state, draw_sort_state, start_state,
                                  isSorted, arr, steps, pivots, comparisons, swaps, arrSize, time);

                draw_binary_search_buttons(mx, my, mstate, search_number, j, editor_state_search, editor_state_size,
                                           binary_state, change_search_button, confirm_search_button);

                binary_search_functionality(mx, my, mstate, search_number, j, binary_counter, binary_check, comparisons, swaps, binary_state, draw_sort_state, time,
                                            isSorted, simulate_binary_button, arr,left_pointers, middle_points, right_pointers);

                draw_metrics(arr, comparisons, swaps, arrSize, sort_state, time);

            }

            //Displays the sorted array when the sort is complete
            if (!draw_sort_state && !binary_state){
                draw_sort(arr);
                al_flip_display();
            }

            //Draws each individual step of the precalculated sort-steps array
            //Commented out, to make program faster if you don't want to see all steps
            else if (draw_sort_state && !pause_draw && sort_counter == 1 && i < steps.size()){

                draw_sort(steps[i]);

                /* each step of sort here... commented out
                cout << "Array at step " << i << ":" << endl;
                for (int k=0; k<steps[i].size(); k++){
                    cout << steps[i][k] << " ";
                }
                cout << endl << endl;

                if (pivots.size() > 0){
                    draw_pivot(arr, pivots[i]);
                    cout << "Pivot is: " << pivots[i] << endl;
                } */

                al_flip_display();
                i++;

                //Once the end of the steps array is reached, stop drawing
                if (i == steps.size()){
                    draw_sort_state = false;
                }

            }

            //If the simulation is paused, draw the most recent frame
            else if (pause_draw){

                if (pivots.size() > 0){
                    draw_pivot(arr, pivots[i]);
                }

                draw_sort(steps[i]);
                al_flip_display();
            }

            //Binary search
            else if (binary_state){

                if (binary_counter == 99 && j < left_pointers.size()-1){
                    j++;
                }
                //if last index of the pointers array is reached, check if the desired number was found
                if (j == left_pointers.size()-1){

                    checkIfFound(arr, search_number, binary_check);
                    draw_binary_simulation(j, arr, left_pointers, middle_points, right_pointers);
                    al_flip_display();

                }
                //Regular drawing of each step of the binary search
                else{
                    draw_binary_simulation(j, arr, left_pointers, middle_points, right_pointers);
                    al_flip_display();
                }
            }

        }

        //Editor states for entering inputs for both array size and search number
        if (editor_state_size && !editor_state_search){
            edit_text(ev, change_size_button);
        }
        else if (editor_state_search && !editor_state_size){
            edit_text(ev, change_search_button);
        }

    }

    return 0;
}


