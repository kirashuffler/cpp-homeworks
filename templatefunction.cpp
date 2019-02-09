#include <iostream>
#include <vector>
template<class T>
void ShellSort(T* A, unsigned N){
    T tmp;
    for(size_t k = N / 2; k > 0; k /= 2)
        for(size_t i = k; i < N; ++i){
           tmp = A[i];
          unsigned j;
         for(j = i; j >= k; j -= k){
            if (tmp < A[j - k])
               A[j] = A[j - k];
            else
               break;
         }
        A[j] = tmp;
        }
}

int main(){
    unsigned N;
    std::cin >> N;
    double* a = new double[N];
    for (size_t i = 0; i < N; ++i)
        std::cin >> a[i];
    ShellSort(a, N);
    for (size_t i = 0; i < N; ++i)
        std::cout << a[i] << ' ';
    delete[] a;
    return 0;
}

