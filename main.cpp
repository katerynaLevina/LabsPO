#include <iostream>
#include <chrono>
#include <random>

using namespace std;

const int N = 10000;

int main() {

    int** matrix = new int*[N];
    for (int i = 0; i < N; i++) {
        matrix[i] = new int[N];
    }


    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand();
        }
    }

    auto start_time = chrono::high_resolution_clock::now();

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N - 1 - i; ++j) {
            swap(matrix[i][j], matrix[N - 1 - j][N - 1 - i]);
        }
    }

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    chrono::duration<double> duration_sec = end_time - start_time;

    cout << "Execution time: " << duration.count() << " microseconds || " << duration_sec.count() << " seconds" << endl;


    for (int i = 0; i < N; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}
