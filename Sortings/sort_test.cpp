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


void ShellSort(int *a, int length){

    int h = 0;

    while(h < length/3){
        h = h*3 + 1;
    }

    while(h >= 1){
        for(int i = h; i < length; i++){
            for(int j = i; (j >= h) and (a[j] < a[j-h]); j -= h){ //j-- -> j -= h
                int tmp;
                tmp = a[j];
                a[j] = a[j-h];
                a[j-h] = tmp;
            }
        }
        h = h/3;
    }
}


void GenerateArrayReversed(int *a, int length){
    for (int i = 0; i < length; i++){
        a[i] = length - i;
    }
}



int main()
{
    int length = 40;
    int a[length];
    std::cout << "Длинны массивов "<< length << std::endl;

    std::cout << "Генерируем массив в обратном порядке" <<std::endl;
    GenerateArrayReversed(a, length);
    PrintArray(a, length);
    std::cout << "Shell sort" <<std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    ShellSort(a, length);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Время сортировкой Шелла " << duration.count() << " микросекунд" << std::endl;
    PrintArray(a, length);

    std::cout << std::endl;

    std::cout << "Генерируем массив в обратном порядке" <<std::endl;
    GenerateArrayReversed(a, length);
    PrintArray(a, length);
    std::cout << "Heap sort" <<std::endl;
    start = std::chrono::high_resolution_clock::now();
    HeapSort(a, length);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Время хип сортом " << duration.count() << " микросекунд" << std::endl;
    PrintArray(a, length);

    return(0);
}