//CS 201 HW 2
//Author: Orhun Ege Çelik
//ID: 22202321
//Section : 3

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <chrono>
using namespace std;

int allocMergeSort = 0;
void bubbleSort(int theArray[], int n) {
    bool sorted = false;
    for (int pass = 1; (pass < n) && !sorted; ++pass) {
        sorted = true;
        for (int index = 0; index < n-pass; ++index) {
            int nextIndex = index + 1;
            if (theArray[index] > theArray[nextIndex]) {
                swap(theArray[index], theArray[nextIndex]);
                sorted = false; // signal exchange
            }
        }
    }
}

void merge(int theArray[], int first, int mid, int last) {
    
    int* tempArray = new int[last-first+1]; // temporary array
    allocMergeSort += last-first+1;
    int first1 = first; // beginning of first subarray
    int last1 = mid; // end of first subarray
    int first2 = mid + 1; // beginning of second subarray
    int last2 = last; // end of second subarray
    int index = first1; // next available location in tempArray
    for ( ; (first1 <= last1) && (first2 <= last2); ++index) {
        if (theArray[first1] < theArray[first2]) {
            tempArray[index-first] = theArray[first1];
            ++first1;
        }
        else {
            tempArray[index-first] = theArray[first2];
            ++first2;
        }
    }
    // finish off the first subarray, if necessary
    for (; first1 <= last1; ++first1, ++index)
        tempArray[index-first] = theArray[first1];
    // finish off the second subarray, if necessary
    for (; first2 <= last2; ++first2, ++index)
        tempArray[index-first] = theArray[first2];
    // copy the result back into the original array
    for (index = first; index <= last; ++index)
        theArray[index] = tempArray[index-first];

    delete[] tempArray;
}

void mergesort(int theArray[], int first, int last) {
    if (first < last) {
        int mid = (first + last)/2; // index of midpoint
        mergesort(theArray, first, mid);
        mergesort(theArray, mid+1, last);
        // merge the two halves
        merge(theArray, first, mid, last);
    }
}




void partition(int theArray[], int first, int last, int &pivotIndex) {
    // Precondition: theArray[first..last] is an array; first <= last.
    // Postcondition: Partitions theArray[first..last] such that:
    // S1 = theArray[first..pivotIndex-1] < pivot
    // theArray[pivotIndex] == pivot
    // S2 = theArray[pivotIndex+1..last] >= pivot
    // place pivot in theArray[first]

    int pivot = theArray[first]; // copy pivot

    // initially, everything but pivot is in unknown
    int lastS1 = first; // index of last item in S1
    int firstUnknown = first + 1; // index of first item in unknown
    // move one item at a time until unknown region is empty
    for ( ; firstUnknown <= last; ++firstUnknown) {
        // Invariant: theArray[first+1..lastS1] < pivot
        // theArray[lastS1+1..firstUnknown-1] >= pivot
        // move item from unknown to proper region
        if (theArray[firstUnknown] < pivot) { // belongs to S1
            ++lastS1;
            swap(theArray[firstUnknown], theArray[lastS1]);
        } // else belongs to S2
    }
    // place pivot in proper position and mark its location
    swap(theArray[first], theArray[lastS1]);
    pivotIndex = lastS1;
}

void quicksort(int theArray[], int first, int last) {
    // Precondition: theArray[first..last] is an array.
    // Postcondition: theArray[first..last] is sorted.
    int pivotIndex;
    if (first < last) {
        // create the partition: S1, pivot, S2
        partition(theArray, first, last, pivotIndex);
        // sort regions S1 and S2
        quicksort(theArray, first, pivotIndex-1);
        quicksort(theArray, pivotIndex+1, last);
    }
}

int *generate_random_array(int size) {
    srand((unsigned int)time(NULL));
    int* arr = new int[size];
    for(int i = 0; i<size; i++){
        arr[i] = rand();
    }
    return arr;
    
}
int *generate_almost_sorted_array(int size) {
    srand((unsigned int)time(NULL));
    int *my_array = new int[size];
    for (int i = 0; i < size; i++) {
        my_array[i] = i;
        if (std::rand() % 10 == 1) {
            my_array[i] = i + size;
        }
    }
    return my_array;
}

