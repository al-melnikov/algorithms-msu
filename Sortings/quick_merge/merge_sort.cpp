#include <iostream>
#include <vector>
#include <random>


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



template <typename T>
void merge_sort(std::vector<T> &A, int start = 0, int end = -5){

    if (end == -5){
        end = A.size()-1;
    }

    if (start >= end){
        return;
    }

    int middle_index = (end-start) / 2;

    merge_sort(A, start, start+middle_index);
    merge_sort(A, start+middle_index+1, end); 

    std::vector<T> buffer;

    int left_i = start;
    int right_i = start+middle_index+1;

    while (left_i <= start+middle_index and right_i <= end) {
        if (A[left_i] <= A[right_i]) {
            buffer.push_back(A[left_i]);
            left_i++;
        } else {
            buffer.push_back(A[right_i]);
            right_i++;
        }
    }

    while (left_i <= start+middle_index) {
        buffer.push_back(A[left_i]);
        left_i++;
    }

    while (right_i <= end) {
        buffer.push_back(A[right_i]);
        right_i++;
    }

    for (int i = 0; i < buffer.size(); i++) {
        A[start+i] = buffer[i];
    }

    return;
}


int main()
{
    std::vector<int> array;
    VectorRandomInt(array, 20, 0, 10);
    PrintVector(array);
    merge_sort(array);
    PrintVector(array);

    return(0);
}
