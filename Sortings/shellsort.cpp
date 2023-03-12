#include <iostream>


void PrintArray(int *a, int length){
    for (int i = 0; i<length; i++){
        std::cout << a[i] << ' ';
    }
    std::cout << std::endl;
}


void ShellSort(int *a, int length){

    int h = 0;

    while(h < length/3){
        h = h*3 + 1;
    }

    while(h >= 1){
        for(int i = h; i < length; i++){
            for(int j = i; (j >= h) and (a[j] < a[j-h]); j--){
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
    int a[] = {27, 54, 23, 465, 43, 687, 323, 34, 35465, 12};
    int length = sizeof(a)/sizeof(a[0]);
    PrintArray(a, length);
    ShellSort(a, length);
    PrintArray(a, length);
    return(0);
}