void printBubble(int size, bool descending, bool ascending){
    double sum = 0;
    
    for(int j = 0; j<10; j++){
        
        int* arr = generate_almost_sorted_array(size);        
        
        double total_time = 0.0;
        
        
        if(descending || ascending)
            quicksort(arr, 0, size-1);
        //To form a reverse decending array
        if(descending){
            for(int i = 0; i< size/2; i++){
                swap(arr[i], arr[size-1-i]);
            }
        }
        
        
        
        std::chrono::time_point<std::chrono::system_clock> start, end;

        start = std::chrono::system_clock::now();
        bubbleSort(arr, size);

        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        
        delete[] arr;
        sum += elapsed_seconds.count();
        
    }
    cout << "Average duration for BubbleSort is: " << sum/10 << endl;
    cout << "Memory used for BubbleSort is: " << size << endl;
    cout<<endl;
}

void printMerge(int size, bool descending, bool ascending){
    double sum = 0;
    
    for(int j = 0; j<10; j++){
        
        int* arr = generate_almost_sorted_array(size);        
        
        double total_time = 0.0;
        
        
         if(descending || ascending)
            quicksort(arr, 0, size-1);
        //To form a reverse decending array
        if(descending){
            for(int i = 0; i< size/2; i++){
                swap(arr[i], arr[size-1-i]);
            }
        }
        
        
        std::chrono::time_point<std::chrono::system_clock> start, end;

        start = std::chrono::system_clock::now();
        mergesort(arr, 0, size-1);

        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        
        delete[] arr;
        sum += elapsed_seconds.count();
        
    }
    cout << "Average duration for MergeSort is: " << sum/10 << endl;
    cout << "Memory used for MergeSort is: " << size + allocMergeSort/10 << endl;
    cout<<endl;
    allocMergeSort = 0;
}

void printQuickSort(int size, bool descending, bool ascending){
    double sum = 0;
    
    for(int j = 0; j<10; j++){
        
        int* arr = generate_almost_sorted_array(size);        
        
        double total_time = 0.0;
        
        
         if(descending || ascending)
            quicksort(arr, 0, size-1);
        //To form a reverse decending array
        if(descending){
            for(int i = 0; i< size/2; i++){
                swap(arr[i], arr[size-1-i]);
            }
        }
        
        
        std::chrono::time_point<std::chrono::system_clock> start, end;

        start = std::chrono::system_clock::now();
        quicksort(arr, 0, size-1);

        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        
        delete[] arr;
        sum += elapsed_seconds.count();
        
    }
    cout << "Average duration for QuickSort is: " << sum/10 << endl;
    cout << "Memory used for QuickSort is: " << size << endl;
    cout<<endl;
}

