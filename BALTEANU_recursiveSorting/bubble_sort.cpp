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

using namespace std;

///Implementation of bubble sort algorithm
void bubbleSort(vector <int> &arr, vector <vector<int>> &steps, int &comparisons, int &swaps){
    //i ontrols passes
    for (int i=0; i<arr.size()-1; i++){
        //Swapped boolean to improve efficiency
        int swapped = false;
        //j loop controls comparisons
        for (int j=0; j<arr.size()-1; j++){
            if (arr[j] > arr[j+1]){
                //Swapping elements if they are out of order
                swapElement(arr, j, j+1);
                swapped = true;
                steps.push_back(arr);
                swaps++;
            }
            comparisons++;
        }
        //If nothing has been swapped in the whole pass, it means the array is sorted
        if (!swapped){
            break;
        }
    }
}

///Swap element function --> also used in Selection sort
void swapElement(vector <int> &arr, int index1, int index2){
    int temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}
