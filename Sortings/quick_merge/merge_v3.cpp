# include <iostream>
# include <vector>
# include <random>
# include <chrono>

std::vector<int> buffer(1000000);

template <typename T>
void merge(std::vector<T> &a, int left, int middle, int right){
    
    int size_left = middle - left + 1;
    int size_right = right - middle;

    //надо сделать без копирования`
    /* temp arrays */

    for (int i = 0; i < size_left; i++){
        buffer[left+i] = a[left+i];
    }
    for (int j = 0; j < size_right; j++){
        buffer[middle+1+j] = a[middle+1+j];
    }

    //Merge part

    int i = 0;
    int j = 0;
    int k = left;

    while (i < size_left and j < size_right){
        if (buffer[left+i] < buffer[middle+1+j]){
            a[k] = buffer[left+i];
            i++;
        } else {
            a[k] = buffer[middle+1+j];
            j++;
        }
        k++;
    }

    while (i < size_left){
        a[k] = buffer[left+i];
        i++;
        k++;
    }

    while (j < size_right){
        a[k] = buffer[middle+1+j];
        j++;
        k++;
    }
}


template <typename T>
void merge_sort(std::vector<T> &a, int left = 0, int right = -5){
    if (right == -5){
        right = a.size() - 1;
    }

    if (left < right){
        int middle = left + (right - left)/2;

        merge_sort(a, left, middle);
        merge_sort(a, middle+1, right);

        merge(a, left, middle, right);
    }
}

template <typename T>
void PrintVector(std::vector<T> const &input){
    for (auto const &i : input) {
        std::cout << i << "   ";
    }
    std::cout << std::endl;
}


void VectorRandomInt(std::vector<int> &myVector, uint size, int min, int max){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(min, max);


    myVector.resize(size);
    for (uint i = 0; i < size; i++){
        myVector[i] = distr(gen);
    }
}



int main()
{
    std::vector<int> arrr {10,9,8,7,6,5,4,3,2}; 
    std::vector<int> array;
    PrintVector(arrr);
    //VectorRandomInt(array, 10, 0, 100);
    //PrintVector(array);
    auto start = std::chrono::high_resolution_clock::now();
    merge_sort(arrr);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout<< (double)duration.count() << " microseconds" << std::endl;
    PrintVector(arrr);

    return(0);
}