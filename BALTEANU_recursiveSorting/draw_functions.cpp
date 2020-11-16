#include <iostream>
#include <sstream>
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
#include <allegro5/color.h>
#include <allegro5/allegro_color.h>

using namespace std;

extern ALLEGRO_FONT *arial;

///Drawing array with corresponding height and width depending on array size
void draw_sort(vector <int> arr){

    float barLength = 1000.0 / arr.size();

    for (int i=0; i<arr.size(); i++){

        float height = (float) arr[i] / arr.size() * 645;

        al_draw_filled_rectangle(i * barLength, 645 - height, (i * barLength) + barLength, SCREEN_H, LIGHTBLUE);
    }

}

///Drawing pivot for quicksort function
void draw_pivot(vector <int> arr, int pivot){

    float barLength = 1000.0 / arr.size();
    al_draw_filled_rectangle(pivot * barLength, 0, (pivot * barLength) + barLength, SCREEN_H, WHITE);
}

///Visualizing binary search
void draw_binary_simulation (int j, vector <int> arr, vector <int> left, vector <int> middle, vector <int> right){

    float barLength = 1000.0 / arr.size();

    int l = left[j];
    int r = right[j];
    int m = middle[j];

    //Draws darkened areas of array to show halves that have been ignored
    for (int i=0; i<arr.size(); i++){

        float height = (float) arr[i] / arr.size() * 645;

        if (i >=0 && i < l){
            al_draw_filled_rectangle(i * barLength, 645 - height, (i * barLength) + barLength, SCREEN_H, BLUE);
        }
        else if (i >= l && i < r+1){
            al_draw_filled_rectangle(i * barLength, 645 - height, (i * barLength) + barLength, SCREEN_H, LIGHTBLUE);
        }
        else if (i >= r && i < arr.size()){
            al_draw_filled_rectangle(i * barLength, 645 - height, (i * barLength) + barLength, SCREEN_H, BLUE);
        }

    }

    //Drawing midpoint
    float height = (float) arr[m] / arr.size() * 645;
    al_draw_filled_rectangle(m * barLength, 645 - height, (m*barLength) + barLength, SCREEN_H, WHITE);
}

///Drawing result of binary search
void checkIfFound(vector <int> &arr, int num, int index){
    if (arr[index] == num){
        string text = "Found element ";
        text += toString(num);
        text += " at index ";
        text += toString(index);

        al_draw_text(arial, WHITE, 10, 10, 0, text.c_str());
    }
    else{
        al_draw_text(arial, WHITE, 10, 10, 0, "No such element found");
    }
}

///Drawing metrics (comparisons, swaps, time, array size)
void draw_metrics(vector <int> arr, int comparisons, int swaps, int arrSize, int sort_mode, float &time){


    al_draw_filled_rounded_rectangle(1015, 465, 1140, 505, ROUND, ROUND, RED);
    al_draw_text(arial, BLACK, 1077, 475, ALLEGRO_ALIGN_CENTRE, "Comparisons");

    al_draw_filled_rounded_rectangle(1145, 465, 1235, 505, ROUND, ROUND, YELLOW);
    al_draw_text(arial, BLACK, 1190, 475, ALLEGRO_ALIGN_CENTRE, toString(comparisons).c_str());

    al_draw_filled_rounded_rectangle(1015, 510, 1140, 550, ROUND, ROUND, RED);
    al_draw_text(arial, BLACK, 1077, 520, ALLEGRO_ALIGN_CENTRE, "Swaps");

    al_draw_filled_rounded_rectangle(1145, 510, 1235, 550, ROUND, ROUND, YELLOW);
    al_draw_text(arial, BLACK, 1190, 520, ALLEGRO_ALIGN_CENTRE, toString(swaps).c_str());

    al_draw_filled_rounded_rectangle(1015, 555, 1140, 595, ROUND, ROUND, YELLOW);
    al_draw_text(arial, BLACK, 1077, 565, ALLEGRO_ALIGN_CENTRE, "Time (S)");

    al_draw_filled_rounded_rectangle(1145, 555, 1235, 595, ROUND, ROUND, RED);
    al_draw_text(arial, BLACK, 1190, 565, ALLEGRO_ALIGN_CENTRE, toString(time).c_str());

    if (sort_mode == 1){
        al_draw_text(arial, BLACK, 1190, 610, ALLEGRO_ALIGN_CENTRE, toString(arrSize).c_str());
    }
    else{
        al_draw_text(arial, BLACK, 1190, 610, ALLEGRO_ALIGN_CENTRE, "0");
    }
}

///Converting numbers to strings
string toString(float a){
    stringstream ss;
    ss<<a;
    string s;
    ss>>s;
    return s;
}

