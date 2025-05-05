#include <stdio.h>
#include <stdlib.h>
#include <limits.h>  // For UINT_MAX

int main() {
    unsigned int num_elements;
    printf("Enter number of integers to allocate: ");
    scanf("%u", &num_elements);

    // Check for integer overflow during size calculation
    if (num_elements > UINT_MAX / sizeof(int)) {
        printf("Integer overflow detected! Allocation aborted.\n");
        return 1;
    }

    unsigned int total_size = num_elements * sizeof(int);
    printf("Allocating %u bytes\n", total_size);

    int *array = (int *)malloc(total_size);  // malloc is now declared via stdlib.h
    if (!array) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Write to the allocated memory
    for (unsigned int i = 0; i < num_elements; i++) {
        array[i] = i;
        if (i % 100000000 == 0)
            printf("Wrote %u elements...\n", i);
    }

    printf("Memory write completed\n");
    free(array);
    return 0;
}
