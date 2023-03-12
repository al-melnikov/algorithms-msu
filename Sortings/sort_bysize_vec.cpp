# include <iostream>
# include <random>
# include <chrono>
# include <vector>
# include <fstream>
# include <iterator>


#define MAX_ARRAY_SIZE 1000000
#define MAX_NUMBER 50000
#define SORT_TIMES 50

#define ARRAY_SIZE 1000


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
void VectorCopy(const std::vector<T> &from, std::vector<T> &to){
    to.resize(from.size());

    for (uint i = 0; i < from.size(); i++){
        to[i] = from[i];
    }
}


template <typename T>
void ShellSort(std::vector<T> &myVector){

    int h = 0;

    while (h < myVector.size()/3){
        h = h*3 + 1;
    }

    if ( (h==0) and (myVector.size() == 2) ){
        if (myVector[0] > myVector[1]){
            int tmp = myVector[1];
            myVector[1] = myVector[0];
            myVector[0] = tmp;
        }
    }

    while (h >= 1){
        for (int i = h; i < myVector.size(); i++){
            for (int j = i; (j >= h) and (myVector[j] < myVector[j-h]); j -= h){
                int tmp = myVector[j];
                myVector[j] = myVector[j-h];
                myVector[j-h] = tmp;
            }
        }
        h = h/3;
    }

}


template <typename T>
void heapify(std::vector<T> &myVector, int length, int i){
    int biggest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if ( (l < length) and (myVector[l] > myVector[biggest]) ){
        biggest = l;
    }

    if ( (r < length) and (myVector[r] > myVector[biggest]) ){
        biggest = r;
    }

    if (biggest != i){
        int tmp = myVector[biggest];
        myVector[biggest] = myVector[i];
        myVector[i] = tmp;

        heapify(myVector, length, biggest);
    }
}

template <typename T>
void HeapSort(std::vector<T> &myVector){

    for (int i = myVector.size()/2 - 1; i >= 0; i--){
        heapify(myVector, myVector.size(), i);
    }

    for (int i = myVector.size()-1; i >= 0; i--){
        int tmp = myVector[0];
        myVector[0] = myVector[i];
        myVector[i] = tmp;

        heapify(myVector, i, 0); //problem here
    }
}




int main()
{
    std::ofstream shellsort_file;
    shellsort_file.open("Shell_out_vec.csv");
    for (uint array_size = 1; array_size <= MAX_ARRAY_SIZE; array_size += 10000){

        // Матрица массивов размера array_size чтобы усренить время сортировки массива конкретного размера
        std::vector<std::vector<int>> matrix(SORT_TIMES);
        for (uint j = 0; j < SORT_TIMES; j++){
            VectorRandomInt(matrix[j], array_size, 0, MAX_NUMBER);
        }

        // здесь массивы размера array_size сортируются SORT_TIMES раз
        auto start = std::chrono::high_resolution_clock::now();
        for (uint j = 0; j < SORT_TIMES; j++){
            ShellSort(matrix[j]);
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        shellsort_file << array_size << '\t' << (double)duration.count()/SORT_TIMES << std::endl;

        std::cout << array_size << " size array is sorted in " << (double)duration.count()/SORT_TIMES 
                            << " microseconds" << " with Shell sort" << std::endl;


    }
    shellsort_file.close(); 


    std::ofstream heapsort_file;
    heapsort_file.open("Heap_out_vec.csv");
    for (uint array_size = 1; array_size <= MAX_ARRAY_SIZE; array_size += 10000){

        // Матрица массивов размера array_size чтобы усренить время сортировки массива конкретного размера
        std::vector<std::vector<int>> matrix(SORT_TIMES);
        for (uint j = 0; j < SORT_TIMES; j++){
            VectorRandomInt(matrix[j], array_size, 0, MAX_NUMBER);
        }

        // здесь массивы размера array_size сортируются SORT_TIMES раз
        auto start = std::chrono::high_resolution_clock::now();
        for (uint j = 0; j < SORT_TIMES; j++){
            HeapSort(matrix[j]);
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        heapsort_file << array_size << '\t' << (double)duration.count()/SORT_TIMES << std::endl;

        std::cout << array_size << " size array is sorted in " << (double)duration.count()/SORT_TIMES 
                            << " microseconds" << " with Heap sort" << std::endl;


    }
    heapsort_file.close(); 



    return(0);
}