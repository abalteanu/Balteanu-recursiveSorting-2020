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

//Merge sort main function
void mergeSort(vector <int> &arr, int l, int r, vector <vector <int>> &steps, int &comparisons, int &swaps){

    if (l < r){

        //Divides array and half continuosly
        int m = (l+r) / 2;

        mergeSort(arr, l, m, steps, comparisons, swaps);
        mergeSort(arr, m+1, r, steps, comparisons, swaps);

        //Recombines the arrays in order
        combine(arr, l, m, r, steps, comparisons, swaps);
    }
}

void combine(vector <int> &arr, int l, int m, int r, vector <vector <int>> &steps, int &comparisons, int &swaps){

    //Separates array into two halves
    vector <int> leftHalf;
    vector <int> rightHalf;

    //Populates the subarrays
    for (int i=l; i<m+1; i++){
        leftHalf.push_back(arr[i]);
    }
    for (int i=m+1; i<r+1; i++){
        rightHalf.push_back(arr[i]);
    }

    int i=0;
    int j=0;
    int k=l;

    //Combines the two sorted arrays, changing the original array
    while (i < leftHalf.size() && j < rightHalf.size()){

        if (leftHalf[i] <= rightHalf[j]){

            arr[k] = leftHalf[i];
            i++;

        }
        else{
            arr[k] = rightHalf[j];
            j++;
        }

        steps.push_back(arr);

        comparisons++;
        swaps++;
        k++;
    }

    //If there is excess leftover in either subarray, finish the job
    while (i < leftHalf.size()){
        arr[k] = leftHalf[i];
        i++;
        k++;
        swaps++;
        steps.push_back(arr);
    }
    while (j < rightHalf.size()){
        arr[k] = rightHalf[j];
        j++;
        k++;
        swaps++;
        steps.push_back(arr);
    }
}
