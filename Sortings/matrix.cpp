# include <iostream>
# include <array>
# include <random>
# include <chrono>
# include <fstream>

#define ARRAY_SIZE 10000
#define SORT_TIMES 3


void ArrayRandom(std::array<int, ARRAY_SIZE> *a, int min, int max){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(min, max);

    for (int i = 0; i < a->size(); i++){
        (*a)[i] = distr(gen);
    }
}

void MatrixRandom(std::array< std::array<int, ARRAY_SIZE>, 2*ARRAY_SIZE-1 > *matrix, int min, int max){
    for (int i = 0; i < (matrix -> size()); i++){
        ArrayRandom( &(*matrix)[i], min, max );
    }
}

void PrintArray(std::array<int, ARRAY_SIZE> *a){
    for (int i = 0; i < ( a -> size() ); i++){
        std::cout << (*a)[i] << "   ";
    }
    std::cout << std::endl;
}

void PrintMatrix(std::array< std::array<int, ARRAY_SIZE>, 2*ARRAY_SIZE-1 > *matrix){
    for (int i = 0; i < (matrix -> size()); i++){
        PrintArray( &(*matrix)[i] );
    }
}

void PrintMatrix(std::array< std::array<int, ARRAY_SIZE>, SORT_TIMES > *matrix){
    for (int i = 0; i < (matrix -> size()); i++){
        PrintArray( &(*matrix)[i] );
    }
}

void ArrayCopy(std::array<int, ARRAY_SIZE> *from, std::array<int, ARRAY_SIZE> *to){
    for (int i = 0; i < (from -> size()); i++){
        (*to)[i] = (*from)[i];
    }
}

void FillMatrix(std::array< std::array<int, ARRAY_SIZE>, SORT_TIMES > *matrix, std::array<int, ARRAY_SIZE> *a){

    for (int i = 0; i < SORT_TIMES; i++){
        ArrayCopy(a, &(*matrix)[i]);
    }
}

void BubbleMatrix(std::array< std::array<int, ARRAY_SIZE>, 2*ARRAY_SIZE-1 > *matrix){
    // По убыванию
    for(int i = ARRAY_SIZE; i < 2*ARRAY_SIZE-1; i++){
        ArrayCopy( &(*matrix)[i-1], &(*matrix)[i]);
        for (int j=0; j < ARRAY_SIZE-1; j++){
            if ( (*matrix)[i][j] > (*matrix)[i][j+1] ){
                int tmp = (*matrix)[i][j];
                (*matrix)[i][j] = (*matrix)[i][j+1];
                (*matrix)[i][j+1] = tmp;
            }
        }
    }
    // по возрастанию
    for(int i = ARRAY_SIZE-2; i >= 0; i--){
        ArrayCopy( &(*matrix)[i+1], &(*matrix)[i]);
        for (int j=0; j < ARRAY_SIZE-1; j++){
            if ( (*matrix)[i][j] < (*matrix)[i][j+1] ){
                int tmp = (*matrix)[i][j];
                (*matrix)[i][j] = (*matrix)[i][j+1];
                (*matrix)[i][j+1] = tmp;
            }
        }
    }
}


void ShellSort(std::array<int, ARRAY_SIZE> *a){

    int h = 0;

    while(h < ARRAY_SIZE/3){
        h = h*3 + 1;
    }

    while(h >= 1){
        for(int i = h; i < ARRAY_SIZE; i++){
            for(int j = i; (j >= h) and ((*a)[j] < (*a)[j-h]); j -= h){ //!! j-- -> j -= h
                int tmp = (*a)[j];
                (*a)[j] = (*a)[j-h];
                (*a)[j-h] = tmp;
            }
        }
        h = h/3;
    }
}


void heapify(std::array<int, ARRAY_SIZE> *a, int length, int i){
    int biggest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if ( (l < length) and ((*a)[l] > (*a)[biggest]) ){
        biggest = l;
    }

    if ( (r < length) and ((*a)[r] > (*a)[biggest]) ){
        biggest = r;
    }

    if (biggest != i){
        int tmp = (*a)[biggest];
        (*a)[biggest] = (*a)[i];
        (*a)[i] = tmp;

        heapify(a, length, biggest);
    }
}


void HeapSort(std::array<int, ARRAY_SIZE> *a){

    for (int i = ARRAY_SIZE/2 - 1; i >= 0; i--){
        heapify(a, ARRAY_SIZE, i);
    }

    for (int i = ARRAY_SIZE-1; i >= 0; i--){
        int tmp = (*a)[0];
        (*a)[0] = (*a)[i];
        (*a)[i] = tmp;

        heapify(a, i, 0); //problem here
    }
}



