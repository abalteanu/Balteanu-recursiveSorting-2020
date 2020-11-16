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

///Main quicksort function (recursive implementation)
void quickSort(vector <int> &arr, int l, int r, vector <vector<int>> &steps, vector <int> &pivots, int &comparisons, int &swaps){
    if (l < r){

        //finding pivot and partitioning the array (organizing array)
        int pivot = create_Partition(arr, l, r, steps, pivots, comparisons, swaps);

        //quickSort is called recursively on the newly created subarrays
        quickSort(arr, l, pivot-1, steps, pivots, comparisons, swaps);
        quickSort(arr, pivot+1, r, steps, pivots, comparisons, swaps);
    }
}

///Partition function
int create_Partition(vector <int> &arr, int l, int r, vector <vector<int>> &steps, vector <int> &pivots, int &comparisons, int &swaps){

    //choosing pivot as last element of array
    int pivot = arr[r];
    int i = l;
    int j = r-1;

    //while array has not been completely traversed
    while (i <= j){

        //finding first element that is larger than  pivot on the left hand side
        while (arr[i] < pivot){
            i++;
        }
        //finding first element that is larger than pivot on the right hand side
        while (arr[j] > pivot){
            j--;
        }

        //swapping the two elements if they are on the wrong sides (opposite sides of eachother)
        if (i <= j){
            swapElement(arr, i, j);
            i++;
            j--;
            swaps++;
            steps.push_back(arr);
            pivots.push_back(pivot);

        }
        comparisons++;
    }

    //placing the pivot in the correct position
    if (i < r){
        swapElement(arr, i, r);
        swaps++;
        steps.push_back(arr);
        pivots.push_back(pivot);
    }

    return i;
}

