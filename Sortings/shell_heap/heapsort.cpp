#include <iostream>
#include <chrono>

void PrintArray(int *a, int length){
    for (int i = 0; i<length; i++){
        std::cout << a[i] << ' ';
    }
    std::cout << std::endl;
}


void heapify(int *a, int length, int i){
    int biggest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < length and a[l] > a[biggest]){
        biggest = l;
    }

    if (r < length and a[r] > a[biggest]){
        biggest = r;
    }

    if (biggest != i){
        int tmp = a[biggest];
        a[biggest] = a[i];
        a[i] = tmp;

        heapify(a, length, biggest);
    }

}


void HeapSort(int *a, int length){

    for (int i = length/2 - 1; i >= 0; i--){
        heapify(a, length, i);
    }

    for (int i = length-1; i >= 0; i--){
        int tmp = a[0];
        a[0] = a[i];
        a[i] = tmp;

        heapify(a, i, 0);
    }
}


int main()
{
    int array[] = {12, 11, 13, 5, 6, 7};
    int length = sizeof(array)/sizeof(array[0]);
    PrintArray(array, length);
    auto start = std::chrono::high_resolution_clock::now();
    HeapSort(array, length);
    auto stop = std::chrono::high_resolution_clock::now();
    PrintArray(array, length);
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    std::cout << "Time duration: " << duration.count() << " nanoseconds" << std::endl;
    return(0);
}