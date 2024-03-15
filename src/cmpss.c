#include <stdio.h>
#include <stdbool.h>

unsigned int compressData(unsigned int x, unsigned int y, unsigned int n, unsigned int p) {
    if (n >= 8 * sizeof(x) || p >= 8 * sizeof(y)) {
        // Invalid compression parameters
        return 0;
    }

    y &= (1 << n) - 1;
    y <<= p;
    x <<= n;
    return x | y;
}

bool decompressData(unsigned int compressed, unsigned int n, unsigned int p, unsigned int *x, unsigned int *y) {
    if (n + p > 8 * sizeof(compressed)) {
        // Invalid compression parameters
        return false;
    }

    *x = compressed;
    *y = compressed;

    *x >>= n;
    *y <<= 8 * sizeof(*y) - n;
    *y >>= 8 * sizeof(*y) - n;

    return true;
}

int cmpss() {
    unsigned int x = 12345;  // Example value for x
    unsigned int y = 67890;  // Example value for y
    unsigned int n = 4;      // Number of bits to preserve
    unsigned int p = 2;      // Number of positions to shift y

    printf("Original values:\n");
    printf("x: %u\n", x);
    printf("y: %u\n\n", y);

    unsigned int compressed = compressData(x, y, n, p);
    if (compressed != 0) {
        printf("Compressed value: %u\n\n", compressed);

        unsigned int decompressed_x, decompressed_y;
        if (decompressData(compressed, n, p, &decompressed_x, &decompressed_y)) {
            printf("Decompressed values:\n");
            printf("x: %u\n", decompressed_x);
            printf("y: %u\n", decompressed_y);
        } else {
            printf("Invalid compression parameters. Decompression failed.\n");
        }
    } else {
        printf("Invalid compression parameters. Compression failed.\n");
    }

    return 0;
}