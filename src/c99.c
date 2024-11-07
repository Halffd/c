#include <stdio.h>
#include <complex.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#define PI calculatePi(0.000000000000001)
#endif
#include <stdio.h>
#include <math.h>

double calculatePi(double threshold) {
    double pi = 0.0;
    int sign = 1;
    int divisor = 1;
    double term;

    do {
        term = (double)sign / divisor;
        pi += term;
        sign *= -1;
        divisor += 2;
    } while (fabs(term) > threshold);

    return pi * 4;
}
// Function declaration
double complex* ditfft2(double complex* in, int N, int s, double complex* out);
typedef int (*compare_func)(const void*, const void*);
int compute(int w, int h, int x, int y, double zoom);

// Cooley-Tukey FFT algorithm implementation
double complex* ditfft2(double complex* in, int N, int s, double complex* out) {
    if (N == 1) {
        out[0] = in[0];
    } else {
        int k;

        ditfft2(in, N/2, 2*s, out);
        ditfft2(in + s, N/2, 2*s, out + N/2);

        for (k = 0; k < N/2; k++) {
            double complex t;
            double complex e;

            t = out[k];
            e = cexp(-2.0 * M_PI * I * k / N);

            out[k] = t + e * out[k + N/2];
            out[k + N/2] = t - e * out[k + N/2];
        }
    }

    return out;
}

int cxpfft() {
    // Input sequence
    double complex in[] = {1.0 + 0.0 * I, 0.0 + 1.0 * I, -1.0 + 0.0 * I, 0.0 - 1.0 * I};

    // Size of the input sequence
    int N = sizeof(in) / sizeof(in[0]);

    // Output array
    double complex out[N];

    // Compute the DFT using the Cooley-Tukey FFT algorithm
    ditfft2(in, N, 1, out);

    // Print the computed DFT
    printf("DFT: ");
    for (int i = 0; i < N; i++) {
        printf("%.2f + %.2fi ", creal(out[i]), cimag(out[i]));
    }
    printf("\n");

    return 0;
}
void hex(){
    double num1 = 123.456;
    double num2 = 0.000123456;
    
    printf("Using %%a:\n");
    printf("num1 in hex: %a\n", num1);
    printf("num2 in hex: %a\n", num2);
    
    printf("Using %%A:\n");
    printf("num1 in hex: %A\n", num1);
    printf("num2 in hex: %A\n", num2);
    
    // Define hexadecimal floating-point numbers
    float hexFloats[] = {
        0x3a.2bp1f,   // 0x3a.2b in base 2 raised to the power of 1
        0x3a.2bp2f,   // 0x3a.2b in base 2 raised to the power of 2
        0x3a.2bp3f,   // 0x3a.2b in base 2 raised to the power of 3
        0x3a.2bp4f,   // 0x3a.2b in base 2 raised to the power of 4
        0x3a.2bp0f,   // 0x3a.2b in base 2 raised to the power of 0
        0xdffa.18eaa12bp1f, // 0xdffa.18eaa12 in base 2 raised to the power of 1
        0x2fa.28a12bp25f, // 0xdffa.18eaa12 in base 2 raised to the power of 1
        0x2f2ffff2a.2bp-12f, // 0xdffa.18eaa12 in base 2 raised to the power of 1
        [8] = 0b01001000101000000100001,
        0.5f,
        1.35f,
        -1.4f,
        8.75f,
        16.001f,
        305.555f,
        -0xff,
        -0x11a.bp+1,
        [18 ... 25] = 0
    };

    // Number of elements in the array
    size_t count = sizeof(hexFloats) / sizeof(hexFloats[0]);

    // Print the hexadecimal floating-point values
    printf("Hexadecimal floating-point values:\n");
    for (size_t i = 0; i < count; i++) {
        printf("Value %zu %x %f: %a\n", i, (int) hexFloats[i], hexFloats[i], hexFloats[i]); // Print in hexadecimal float format
    }
}
void c99(){
    //cxpfft();
    //crimg();
    //cmplx();
    hex();
}
int cmplx() {
    int width = 8;
    int height = 3;
    double zoom = 1.5;

    // Iterate over each pixel in the image
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int iterations = compute(width, height, x, y, zoom);
            printf("(%d, %d) -> %d\n", x, y, iterations);
        }
    }

    return 0;
}

int compute(int w, int h, int x, int y, double zoom){
    const int max_iter = 100;

    const double c_x = zoom * (x * 1.0 / w - 0.5);
    const double c_y = zoom * (y * 1.0 / h - 0.5);
    const double complex c = c_y * 2.0 * I + c_x * 3.0 - 1.0;

    double complex z = 0.0 + 0.0 * I;

    int i = 0;

    for (; i < max_iter; ++i) {
        z = z * z + c;

        double magnitude_squared = creal(z) * creal(z) + cimag(z) * cimag(z);
        if (magnitude_squared > 4) {
            break;
        }
    }

    return i;
    }


int compare_complex(const void* a, const void* b) {
 double complex x = *(double complex*)a;
 double complex y = *(double complex*)b;
 if(creal(x) != creal(y)) return (creal(x) < creal(y)) ? -1 : 1;
 else return (cimag(x) < cimag(y)) ? -1 : 1;
}

void rotate(double complex* arr, unsigned int len, unsigned int k) {
 double complex* temp = (double complex*)malloc(k*sizeof(double complex));
 unsigned int i;
 for(i = 0; i < k; i++) temp[i] = arr[i];
 for(i = 0; i < len-k; i++) arr[i] = arr[i+k];
 for(i = 0; i < k; i++) arr[i+len-k] = temp[i];
 free(temp);
}

int crimg() {
 double complex arr[] = {1.0 + 2.0*I, 3.0 + 4.0*I, 2.0 + 3.0*I, 5.0 + 7.0*I, 6.0 + 8.0*I};
 unsigned int len = sizeof(arr)/sizeof(arr[0]);

 qsort(arr, len, sizeof(double complex), (compare_func)compare_complex);
 rotate(arr, len, 2);

 for(unsigned int i = 0; i < len; i++)
 printf("%lf + %lfi\n", creal(arr[i]), cimag(arr[i]));

 return 0;
}