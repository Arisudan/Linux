#include <stdio.h>
#include <stdlib.h>

int main() {
    unsigned int num_elements;
    printf("Enter number of integers to allocate: ");
    scanf("%u", &num_elements);

    unsigned int total_size = num_elements * sizeof(int);  // Vulnerable: no overflow check
    printf("Allocating %u bytes\n", total_size);

    int *array = (int *)malloc(total_size);
    if (!array) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Force memory write to trigger crash on overflow
    for (unsigned int i = 0; i < num_elements; i++) {
        array[i] = i;
        if (i % 100000000 == 0)
            printf("Wrote %u elements...\n", i);
    }

    printf("Memory write completed\n");
    free(array);
    return 0;
}
