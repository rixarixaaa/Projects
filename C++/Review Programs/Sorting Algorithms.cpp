#include <iostream>
#include <cstdlib>
#include <ctime>
#include <list>

using namespace std;

void bubbleSort(int arr[]) { // O(n^2)
  bool swapped;
  int swaps = 0, comps = 0;
  
  for(int i = 0; i < 5000 - 1; i++) {
      swapped = false;
      
      for(int j = 0; j < 5000 - i - 1; j++) {
          if(arr[j] > arr[j + 1]) {
            int t = arr[j];
            arr[j] = arr[j + 1];
            arr[j + 1] = t;
            swaps++;
            swapped = true;
          }
          comps++;
      }
      
      if(swapped == false) {
          break;
      }
    }
    
    cout << "Bubble Sort:" << endl << "Element Comparisons: " << comps << ", Swaps Made: " << swaps << endl << endl;
}

void selectionSort(int arr[]) { // O(n^2)
   int min_idx, comps = 0, swaps = 0;
   
   for(int i = 0; i < 5000 - 1; i++) {
       min_idx = i;
       for(int j = i + 1; j < 5000; j++) {
           if(arr[j] < arr[min_idx]) {
               min_idx = j;
           }
           comps++;
       }
       
       if(min_idx != i) {
           int t = arr[min_idx];
           arr[min_idx] = arr[i];
           arr[i] = t;
           swaps++;
       }
   }
    cout << "Selection Sort:" << endl << "Element Comparisons: " << comps << ", Swaps Made: " << swaps << endl << endl;
}

void insertionSort(int arr[]) { // O(n^2)
    int key, comps = 0, swaps = 0;
    
    for(int i = 0; i < 5000; i++) {
        key = arr[i];
        int j = i - 1;
        
        while(j >= 0 && arr[j] > key) {
            comps++;
            arr[j + 1] = arr[j];
            swaps++;
            j = j - 1;
        }
        comps++;
        arr[j + 1] = key;
        swaps++;
    }
        cout << "Insertion Sort:" << endl << "Element Comparisons: " << comps << ", Swaps Made: " << swaps << endl << endl;
}

int partition(int ar[], int st, int en) {
    int pivot = ar[st];
    int count = 0;
    
    for(int i = st + 1; i <= en; i++) {
        if(ar[i] <= pivot) {
            count++;
        }
    }
    
    int pivotIndex = st + count;
    
    int t = ar[st];
    ar[st] = ar[pivotIndex];
    ar[pivotIndex] = t;
    
    
    int i = st, j = en;
    
    while(i < pivotIndex && j > pivotIndex) {
        while(ar[i] <= pivot) {
            i++;
        }
        
        while(ar[j] > pivot) {
            j--;
        }
        
        if(i < pivotIndex && j > pivotIndex) {
            int temp = ar[j - 1];
            ar[j - 1] = ar[i + 1];
            ar[i + 1] = temp;
        }
    }
    return pivotIndex;
}

void quickSort(int arr[], int s, int e) { // O(log n)
    int p = partition(arr, s, e);
    quickSort(arr, s, p - 1);
    quickSort(arr, p + 1, e);
}

void mergeSort(int* list) { // O(log n)
    
} 

int main()
{
    int arr1[5000], arr2[5000], arr3[5000], arr4[5000];
    list<int>list1;
    
    for(int i = 0; i < 5000; i++) {
        int a = rand();
        
        arr1[i] = arr2[i] = arr3[i] = arr4[i] = a;
        list1.push_back(a);
    }
    
    bubbleSort(arr1);
    selectionSort(arr2);
    insertionSort(arr3);
    //quickSort(arr4, 0, 4999);
    //mergeSort(list1);
    
}

