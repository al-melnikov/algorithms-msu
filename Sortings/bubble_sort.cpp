#include <iostream>

void PrintArray(int *a, int length){
    for (int i = 0; i<length; i++){
        std::cout << a[i] << ' ';
    }
    std::cout << std::endl;
}

void BubbleSort(int *a, int length){
    PrintArray(a, length);
    std::cout << "---------------------------" << std::endl;
    for (int i=0; i<length-1; i++){
        for(int j=0; j < length-i-1; j++){
            if (a[j] < a[j+1]){ //по убыванию
                int tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
            }
        }
        PrintArray(a, length);
    }
    std::cout << "---------------------------" << std::endl;
    PrintArray(a, length);
}


int main()
{
    int a[5] = {1,2,3,4,5};

    //PrintArray(a, 5);

    BubbleSort(a, 5);

    //PrintArray(a, 5);


    return(0);
}