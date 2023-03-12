#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>

#define ARRAY_SIZE 10000
#define SORT_TIMES 1



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


void MatrixRandomInt(std::vector< std::vector<int> > &matrix, int min, int max, uint size = ARRAY_SIZE){
    matrix.resize(size*2 - 1);
    for(int i = 0; i < matrix.size(); i++){
        VectorRandomInt(matrix[i], size, min, max);
    }
}


template <typename T>
void PrintMatrix(std::vector< std::vector<T> > &matrix){
    for (int i = 0; i < matrix.size(); i++){
        PrintVector(matrix[i]);
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
void FillMatrix(std::vector< std::vector<T> > &matrix, std::vector<T> arr, uint times){
    matrix.resize(times);
    for (int i = 0; i < times; i++){
        VectorCopy(arr, matrix[i]);
    }
}



template <typename T>
void BubbleMatrix(std::vector< std::vector<T> > &matrix, std::vector<T> &templ){
    uint size = templ.size();
    size = ARRAY_SIZE;
    matrix.resize(2*size - 1);
    VectorCopy(templ, matrix[size-1]);

    //по возрастанию
    for (int i = size; i < 2*size - 1; i++){
        VectorCopy(matrix[i-1], matrix[i]);
        for (int j = 0; j < size-1; j++){
            if (matrix[i][j] > matrix[i][j+1]){
                int tmp = matrix[i][j];
                matrix[i][j] = matrix[i][j+1];
                matrix[i][j+1] = tmp;
            }
        }
    }
    //по убыванию
    for (int i = size-2; i >= 0; i--){
        VectorCopy(matrix[i+1], matrix[i]);
        for (int j = 0; j < size-1; j++){
            if (matrix[i][j] < matrix[i][j+1]){
                int tmp = matrix[i][j];
                matrix[i][j] = matrix[i][j+1];
                matrix[i][j+1] = tmp;
            }
        }
    }

}



/*
template <typename T>
int partition(std::vector<T> &A, int start, int end){ 

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(start, end);
    int pivotIndex = distr(gen);

	int temp;
	int pivot = A[pivotIndex];
    std::swap(A[pivotIndex], A[end]);
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
*/
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
        //наверно надо сортировать сначала с меньшей длиной будет быстрее
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
    std::cout << "start" << std::endl;
    std::vector<int> templ;
    VectorRandomInt(templ, ARRAY_SIZE, 0, 50000);

/*
    auto start = std::chrono::high_resolution_clock::now();
    quick_sort(templ);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "sort time " << duration.count() << std:: endl; 

    start = std::chrono::high_resolution_clock::now();
    quick_sort(templ);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "sort time " << duration.count() << std:: endl; 

    VectorRandomInt(templ, ARRAY_SIZE, 0, 50000);

    start = std::chrono::high_resolution_clock::now();
    merge_sort(templ);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "sort time " << duration.count() << std:: endl; 

    start = std::chrono::high_resolution_clock::now();
    merge_sort(templ);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "sort time " << duration.count() << std:: endl; 
*/


    std::vector< std::vector<int> > matrix_to_sort;
    //matrix
    std::vector< std::vector<int> > matrix;
    BubbleMatrix(matrix, templ);



    //merge sort
    std::ofstream mergesort_file;
    mergesort_file.open("merge_out.csv");

    for (int arr_number = 0; arr_number < matrix.size(); arr_number++){

        FillMatrix(matrix_to_sort, matrix[arr_number], SORT_TIMES);
        std::cout << "filled matrix with " << arr_number << " array" << std::endl;

        auto start = std::chrono::high_resolution_clock::now();
        for (int time = 0; time < SORT_TIMES; time++){
            merge_sort(matrix_to_sort[time]);
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        mergesort_file << arr_number << '\t' << (double)duration.count()/SORT_TIMES << std::endl;
        std::cout << arr_number << " array is sorted in " << (double)duration.count()/SORT_TIMES 
                            << " microseconds" << " with merge sort" << std::endl;
    }
    mergesort_file.close();

    

    BubbleMatrix(matrix, templ);

    //quick sort
    std::ofstream quicksort_file;
    quicksort_file.open("quick_out.csv");

    for (int arr_number = 0; arr_number < matrix.size(); arr_number++){

        FillMatrix(matrix_to_sort, matrix[arr_number], SORT_TIMES);
        std::cout << "filled matrix with " << arr_number << " array" << std::endl;

        auto start = std::chrono::high_resolution_clock::now();
        for (int time = 0; time < SORT_TIMES; time++){
            quick_sort(matrix_to_sort[time]);
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        quicksort_file << arr_number << '\t' << (double)duration.count()/SORT_TIMES << std::endl;
        std::cout << arr_number << " array is sorted in " << (double)duration.count()/SORT_TIMES 
                            << " microseconds" << " with quick sort" << std::endl;
    }
    quicksort_file.close();





    return(0);
}