int main()
{
    //std::array<int, ARRAY_SIZE> arr;
    //PrintArray(&arr);
    //ArrayRandom(&arr, 0, 300);
    //PrintArray(&arr);
    //std::array<int, ARRAY_SIZE> arr1;
    //PrintArray(&arr1);
    //ArrayCopy(&arr, &arr1);
    //PrintArray(&arr1);
    //ShellSort(&arr);
    //HeapSort(&arr);
    //PrintArray(&arr);
    //std::array< std::array<int, ARRAY_SIZE>, 2*ARRAY_SIZE-1 > matrix;
    //ArrayRandom( &matrix[ARRAY_SIZE-1], 0, 100 );
    //MatrixRandom(&matrix, 0, 5);
    //PrintMatrix(&matrix);
    //BubbleMatrix(&matrix);
    //PrintMatrix(&matrix);



/*
     //Stack overflow
    //шаблон
    std::cout << "1 mark" << std::endl;
    std::array<int, ARRAY_SIZE> templ;
    ArrayRandom(&templ, 0 , 50000);
    std::cout << "1 mark" << std::endl;
    //матрица
    std::array< std::array<int, ARRAY_SIZE>, 2*ARRAY_SIZE-1 > matrix;
    ArrayCopy(&templ, &matrix[ARRAY_SIZE-1]);
    BubbleMatrix(&matrix);
    //PrintMatrix(&matrix);

    // Shell sort
    std::ofstream shellsort_file;
    shellsort_file.open("Shell_out.csv");
    for (int arr_nomber=0; arr_nomber < 2*ARRAY_SIZE-1; arr_nomber++){
        auto start = std::chrono::high_resolution_clock::now();
        ShellSort(&matrix[arr_nomber]);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        shellsort_file << arr_nomber << '\t' << duration.count() << std::endl;
        std::cout << arr_nomber << " array is sorted in " << duration.count() 
                            << " microseconds" << " with Shell sort" << std::endl;
    }

    //PrintMatrix(&matrix);

    ArrayCopy(&templ, &matrix[ARRAY_SIZE-1]);
    BubbleMatrix(&matrix);

    //PrintMatrix(&matrix);
    //Heap sort
    std::ofstream heapsort_file;
    heapsort_file.open("Heap_out.csv");
    for (int arr_nomber=0; arr_nomber < 2*ARRAY_SIZE-1; arr_nomber++){
        auto start = std::chrono::high_resolution_clock::now();
        HeapSort(&matrix[arr_nomber]);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        heapsort_file << arr_nomber << '\t' << duration.count() << std::endl;
        std::cout << arr_nomber << " array is sorted in " << duration.count() 
                            << " microseconds" << " with Heap sort" << std::endl;
    }
    //PrintMatrix(&matrix);
*/

//шаблон
    std::cout << "start" << std::endl;
    std::array<int, ARRAY_SIZE>* templ = new std::array<int, ARRAY_SIZE>;
    ArrayRandom(templ, 0 , 50000);
    //матрица
    std::cout << "generated random" << std::endl;
    std::array< std::array<int, ARRAY_SIZE>, 2*ARRAY_SIZE-1 >* matrix;
    matrix = new std::array< std::array<int, ARRAY_SIZE>, 2*ARRAY_SIZE-1 >;
    std::cout << "allocated memory for matrix" << std::endl;
    ArrayCopy(templ, &(*matrix)[ARRAY_SIZE-1]);
    std::cout << "copied array" << std::endl;
    BubbleMatrix(matrix);
    std::cout << "made bubble matrix" << std::endl;
    //PrintMatrix(&matrix);


    std::array< std::array<int, ARRAY_SIZE>, SORT_TIMES >* matrix_to_sort;
    matrix_to_sort = new std::array< std::array<int, ARRAY_SIZE>, SORT_TIMES >;




    // Shell sort
    std::ofstream shellsort_file;
    shellsort_file.open("Shell_out.csv");
    for (int arr_nomber=0; arr_nomber < 2*ARRAY_SIZE-1; arr_nomber++){
        auto start = std::chrono::high_resolution_clock::now();
        ShellSort(&(*matrix)[arr_nomber]);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        shellsort_file << arr_nomber << '\t' << duration.count() << std::endl;
        std::cout << arr_nomber << " array is sorted in " << duration.count() 
                            << " microseconds" << " with Shell sort" << std::endl;
    }

    //PrintMatrix(&matrix);

    ArrayCopy(templ, &(*matrix)[ARRAY_SIZE-1]);
    BubbleMatrix(matrix);

    //PrintMatrix(&matrix);
    //Heap sort
    std::ofstream heapsort_file;
    heapsort_file.open("Heap_out.csv");
    for (int arr_nomber=0; arr_nomber < 2*ARRAY_SIZE-1; arr_nomber++){
        auto start = std::chrono::high_resolution_clock::now();
        HeapSort(&(*matrix)[arr_nomber]);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        heapsort_file << arr_nomber << '\t' << duration.count() << std::endl;
        std::cout << arr_nomber << " array is sorted in " << duration.count() 
                            << " microseconds" << " with Heap sort" << std::endl;
    }


    delete templ;
    delete matrix;
    delete matrix_to_sort;

/*
    std::array< std::array<int, ARRAY_SIZE>, SORT_TIMES >* matrix_to_sort;
    matrix_to_sort = new std::array< std::array<int, ARRAY_SIZE>, SORT_TIMES >;

    std::array<int, ARRAY_SIZE> *a = new std::array<int, ARRAY_SIZE>;
    ArrayRandom(a, 0, 10);
    PrintArray(a);
    PrintMatrix(matrix_to_sort);
    FillMatrix(matrix_to_sort, a);
    PrintMatrix(matrix_to_sort);
*/
    return(0);
}