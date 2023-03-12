#include <iostream>
#include <random>
#include <chrono>
#include <fstream>

#define NUMBER_OF_ARRAYS 10000

void PrintArray(int *a, int length){
    for (int i = 0; i<length; i++){
        std::cout << a[i] << ' ';
    }
    std::cout << std::endl;
}

void ArrayRandom(int *a, int length, int min, int max){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(min, max);

    for (int i = 0; i < length; i++){
        a[i] = distr(gen);
    }
}

void GenerateArrayReversed(int *a, int length){
    for (int i = 0; i < length; i++){
        a[i] = length - i;
    }
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


void ShellSort(int *a, int length){

    int h = 0;

    while(h < length/3){
        h = h*3 + 1;
    }

    while(h >= 1){
        for(int i = h; i < length; i++){
            for(int j = i; (j >= h) and (a[j] < a[j-h]); j -= h){ //!! j-- -> j -= h
                int tmp;
                tmp = a[j];
                a[j] = a[j-h];
                a[j-h] = tmp;
            }
        }
        h = h/3;
    }
}


int main()
{
    int a[] = {1, 2, 3, 4 ,5 ,6};
    int length = sizeof(a)/sizeof(a[0]);
    PrintArray(a, length);
    ArrayRandom(a, length, 1, 100);
    PrintArray(a, length);

    //Shell sort
    std::ofstream shellsort_file;
    shellsort_file.open("Shell_out.csv");
    for (int length = 1; length <= NUMBER_OF_ARRAYS; length++){
        int a[length];
        ArrayRandom(a, length, 0, length);
        //GenerateArrayReversed(a, length);

        auto start = std::chrono::high_resolution_clock::now();
        ShellSort(a, length);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        shellsort_file << length << '\t' << duration.count() << std::endl;
        std::cout << length << " size array is sorted in " << duration.count() 
                            << " microseconds" << " with Shell sort" << std::endl;
    }
    shellsort_file.close();


    //Heap sort
    std::ofstream heapsort_file;
    heapsort_file.open("Heap_out.csv");
    for (int length = 1; length <= NUMBER_OF_ARRAYS; length++){
        int a[length];
        ArrayRandom(a, length, 0, length);
        //GenerateArrayReversed(a, length);

        auto start = std::chrono::high_resolution_clock::now();
        HeapSort(a, length);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        heapsort_file << length << '\t' << duration.count() << std::endl;
        std::cout << length << " size array is sorted in " << duration.count() 
                            << " microseconds" << " with heap sort" << std::endl;
    }
    heapsort_file.close();

    return(0);
}