void sortTester(){

double sum = 0;
    int size = 16;
    for(int j = 0; j<10; j++){
        cout << "Now Bubble Sorting " << j+1 << "th time for size " << size <<"."<<endl;
        int* arr = generate_random_array(size);        
        cout << endl;
        double total_time = 0.0;
        
        
        //quicksort(arr, 0, size-1);
        //To form a reverse decending array
        /*
        for(int i = 0; i< size/2; i++){
            swap(arr[i], arr[sizse-1-i]);
        }
        */
        
        for(int i = 0; i<size; i++){
            cout << arr[i] << "\t";
            if(i != 0 && i%8 == 0){
                cout << endl;
            }
        }
        
        cout<<endl;
        std::chrono::time_point<std::chrono::system_clock> start, end;

        start = std::chrono::system_clock::now();
        bubbleSort(arr, size);

        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        cout << "Execution took " << elapsed_seconds.count() << " seconds." << endl;
        cout << endl;
        
        for(int i = 0; i<size; i++){
            cout << arr[i] << "\t";
            if(i != 0 && i % 8 == 0){
                cout << endl;
            }
        }
        
        delete[] arr;
        cout << endl;
        cout << "Sorting and printing complete for " << (j+1) <<"th time."<<endl;
        cout << endl;
        sum += elapsed_seconds.count();
        
    }
    cout << "Average duration is: " << sum/10 << endl;
    cout << "Memory used is: " << size << endl;


    sum = 0;
    size = 16;
    for(int j = 0; j<10; j++){
        cout << "Now Merge Sorting " << j+1 << "th time for size " << size <<"."<<endl;
        int* arr = generate_random_array(size);        
        cout << endl;
        double total_time = 0.0;
        
        
        //quicksort(arr, 0, size-1);
        //To form a reverse decending array
        /*
        for(int i = 0; i< size/2; i++){
            swap(arr[i], arr[sizse-1-i]);
        }
        */
        
        for(int i = 0; i<size; i++){
            cout << arr[i] << "\t";
            if(i != 0 && i%8 == 0){
                cout << endl;
            }
        }
        
        cout<<endl;
        std::chrono::time_point<std::chrono::system_clock> start, end;

        start = std::chrono::system_clock::now();
        mergesort(arr, 0, size-1);
        

        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        cout << "Execution took " << elapsed_seconds.count() << " seconds." << endl;
        cout << endl;
        
        for(int i = 0; i<size; i++){
            cout << arr[i] << "\t";
            if(i != 0 && i % 8 == 0){
                cout << endl;
            }
        }
        
        delete[] arr;
        cout << endl;
        cout << "Sorting and printing complete for " << (j+1) <<"th time."<<endl;
        cout << endl;
        sum += elapsed_seconds.count();
        
    }
    cout << "Average duration is: " << sum/10 << endl;
    cout << "Memory used is: " << size << endl;


    sum = 0;
    size = 16;
    for(int j = 0; j<10; j++){
        cout << "Now Quick Sorting " << j+1 << "th time for size " << size <<"."<<endl;
        int* arr = generate_random_array(size);        
        cout << endl;
        double total_time = 0.0;
        
        
        //quicksort(arr, 0, size-1);
        //To form a reverse decending array
        /*
        for(int i = 0; i< size/2; i++){
            swap(arr[i], arr[sizse-1-i]);
        }
        */
        
        for(int i = 0; i<size; i++){
            cout << arr[i] << "\t";
            if(i != 0 && i%8 == 0){
                cout << endl;
            }
        }
        
        cout<<endl;
        std::chrono::time_point<std::chrono::system_clock> start, end;

        start = std::chrono::system_clock::now();
        quicksort(arr, 0, size-1);
    

        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        cout << "Execution took " << elapsed_seconds.count() << " seconds." << endl;
        cout << endl;
        
        for(int i = 0; i<size; i++){
            cout << arr[i] << "\t";
            if(i != 0 && i % 8 == 0){
                cout << endl;
            }
        }
        
        delete[] arr;
        cout << endl;
        cout << "Sorting and printing complete for " << (j+1) <<"th time."<<endl;
        cout << endl;
        sum += elapsed_seconds.count();
        
    }
    cout << "Average duration is: " << sum/10 << endl;
    cout << "Memory used is: " << size << endl;

}

int main(){
    int size = 64;
    
    for(int i = size; i<=16384; i*=2){
        cout<<"Random Array Sorting results for size " << i << endl;
        printBubble(i, false, false);
        printMerge(i, false, false);
        printQuickSort(i, false, false);
    }

     for(int i = size; i<=16384; i*=2){
        cout<<"Descending Sorted Array Sorting results for size " << i << endl;
        printBubble(i, true, false);
        printMerge(i, true, false);
        printQuickSort(i, true, false);
    }

     for(int i = size; i<=16384; i*=2){
        cout<<"Ascending Sorted Array Sorting results for size " << i << endl;
        printBubble(i, false, true);
        printMerge(i, false, true);
        printQuickSort(i, false, true);
    }
    
    
    return 0;
}
