# include <iostream>
# include <vector>
# include <random>

std::vector<int> buffer(1000000);

template <typename T>
void merge(std::vector<T> &a, int left, int middle, int right){
    
    int size_left = middle - left + 1;
    int size_right = right - middle;

    //надо сделать без копирования
    /* temp arrays */
    std::vector<T> left_arr;
    left_arr.resize(size_left);
    std::vector<T> right_arr;
    right_arr.resize(size_right);

    for (int i = 0; i < size_left; i++){
        left_arr[i] = a[left+i];
    }
    for (int j = 0; j < size_right; j++){
        right_arr[j] = a[middle+1+j];
    }

    //Merge part

    int i = 0;
    int j = 0;
    int k = left;

    while (i < size_left and j < size_right){
        if (left_arr[i] < right_arr[j]){
            a[k] = left_arr[i];
            i++;
        } else {
            a[k] = right_arr[j];
            j++;
        }
        k++;
    }

    while (i < size_left){
        a[k] = left_arr[i];
        i++;
        k++;
    }

    while (j < size_right){
        a[k] = right_arr[j];
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
    std::vector<int> array;
    PrintVector(array);
    VectorRandomInt(array, 10, 0, 100);
    PrintVector(array);
    merge_sort(array);
    PrintVector(array);

    return(0);
}