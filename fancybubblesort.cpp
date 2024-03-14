#include <iostream>
using namespace std;

// Purpose of the Swap Function: Swaps the two integers using call by reference
// Parameters: 2 integers
void swap (int &a, int &b){
    int temp; // create a temporary variable to copy the first variable
    temp = a; // copy the first variable
    a = b; // assign the second variable to the first variable
    b = temp; // assign the first variable to the second variable

    return;
}

int main (){
    int my_array[10] = {10,9,0,7,6,5,411,2,2,1}; // creates the array called my_array that will be sorted
    int listsize = 10; // length of my_array
    
    int counter = 0; // counter that keeps track of how many swaps were made
    
    bool sorted; // to keep track if the array was sorted
    bool hadToSwap = false; // to keep track if swaps are made

    // do while loop to run through the array at least one time until it is sorted
    do {
        sorted = false; 

        // go through the array and swap adjacent integers if not in ascending order
        for (int i=0; i<listsize-1;i++){
            if (my_array[i] > my_array[i+1]){
                swap(my_array[i], my_array[i+1]); // calls the swap function
                sorted = true;
                counter++;
            }
        }
    } while (sorted);

    // Determines if the array was already sorted
    if (counter != 0){
        hadToSwap = true;
    }

    // Output the results of the bubblesort program
    if (hadToSwap){
            cout << "The array had to be sorted using " << counter << " swaps. Here is sorted the array: ";
        }
        else{
            cout << "The array was already sorted and zero swaps were made. Here is the array: ";
        }

    // Output the sorted array
    for (int i=0; i<listsize; i++){
        cout << my_array[i];
        if (i != listsize-1){
            cout <<", ";
        }
    }
    
    // Return 0 for the main function
    return 0;
}