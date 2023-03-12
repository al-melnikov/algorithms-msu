#include <iostream>
#include <vector>
#include <random>
#include <chrono>


template <typename T>
void PrintVector(std::vector<T> const &input){
    for (auto const &i : input) {
        std::cout << i << "   ";
    }
    std::cout << std::endl;
}


template <typename T>
int partition(std::vector<T> &A, int start, int end){ 

	int temp;
    int pivotIndex = (start+end)/2;
    //std::swap(A[pivotIndex], A[end]);
	int pivot = A[end];
	int partitionIndex = start; // set partition index as start initially

	for(int i=start; i<end; i++){
		if(A[i] < pivot){
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
    std:: vector<int> array;
    VectorRandomInt(array, 10000, 0, 100);
    //PrintVector(array);
    //QuickSort(array, 0, array.size()-1);
    //quick_sort(array, 0, array.size()-1);
    quick_sort(array);
    auto start = std::chrono::high_resolution_clock::now();
    quick_sort(array);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout<< (double)duration.count() << " microseconds" << std::endl;
    //PrintVector(array);

    return(0);
}