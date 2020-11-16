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

///Checks if button is pressed and that array has been sorted, then calls binary sort
void binary_search_functionality(int mx, int my, bool mstate, int search_num, int &j, int &cnt, int &check, int &comparisons, int &swaps, bool &binary_state, bool &draw_sort_state, float &time,
                                 bool &isSorted, button &simulate, vector <int> &arr, vector <int> &left, vector <int> &middle, vector <int> &right){

    simulate.draw(mx, my, mstate);

    if (simulate.isClicked && isSorted && !draw_sort_state){

        //Stats are reset
        j = 0;
        cnt = 0;
        comparisons = 0;
        swaps = 0;

        left.clear();
        right.clear();
        middle.clear();
        middle.push_back(0);

        const clock_t begin_time = clock();

        binary_state = true;

        check = binarySearch(arr, 0, arr.size()-1, search_num, comparisons, left, middle, right);
    }
}


///Implementation of binary search
int binarySearch (vector <int> &arr, int l, int r, int x, int &comparisons, vector <int> &left, vector <int> &middle, vector <int> &right){

    if (r >= l){

        //Finds a midpoint
        int mid = (l + r) / 2;

        left.push_back(l);
        right.push_back(r);
        middle.push_back(mid);

        //If the mid point is not the desired number, the left half or the right half of the sorted array is ignored depending on size of number
        if (arr[mid] == x){
            return mid;
        }
        else if (arr[mid] > x){
            comparisons++;
            binarySearch(arr, l, mid - 1, x, comparisons, left, middle, right);

        }
        else if (arr[mid] < x){
            comparisons++;
            binarySearch(arr, mid + 1, r, x, comparisons, left, middle, right);
        }

        else{
            return -1;
        }
    }
}
