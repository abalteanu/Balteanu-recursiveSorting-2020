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

///Implementation of Selection sort algorithm
void selectionSort(vector <int> &arr, vector <vector<int>> &steps, int &comparisons, int &swaps){
    int i, j, min_idx;
    //Moving boundry of pass up by one for every pass
    for (i = 0; i < arr.size()-1; i++)
    {
        //Finding the min element in unsorted array (save index)
        min_idx = i;
        for (j = i+1; j < arr.size(); j++){
            if (arr[j] < arr[min_idx]){
                steps.push_back(arr);
                swaps++;
                min_idx = j;
            }
            comparisons++;
        }
        //Swap min with first element in pass
        swapElement(arr, min_idx, i);
    }
}
