#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>

#define MAX_ARRAY_SIZE 1000000
#define MAX_NUMBER 50000
#define SORT_TIMES 50

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
void VectorCopy(std::vector<T> &from, std::vector<T> &to){
    to.resize( from.size() );
    for (int i = 0; i < from.size(); i++){
        to[i] = from[i];
    }
}




template <typename T>
int partition(std::vector<T> &A, int start, int end){ 

	int temp;
	int pivot = A[end];
	int partitionIndex = start; // set partition index as start initially

	for(int i=start; i<end; i++){
		if(A[i] <= pivot){
			std::swap(A[i], A[partitionIndex]);
			partitionIndex++;
		}
	}
	std::swap(A[partitionIndex], A[end]);		//	partition index

	return partitionIndex;
}


template <typename T>
void quick_sort( std::vector<T> &A, int start = 0, int end = -5 ){

    if (end == -5){
        end = A.size() - 1;
    }
	
	if (start < end){
		int partitionIndex = partition(A, start, end);
		quick_sort(A, start, partitionIndex-1);
		quick_sort(A, partitionIndex+1, end);
	}

    return;
}





template <typename T>
void merge(std::vector<T> &a, int left, int middle, int right){
    
    int size_left = middle - left + 1;
    int size_right = right - middle;

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





int main()
{
    //merge sort
    std::ofstream mergesort_file;
    mergesort_file.open("merge_out_vec.csv");
    for (uint array_size = 1; array_size <= MAX_ARRAY_SIZE; array_size += 10000){

        // Матрица массивов размера array_size чтобы усренить время сортировки массива конкретного размера
        std::vector<std::vector<int>> matrix(SORT_TIMES);
        for (uint j = 0; j < SORT_TIMES; j++){
            VectorRandomInt(matrix[j], array_size, 0, MAX_NUMBER);
        }

        // здесь массивы размера array_size сортируются SORT_TIMES раз
        auto start = std::chrono::high_resolution_clock::now();
        for (uint j = 0; j < SORT_TIMES; j++){
            merge_sort(matrix[j]);
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        mergesort_file << array_size << '\t' << (double)duration.count()/SORT_TIMES << std::endl;

        std::cout << array_size << " size array is sorted in " << (double)duration.count()/SORT_TIMES 
                            << " microseconds" << " with merge sort" << std::endl;


    }
    mergesort_file.close(); 


    //quick sort
    std::ofstream quicksort_file;
    quicksort_file.open("quick_out_vec.csv");
    for (uint array_size = 1; array_size <= MAX_ARRAY_SIZE; array_size += 10000){

        // Матрица массивов размера array_size чтобы усренить время сортировки массива конкретного размера
        std::vector<std::vector<int>> matrix(SORT_TIMES);
        for (uint j = 0; j < SORT_TIMES; j++){
            VectorRandomInt(matrix[j], array_size, 0, MAX_NUMBER);
        }

        // здесь массивы размера array_size сортируются SORT_TIMES раз
        auto start = std::chrono::high_resolution_clock::now();
        for (uint j = 0; j < SORT_TIMES; j++){
            quick_sort(matrix[j]);
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        quicksort_file << array_size << '\t' << (double)duration.count()/SORT_TIMES << std::endl;

        std::cout << array_size << " size array is sorted in " << (double)duration.count()/SORT_TIMES 
                            << " microseconds" << " with quick sort" << std::endl;


    }
    quicksort_file.close(); 



    return(0);
}