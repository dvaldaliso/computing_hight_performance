#include <stdio.h>
#include <omp.h>

int main() {
    int sum = 0;
    int n = 5;

    #pragma omp parallel for schedule(dynamic) reduction(-:sum)
    for (int i = 0; i < n; i++) {
        sum += i;
    }

    printf("Resultado de la suma: %d\n", sum);

    return 0;
}