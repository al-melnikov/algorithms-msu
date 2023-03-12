# include <iostream>
# include <random>
# include <chrono>
# include <array>
# include <fstream>

#define MAX_ARRAY_SIZE 1000000
#define MAX_NUMBER 50000
#define SORT_TIMES 100

#define ARRAY_SIZE 10


template <typename T, std::size_t size> // parameterize the element type and size
void PrintArray(const std::array<T, size> &myArray){
    for (auto element : myArray){
        std::cout << element << "   ";
    }
    std::cout << std::endl;
}


template <std::size_t size>
void ArrayRandomInt(std::array<int, size> &myArray, int min, int max){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(min, max);

    for (uint i = 0; i < myArray.size(); i++){
        myArray[i] = distr(gen);
    }
}


template <typename T, std::size_t size>
void ArrayCopy(const std::array<T, size> &from, std::array<T, size> &to){
    for (uint i = 0; i < from.size(); i++){
        to[i] = from[i];
    }
}


template <typename T, std::size_t size>
void ShellSort(std::array<T, size> &myArray){

    int h = 0;

    while (h < size/3){
        h = h*3 + 1;
    }

    while (h >= 1){
        for (int i = h; i < size; i++){
            for (int j = i; (j >= h) and (myArray[j] < myArray[j-h]); j -= h){
                int tmp = myArray[j];
                myArray[j] = myArray[j-h];
                myArray[j-h] = tmp;
            }
        }
        h = h/3;
    }

}


template <typename T, std::size_t size>
void heapify(std::array<T, size> &myArray, int length, int i){
    int biggest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if ( (l < length) and (myArray[l] > myArray[biggest]) ){
        biggest = l;
    }

    if ( (r < length) and (myArray[r] > myArray[biggest]) ){
        biggest = r;
    }

    if (biggest != i){
        int tmp = myArray[biggest];
        myArray[biggest] = myArray[i];
        myArray[i] = tmp;

        heapify(myArray, length, biggest);
    }
}

template <typename T, std::size_t size>
void HeapSort(std::array<T, size> &myArray){

    for (int i = size/2 - 1; i >= 0; i--){
        heapify(myArray, size, i);
    }

    for (int i = size-1; i >= 0; i--){
        int tmp = myArray[0];
        myArray[0] = myArray[i];
        myArray[i] = tmp;

        heapify(myArray, i, 0); //problem here
    }
}




int main()
{
    // типа генерируем массивы от 1 элемента до миллиона элементов, считаем время сортировки. 
    /*
    for (uint array_size = 1; array_size < MAX_ARRAY_SIZE; array_size++){
        std::array<int, array_size> *myArray = new std::array<int, array_size>;
        std::cout << "Allocated memory for " << array_size << " array" << std::endl;

        delete myArray;
        std::cout << "Deleted " << array_size << " array" << std::endl;
    } */

    int i = 5;
    std::array<int, ARRAY_SIZE> arr;
    PrintArray(arr);


    return(0);
}