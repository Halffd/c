#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

bool pesqrec(const double v[], int i, int j, double r) {
    if (i > j)
        return false;

    int mid = (i + j) / 2;

    if (v[mid - 1] == r)  // -1 because your array is 1-indexed in pseudocode, C is 0-indexed
        return true;
    else if (v[mid - 1] > r)
        return pesqrec(v, i, mid - 1, r);
    else
        return pesqrec(v, mid + 1, j, r);
}

bool pesqbin(const double v[], double r) {
    return pesqrec(v, 1, 10, r);
}
int main() {
    double v[10] = {1.0, 2.1, 3.3, 4.5, 5.5, 6.7, 7.9, 8.8, 9.9, 10.0};
    double r = 5.5;

    if (pesqbin(v, r))
        printf("Found!\n");
    else
        printf("Not found.\n");

    return 0;
}
