#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

const int N = 10000;
const int numThreads = 16;

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

    thread* threads = new thread[numThreads];
    int chunkSize = N / numThreads;

    auto start_time = chrono::high_resolution_clock::now();

    for (int t = 0; t < numThreads; ++t) {
        int start_row = t * chunkSize;
        int end_row = (t == numThreads - 1) ? N : (t + 1) * chunkSize;

        threads[t] = thread([matrix, start_row, end_row]() {
            for (int i = start_row; i < end_row; ++i) {
                int limit = N - 1 - i;
                for (int j = 0; j < limit; ++j) {
                    swap(matrix[i][j], matrix[N - 1 - j][N - 1 - i]);
                }
            }
        });
    }

    for (int i = 0; i < numThreads; ++i) {
        threads[i].join();
    }

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    chrono::duration<double> duration_sec = end_time - start_time;

    cout << "Execution time: " << duration.count() << " microseconds || " << duration_sec.count() << " seconds" << endl;


    for (int i = 0; i < N; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    delete[] threads;

    return 0;
}
