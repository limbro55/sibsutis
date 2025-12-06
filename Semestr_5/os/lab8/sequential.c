#include "common.h"


int main() {
int* array = malloc(ARRAY_SIZE * sizeof(int));
for (size_t i = 0; i < ARRAY_SIZE; i++) {
array[i] = 1;
}


double start_time = get_time();
long long sum = sequential_sum(array, ARRAY_SIZE);
double end_time = get_time();


printf("Sequential version:\n");
printf("Sum: %lld\n", sum);
printf("Time: %.6f seconds\n", end_time - start_time);


free(array);
return 0;
}