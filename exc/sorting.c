#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h> // For sleep()
#include <pthread.h> // For sleep sort
#define TAMANHO 10
#define MAX_SLEEP_VAL 100 // Cap sleep values for sanity
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <math.h>  // For log() function
#include <limits.h> // For INT_MAX

// Function prototypes for intro sort
void intro_sort(int *v, int print_steps);
void intro_sort_util(int arr[], int low, int high, int depth_limit, int print_steps);
void insertion_sort_range(int arr[], int low, int high);
void heap_sort_range(int arr[], int low, int high);
void heapify_range(int arr[], int n, int i, int low);
int partition_for_quicksort(int arr[], int low, int high);

// Function prototypes for other sorts
void swap(int *a, int *b);
void stooge_sort(int *v, int print_steps);
void stooge_sort_util(int arr[], int low, int high, int print_steps, int depth, int *steps);
void bitonic_sort(int *v, int print_steps);
void bitonic_sort_util(int a[], int low, int count, int dir, int print_steps);
void compare_and_swap(int a[], int i, int j, int dir);
void bitonic_merge(int a[], int low, int count, int dir, int print_steps);
void smooth_sort(int *v, int print_steps);
void smooth_sift(int arr[], int root, int lp, int L[], int print_steps, int n);
void smooth_trinkle(int arr[], int root, int p, int pshift, int trusty, int L[], int print_steps, int n);
// This could be controlled at runtime, would require an extra pass though.
#define MEMSORT_SIZE 0xffff

uint16_t *memsort_buf[MEMSORT_SIZE];

#define N_NUMBERS 20000

static int numbers[N_NUMBERS];
static int sorted[N_NUMBERS];

// Sleep sort thread function
typedef struct {
    int val;
    int idx;
    int *result;
    int *counter;
    pthread_mutex_t *mutex;
} sleep_data;

void* sleep_sort_thread(void *arg) {
    sleep_data *data = (sleep_data*)arg;
    
    // Sleep proportional to value (scale down for demo purposes)
    usleep(data->val * 50000); // 50ms per unit of value
    
    // Critical section - update the result array
    pthread_mutex_lock(data->mutex);
    data->result[(*data->counter)++] = data->val;
    pthread_mutex_unlock(data->mutex);
    
    pthread_exit(NULL);
}
void memsort(int *in, size_t n, int *out)
{
 for (size_t i = 0; i < n; i++)
 {
 int num = in[i];
 assert(num < MEMSORT_SIZE);
 memsort_buf[num] += 1;
 }

 size_t pos = 0;

 for (size_t i = 0; i < MEMSORT_SIZE; i++)
 {
 while (memsort_buf[i]--)
 {
 out[pos++] = i;
 }
 }
}
void memsortTest()
{
 for (size_t i = 0; i < N_NUMBERS; i++)
 {
 numbers[i] = rand() % MEMSORT_SIZE;
 }

 clock_t t = clock();

 memsort(numbers, N_NUMBERS, sorted);

 t = clock() - t;

 for (size_t i = 0; i < N_NUMBERS; i++)
 {
 printf("%i\n", sorted[i]);
 }

 printf("\nThat took %f ms\n", t / (float) CLOCKS_PER_SEC * 1000.0);
}
// Heapify a subtree rooted at index i in array v of size n
void heapify(int *v, int n, int i, int print_steps) {
    int largest = i;      // Initialize largest as root
    int left = 2 * i + 1; // Left child
    int right = 2 * i + 2; // Right child
    int temp;
    
    // If left child is larger than root
    if (left < n) {
        if (print_steps) printf("Comparing v[%d]=%d with v[%d]=%d (left child)\n", largest, v[largest], left, v[left]);
        if (v[left] > v[largest])
            largest = left;
    }
    
    // If right child is larger than largest so far
    if (right < n) {
        if (print_steps) printf("Comparing v[%d]=%d with v[%d]=%d (right child)\n", largest, v[largest], right, v[right]);
        if (v[right] > v[largest])
            largest = right;
    }
    
    // If largest is not root
    if (largest != i) {
        if (print_steps) printf("Swapping v[%d]=%d and v[%d]=%d\n", i, v[i], largest, v[largest]);
        
        // Swap
        temp = v[i];
        v[i] = v[largest];
        v[largest] = temp;
        
        // Recursively heapify the affected sub-tree
        heapify(v, n, largest, print_steps);
    }
}

void heap_sort(int *v, int print_steps) {
    int n = TAMANHO;
    int i, temp;
    int swaps = 0;
    int comparisons = 0;
    
    printf("Initial array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n\n");
    
    if (print_steps) printf("Phase 1: Building max heap...\n");
    clock_t start = clock();
    
    // Build heap (rearrange array)
    for (i = n / 2 - 1; i >= 0; i--) {
        if (print_steps) printf("\nHeapifying subtree rooted at index %d:\n", i);
        heapify(v, n, i, print_steps);
        
        if (print_steps) {
            printf("Heap after heapify at index %d: ", i);
            for (int j = 0; j < n; j++) {
                printf("%d ", v[j]);
            }
            printf("\n");
        }
    }
    
    if (print_steps) {
        printf("\nMax heap built! Current array: ");
        for (int j = 0; j < n; j++) {
            printf("%d ", v[j]);
        }
        printf("\n\nPhase 2: Extracting elements from heap...\n");
    }
    
    // One by one extract an element from heap
    for (i = n - 1; i > 0; i--) {
        // Move current root to end
        if (print_steps) printf("\nMoving root (max element) v[0]=%d to position %d\n", v[0], i);
        temp = v[0];
        v[0] = v[i];
        v[i] = temp;
        swaps++;
        
        // Call max heapify on the reduced heap
        if (print_steps) printf("Heapifying reduced heap (size %d):\n", i);
        heapify(v, i, 0, print_steps);
        
        if (print_steps) {
            printf("Array after extraction %d: ", n - i);
            for (int j = 0; j < n; j++) {
                if (j == i) printf("| ");
                printf("%d ", v[j]);
            }
            printf("\n");
        }
    }
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n----- FINAL STATS (HEAP SORT) -----\n");
    printf("Sorted array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n");
    printf("Time complexity: O(n log n) - guaranteed\n");
    printf("Space complexity: O(1) - in-place sorting\n");
    printf("Time spent: %.6f seconds\n", time_spent);
    printf("----------------------\n\n");
}
void quicksort(int *v, int inicio, int fim, int print_steps) {
    int pivo, esq, dir, meio, aux;
    int comparisons = 0;
    int swaps = 0;
    
    // Base case - if partition has 1 or 0 elements
    if(inicio >= fim) return;
    
    // Choose pivot (middle element to avoid worst-case on sorted arrays)
    meio = (inicio + fim) / 2;
    pivo = v[meio];
    
    if(print_steps) {
        printf("Partitioning subarray: [");
        for(int i = inicio; i <= fim; i++) {
            printf("%d ", v[i]);
        }
        printf("]\n");
        printf("Pivot selected: v[%d]=%d\n", meio, pivo);
    }
    
    // Move pivot to beginning (traditional Lomuto scheme)
    v[meio] = v[inicio];
    v[inicio] = pivo;
    swaps++;
    
    // Partition process
    esq = inicio + 1;
    dir = fim;
    
    while(esq <= dir) {
        // Find element greater than pivot from left
        while(esq <= fim && v[esq] <= pivo) {
            comparisons++;
            if(print_steps) printf("Comparing v[%d]=%d with pivot %d: less or equal\n", esq, v[esq], pivo);
            esq++;
        }
        
        // Find element less than pivot from right
        while(dir > inicio && v[dir] > pivo) {
            comparisons++;
            if(print_steps) printf("Comparing v[%d]=%d with pivot %d: greater\n", dir, v[dir], pivo);
            dir--;
        }
        
        // Swap if pointers haven't crossed
        if(esq < dir) {
            if(print_steps) printf("Swapping v[%d]=%d and v[%d]=%d\n", esq, v[esq], dir, v[dir]);
            aux = v[esq];
            v[esq] = v[dir];
            v[dir] = aux;
            swaps++;
        }
    }
    
    // Put pivot in its final position
    if(print_steps) printf("Placing pivot %d at position %d\n", pivo, dir);
    v[inicio] = v[dir];
    v[dir] = pivo;
    swaps++;
    
    if(print_steps) {
        printf("After partition: [");
        for(int i = inicio; i <= fim; i++) {
            printf("%d ", v[i]);
            if(i == dir) printf("| ");
        }
        printf("]\n\n");
    }
    
    // Recursively sort subarrays
    quicksort(v, inicio, dir-1, print_steps);
    quicksort(v, dir+1, fim, print_steps);
}

void quick_sort(int *v, int print_steps) {
    int comparisons = 0;
    int swaps = 0;
    
    printf("Initial array: ");
    for(int j = 0; j < TAMANHO; j++) {
        printf("%d ", v[j]);
    }
    printf("\n\n");
    
    clock_t start = clock();
    
    // Call recursive quicksort
    quicksort(v, 0, TAMANHO-1, print_steps);
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n----- FINAL STATS (QUICK SORT) -----\n");
    printf("Sorted array: ");
    for(int j = 0; j < TAMANHO; j++) {
        printf("%d ", v[j]);
    }
    printf("\n");
    printf("Time complexity: Average O(n log n), Worst O(n²)\n");
    printf("Space complexity: O(log n) for recursion stack\n");
    printf("Time spent: %.6f seconds\n", time_spent);
    printf("----------------------\n\n");
}
void merge(int *v, int *c, int i, int m, int f, int print_steps) {
    int z, iv = i, ic = m + 1;
    
    if (print_steps) {
        printf("Merging subarrays: [");
        for (int k = i; k <= m; k++) printf("%d ", v[k]);
        printf("] and [");
        for (int k = m+1; k <= f; k++) printf("%d ", v[k]);
        printf("]\n");
    }
    
    // Copy to auxiliary array
    for (z = i; z <= f; z++)
        c[z] = v[z];
    
    z = i;
    
    // Merge process - the actual sorting happens here!
    while (iv <= m && ic <= f) {
        if (print_steps) printf("Comparing c[%d]=%d and c[%d]=%d\n", iv, c[iv], ic, c[ic]);
        
        if (c[iv] <= c[ic]) {
            v[z] = c[iv];
            iv++;
            if (print_steps) printf("Taking left element: %d\n", v[z]);
        } else {
            v[z] = c[ic];
            ic++;
            if (print_steps) printf("Taking right element: %d\n", v[z]);
        }
        z++;
    }
    
    // Copy remaining elements from left subarray
    while (iv <= m) {
        v[z] = c[iv];
        if (print_steps) printf("Copying remaining left element: %d\n", c[iv]);
        z++;
        iv++;
    }
    
    // Copy remaining elements from right subarray
    while (ic <= f) {
        v[z] = c[ic];
        if (print_steps) printf("Copying remaining right element: %d\n", c[ic]);
        z++;
        ic++;
    }
    
    if (print_steps) {
        printf("After merge: [");
        for (int k = i; k <= f; k++) printf("%d ", v[k]);
        printf("]\n\n");
    }
}

void sort(int *v, int *c, int i, int f, int print_steps) {
    if (i >= f) return;
    
    int m = (i + f) / 2;
    
    if (print_steps) {
        printf("Dividing array [");
        for (int k = i; k <= f; k++) printf("%d ", v[k]);
        printf("] at midpoint %d\n", m);
    }
    
    // Recursively sort left and right halves
    sort(v, c, i, m, print_steps);
    sort(v, c, m + 1, f, print_steps);
    
    // If already sorted, skip merge (optimization)
    if (v[m] <= v[m + 1]) {
        if (print_steps) printf("Subarrays already ordered, skipping merge\n\n");
        return;
    }
    
    // Merge the sorted halves
    merge(v, c, i, m, f, print_steps);
}

void mergesort(int *v, int print_steps) {
    int comparisons = 0; // For stats (though harder to track in merge sort)
    
    printf("Initial array: ");
    for (int j = 0; j < TAMANHO; j++) {
        printf("%d ", v[j]);
    }
    printf("\n\n");
    
    if (print_steps) printf("Beginning merge sort process...\n\n");
    
    // Allocate auxiliary array
    int *c = malloc(sizeof(int) * TAMANHO);
    if (c == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    clock_t start = clock();
    
    // Start the recursive sorting
    sort(v, c, 0, TAMANHO - 1, print_steps);
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    // Free auxiliary array
    free(c);
    
    printf("\n----- FINAL STATS (MERGE SORT) -----\n");
    printf("Sorted array: ");
    for (int j = 0; j < TAMANHO; j++) {
        printf("%d ", v[j]);
    }
    printf("\n");
    printf("Time complexity: O(n log n)\n");
    printf("Space complexity: O(n) - requires auxiliary array\n");
    printf("Time spent: %.6f seconds\n", time_spent);
    printf("----------------------\n\n");
}
void selecao(int *v, int print_steps) {
    int i, j, aux, minimo, pos_minimo;
    int comparisons = 0;
    int swaps = 0;
    
    printf("Initial array: ");
    for (int j = 0; j < TAMANHO; j++) {
        printf("%d ", v[j]);
    }
    printf("\n\n");
    
    clock_t start = clock();
    
    for (i = 0; i < TAMANHO-1; i++) {
        minimo = v[i];
        pos_minimo = i;
        
        if (print_steps) printf("Finding minimum element starting from position %d...\n", i);
        
        for (j = i+1; j < TAMANHO; j++) {
            comparisons++;
            if (print_steps) printf("Comparing v[%d]=%d and v[%d]=%d\n", pos_minimo, minimo, j, v[j]);
            
            if (minimo > v[j]) {
                minimo = v[j];
                pos_minimo = j;
                if (print_steps) printf("New minimum found: v[%d]=%d\n", pos_minimo, minimo);
            }
        }
        
        if (pos_minimo != i) {
            aux = v[pos_minimo];
            v[pos_minimo] = v[i];
            v[i] = aux;
            swaps++;
            
            if (print_steps) {
                printf("SWAP! Placing minimum at position %d. Array now: ", i);
                for (int k = 0; k < TAMANHO; k++) {
                    printf("%d ", v[k]);
                }
                printf("\n");
            }
        } else if (print_steps) {
            printf("Minimum already in correct position!\n");
        }
        
        if (print_steps) {
            printf("\n--- End of selection pass %d ---\n", i+1);
            printf("Current array: ");
            for (int k = 0; k < TAMANHO; k++) {
                printf("%d ", v[k]);
            }
            printf("\n\n");
        }
    }
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n----- FINAL STATS (SELECTION SORT) -----\n");
    printf("Sorted array: ");
    for (int j = 0; j < TAMANHO; j++) {
        printf("%d ", v[j]);
    }
    printf("\n");
    printf("Total passes: %d\n", TAMANHO - 1);
    printf("Total comparisons: %d\n", comparisons);
    printf("Total swaps: %d\n", swaps);
    printf("Time spent: %.6f seconds\n", time_spent);
    printf("----------------------\n\n");
}
void insertion(int *v, int print_steps) {
    int n = TAMANHO;
    clock_t start = clock();
    
    printf("Initial array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n\n");
    
    for (int i = 1; i < n; i++) {
        int key = v[i];
        int j = i - 1;
        
        // Move elements of v[0..i-1] that are greater than key
        // to one position ahead of their current position
        while (j >= 0 && v[j] > key) {
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[j + 1] = key;
        
        if (print_steps) {
            printf("After inserting %d: ", key);
            for (int k = 0; k < n; k++) {
                printf("%d ", v[k]);
            }
            printf("\n");
        }
    }
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n----- FINAL STATS (INSERTION SORT) -----\n");
    printf("Sorted array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n");
    printf("Time complexity: O(n²) worst case, O(n) best case\n");
    printf("Space complexity: O(1) - in-place sorting\n");
    printf("Time spent: %.6f seconds\n", time_spent);
    printf("----------------------\n\n");
}

void bolha(int *v, int print_steps) {
    int n = TAMANHO;
    clock_t start = clock();
    
    printf("Initial array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n\n");
    
    int swapped;
    int passes = 0;
    
    for (int i = 0; i < n - 1; i++) {
        swapped = 0;
        passes++;
        
        for (int j = 0; j < n - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                // Swap v[j] and v[j+1]
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
                swapped = 1;
            }
        }
        
        if (print_steps) {
            printf("After pass %d: ", passes);
            for (int k = 0; k < n; k++) {
                printf("%d ", v[k]);
            }
            printf("\n");
        }
        
        // If no swapping occurred in this pass, array is sorted
        if (swapped == 0) {
            break;
        }
    }
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n----- FINAL STATS (BUBBLE SORT) -----\n");
    printf("Sorted array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n");
    printf("Number of passes: %d\n", passes);
    printf("Time complexity: O(n²) worst case, O(n) best case\n");
    printf("Space complexity: O(1) - in-place sorting\n");
    printf("Time spent: %.6f seconds\n", time_spent);
    printf("----------------------\n\n");
}
// Helper function to check if array is sorted
int is_sorted(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i+1]) {
            return 0;
        }
    }
    return 1;
}

void bogosort(int *v, int print_steps) {
    int shuffles = 0;
    int max_shuffles = 100000; // Sanity limit
    int aux, j, k;
    
    printf("Initial array: ");
    for (int j = 0; j < TAMANHO; j++) {
        printf("%d ", v[j]);
    }
    printf("\n\n");
    
    printf("WARNING: Bogo Sort might take a very long time...\n");
    printf("Limited to %d shuffle attempts for sanity\n\n", max_shuffles);
    
    clock_t start = clock();
    
    // Keep shuffling until sorted or max attempts reached
    while (!is_sorted(v, TAMANHO) && shuffles < max_shuffles) {
        shuffles++;
        
        // Fisher-Yates shuffle
        for (j = TAMANHO - 1; j > 0; j--) {
            k = rand() % (j + 1);
            aux = v[j];
            v[j] = v[k];
            v[k] = aux;
        }
        
        if (print_steps && shuffles % 1000 == 0) {
            printf("Shuffle attempt #%d: ", shuffles);
            for (int j = 0; j < TAMANHO; j++) {
                printf("%d ", v[j]);
            }
            printf("\n");
        }
    }
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n----- FINAL STATS (BOGO SORT) -----\n");
    if (shuffles >= max_shuffles) {
        printf("GAVE UP after %d shuffle attempts!\n", max_shuffles);
    } else {
        printf("SUCCESS! Array sorted after %d shuffles.\n", shuffles);
    }
    
    printf("Sorted array: ");
    for (int j = 0; j < TAMANHO; j++) {
        printf("%d ", v[j]);
    }
    printf("\n");
    printf("Shuffle attempts: %d\n", shuffles);
    printf("Time spent: %.6f seconds\n", time_spent);
    printf("----------------------\n\n");
}

void stalin_sort(int *v, int print_steps) {
    int result[TAMANHO];
    int result_size = 0;
    int eliminated = 0;
    
    printf("Initial array: ");
    for (int j = 0; j < TAMANHO; j++) {
        printf("%d ", v[j]);
    }
    printf("\n\n");
    
    clock_t start = clock();
    
    // First element always stays
    result[result_size++] = v[0];
    if (print_steps) printf("Starting with first element %d\n", v[0]);
    
    // Check each subsequent element
    for (int i = 1; i < TAMANHO; i++) {
        if (print_steps) printf("Checking element v[%d]=%d\n", i, v[i]);
        
        if (v[i] >= result[result_size-1]) {
            result[result_size++] = v[i];
            if (print_steps) printf("Element %d keeps its party membership!\n", v[i]);
        } else {
            eliminated++;
            if (print_steps) printf("Element %d has been ELIMINATED! Not obeying order!\n", v[i]);
        }
        
        if (print_steps) {
            printf("Current array after purge: ");
            for (int j = 0; j < result_size; j++) {
                printf("%d ", result[j]);
            }
            printf("\n\n");
        }
    }
    
    // Copy result back to original array
    for (int i = 0; i < result_size; i++) {
        v[i] = result[i];
    }
    
    // Fill remaining spots with -1 to show they're eliminated
    for (int i = result_size; i < TAMANHO; i++) {
        v[i] = -1; // Mark as eliminated
    }
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n----- FINAL STATS (STALIN SORT) -----\n");
    printf("Final array (eliminated elements marked as -1): ");
    for (int j = 0; j < TAMANHO; j++) {
        printf("%d ", v[j]);
    }
    printf("\n");
    printf("Elements that survived: %d\n", result_size);
    printf("Elements eliminated: %d\n", eliminated);
    printf("Time spent: %.6f seconds\n", time_spent);
    printf("----------------------\n\n");
}

void sleep_sort(int *v, int print_steps) {
    pthread_t threads[TAMANHO];
    sleep_data thread_data[TAMANHO];
    int result[TAMANHO];
    int counter = 0;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    
    printf("Initial array: ");
    for (int j = 0; j < TAMANHO; j++) {
        printf("%d ", v[j]);
    }
    printf("\n\n");
    
    printf("Starting Sleep Sort (this will take some time)...\n");
    
    // Cap values for reasonable sleep times
    int capped_values[TAMANHO];
    for (int i = 0; i < TAMANHO; i++) {
        capped_values[i] = v[i] > MAX_SLEEP_VAL ? MAX_SLEEP_VAL : v[i];
        if (v[i] != capped_values[i] && print_steps) {
            printf("Capped value %d to %d for reasonable sleep time\n", v[i], capped_values[i]);
        }
    }
    
    clock_t start = clock();
    
    // Create threads
    for (int i = 0; i < TAMANHO; i++) {
        thread_data[i].val = capped_values[i];
        thread_data[i].idx = i;
        thread_data[i].result = result;
        thread_data[i].counter = &counter;
        thread_data[i].mutex = &mutex;
        
        if (print_steps) printf("Creating thread for value %d\n", capped_values[i]);
        
        pthread_create(&threads[i], NULL, sleep_sort_thread, (void*)&thread_data[i]);
    }
    
    // Wait for all threads to complete
    for (int i = 0; i < TAMANHO; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Copy result back to original array
    for (int i = 0; i < TAMANHO; i++) {
        v[i] = result[i];
    }
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n----- FINAL STATS (SLEEP SORT) -----\n");
    printf("Sorted array: ");
    for (int j = 0; j < TAMANHO; j++) {
        printf("%d ", v[j]);
    }
    printf("\n");
    printf("Time spent: %.6f seconds\n", time_spent);
    printf("Note: Sleep Sort is probabilistic and may not always sort correctly!\n");
    printf("----------------------\n\n");
}
// Function to get the maximum value in array v[]
int getMax(int *v, int n) {
    int max = v[0];
    for (int i = 1; i < n; i++)
        if (v[i] > max)
            max = v[i];
    return max;
}
// 1. Bucket Sort
void bucket_sort(int *v, int print_steps) {
    int n = TAMANHO;
    clock_t start = clock();
    
    printf("Initial array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n\n");
    
    // Find maximum and minimum values
    int max_val = v[0];
    int min_val = v[0];
    for (int i = 1; i < n; i++) {
        if (v[i] > max_val) max_val = v[i];
        if (v[i] < min_val) min_val = v[i];
    }
    
    // Create buckets
    int bucket_count = 10; // Can be adjusted based on input range
    int **buckets = (int**)malloc(sizeof(int*) * bucket_count);
    int *bucket_sizes = (int*)calloc(bucket_count, sizeof(int));
    
    for (int i = 0; i < bucket_count; i++) {
        buckets[i] = (int*)malloc(sizeof(int) * n); // Allocate max possible size
    }
    
    // Distribute elements into buckets
    for (int i = 0; i < n; i++) {
        int bucket_index = (bucket_count - 1) * (v[i] - min_val) / (max_val - min_val + 1);
        buckets[bucket_index][bucket_sizes[bucket_index]++] = v[i];
    }
    
    if (print_steps) {
        printf("Distributing elements into buckets:\n");
        for (int i = 0; i < bucket_count; i++) {
            printf("Bucket %d: ", i);
            for (int j = 0; j < bucket_sizes[i]; j++) {
                printf("%d ", buckets[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    
    // Sort individual buckets (using insertion sort)
    for (int i = 0; i < bucket_count; i++) {
        for (int j = 1; j < bucket_sizes[i]; j++) {
            int key = buckets[i][j];
            int k = j - 1;
            
            while (k >= 0 && buckets[i][k] > key) {
                buckets[i][k + 1] = buckets[i][k];
                k--;
            }
            buckets[i][k + 1] = key;
        }
    }
    
    if (print_steps) {
        printf("After sorting each bucket:\n");
        for (int i = 0; i < bucket_count; i++) {
            printf("Bucket %d: ", i);
            for (int j = 0; j < bucket_sizes[i]; j++) {
                printf("%d ", buckets[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    
    // Concatenate buckets back into the original array
    int index = 0;
    for (int i = 0; i < bucket_count; i++) {
        for (int j = 0; j < bucket_sizes[i]; j++) {
            v[index++] = buckets[i][j];
        }
        free(buckets[i]);
    }
    
    free(buckets);
    free(bucket_sizes);
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n----- FINAL STATS (BUCKET SORT) -----\n");
    printf("Sorted array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n");
    printf("Time complexity: O(n+k) average, O(n²) worst case\n");
    printf("Space complexity: O(n+k)\n");
    printf("Time spent: %.6f seconds\n", time_spent);
    printf("----------------------\n\n");
}

// 2. Tim Sort
#define MIN_MERGE 32

// This function sorts array from left index to right index using insertion sort
void insertionSort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

// Merge function merges the sorted runs
void merge_for_timsort(int arr[], int l, int m, int r) {
    // Original array is broken in two parts - left and right array
    int len1 = m - l + 1, len2 = r - m;
    int *left = (int*)malloc(len1 * sizeof(int));
    int *right = (int*)malloc(len2 * sizeof(int));
    
    for (int i = 0; i < len1; i++)
        left[i] = arr[l + i];
    for (int i = 0; i < len2; i++)
        right[i] = arr[m + 1 + i];
        
    int i = 0, j = 0, k = l;
    
    // After comparing, we merge those two array in larger sub array
    while (i < len1 && j < len2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    
    // Copy remaining elements
    while (i < len1) {
        arr[k] = left[i];
        k++;
        i++;
    }
    
    while (j < len2) {
        arr[k] = right[j];
        k++;
        j++;
    }
    
    free(left);
    free(right);
}

// Helper function for min
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Tim Sort implementation
void tim_sort(int *v, int print_steps) {
    int n = TAMANHO;
    clock_t start = clock();
    
    printf("Initial array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n\n");
    
    // Sort individual subarrays of size MIN_MERGE
    for (int i = 0; i < n; i += MIN_MERGE) {
        insertionSort(v, i, min(i + MIN_MERGE - 1, n - 1));
    }
    
    if (print_steps) {
        printf("After sorting subarrays of size %d: ", MIN_MERGE);
        for (int i = 0; i < n; i++) {
            printf("%d ", v[i]);
        }
        printf("\n\n");
    }
    
    // Start merging from size MIN_MERGE
    for (int size = MIN_MERGE; size < n; size = 2 * size) {
        // Pick starting point of left sub array. We merge arr[left..left+size-1] and arr[left+size, left+2*size-1]
        for (int left = 0; left < n; left += 2 * size) {
            // Find ending point of left sub array. mid+1 is starting point of right sub array
            int mid = min(left + size - 1, n-1);
            int right = min((left + 2 * size - 1), (n - 1));
            
            // Merge sub array arr[left.....mid] & arr[mid+1....right]
            if (mid < right) {
                merge_for_timsort(v, left, mid, right);
            }
        }
        
        if (print_steps) {
            printf("After merging subarrays of size %d: ", size);
            for (int i = 0; i < n; i++) {
                printf("%d ", v[i]);
            }
            printf("\n\n");
        }
    }
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n----- FINAL STATS (TIM SORT) -----\n");
    printf("Sorted array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n");
    printf("Time complexity: O(n log n)\n");
    printf("Space complexity: O(n)\n");
    printf("Time spent: %.6f seconds\n", time_spent);
    printf("----------------------\n\n");
}

// 3. Comb Sort
void comb_sort(int *v, int print_steps) {
    int n = TAMANHO;
    clock_t start = clock();
    
    printf("Initial array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n\n");
    
    // Initialize gap
    int gap = n;
    
    // Initialize swapped as true to enter the loop
    int swapped = 1;
    
    // Keep running while gap is more than 1 and there was a swap in the last iteration
    while (gap > 1 || swapped) {
        // Calculate gap using shrink factor of 1.3
        gap = (gap * 10) / 13;
        if (gap < 1) gap = 1;
        
        // Initialize swapped as false
        swapped = 0;
        
        // Compare all elements with the current gap
        for (int i = 0; i < n - gap; i++) {
            if (v[i] > v[i + gap]) {
                // Swap elements
                int temp = v[i];
                v[i] = v[i + gap];
                v[i + gap] = temp;
                
                // Set swapped to true
                swapped = 1;
            }
        }
        
        if (print_steps && swapped) {
            printf("Array after gap %d: ", gap);
            for (int j = 0; j < n; j++) {
                printf("%d ", v[j]);
            }
            printf("\n\n");
        }
    }
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n----- FINAL STATS (COMB SORT) -----\n");
    printf("Sorted array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n");
    printf("Time complexity: O(n² / 2^p) where p is number of increments\n");
    printf("Space complexity: O(1) - in-place sorting\n");
    printf("Time spent: %.6f seconds\n", time_spent);
    printf("----------------------\n\n");
}
// 4. Intro Sort
void intro_sort(int *v, int print_steps) {
    int n = TAMANHO;
    clock_t start = clock();
    
    printf("Initial array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n\n");
    
    // Call intro sort utility function
    intro_sort_util(v, 0, n-1, 2*log(n), print_steps);
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n----- FINAL STATS (INTRO SORT) -----\n");
    printf("Sorted array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n");
    printf("Time complexity: O(n log n)\n");
    printf("Space complexity: O(log n)\n");
    printf("Time spent: %.6f seconds\n", time_spent);
    printf("----------------------\n\n");
}

// Utility function for intro sort
void intro_sort_util(int arr[], int low, int high, int depth_limit, int print_steps) {
    // If partition size is low, use insertion sort
    if (high - low <= 16) {
        insertion_sort_range(arr, low, high);
        return;
    }
    
    // If recursion depth reaches limit, use heap sort
    if (depth_limit == 0) {
        if (print_steps) {
            printf("Recursion depth limit reached, switching to heap sort\n");
        }
        heap_sort_range(arr, low, high);
        return;
    }
    
    // Otherwise use quicksort approach
    int pivot = partition_for_quicksort(arr, low, high);
    
    if (print_steps) {
        printf("After quicksort partition (pivot=%d): ", arr[pivot]);
        for (int i = low; i <= high; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n\n");
    }
    
    // Recursively sort subarrays
    intro_sort_util(arr, low, pivot - 1, depth_limit - 1, print_steps);
    intro_sort_util(arr, pivot + 1, high, depth_limit - 1, print_steps);
}

// Helper for introsort - insertion sort on a range
void insertion_sort_range(int arr[], int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Helper for introsort - heap sort on a range
void heap_sort_range(int arr[], int low, int high) {
    int n = high - low + 1;
    
    // Build heap (rearrange array)
    for (int i = n / 2 - 1 + low; i >= low; i--)
        heapify_range(arr, n, i, low);
    
    // One by one extract from heap
    for (int i = high; i > low; i--) {
        // Move current root to end
        int temp = arr[low];
        arr[low] = arr[i];
        arr[i] = temp;
        
        // Call heapify on reduced heap
        heapify_range(arr, i - low, low, low);
    }
}

// Heapify a subtree rooted with node i
void heapify_range(int arr[], int n, int i, int low) {
    int largest = i;      // Initialize largest as root
    int l = 2 * (i - low) + 1 + low;  // left = 2*i + 1
    int r = 2 * (i - low) + 2 + low;  // right = 2*i + 2
    
    // If left child is larger than root
    if (l < n + low && arr[l] > arr[largest])
        largest = l;
    
    // If right child is larger than largest so far
    if (r < n + low && arr[r] > arr[largest])
        largest = r;
    
    // If largest is not root
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        
        // Recursively heapify the affected sub-tree
        heapify_range(arr, n, largest, low);
    }
}

// Helper for introsort - partition function for quicksort
int partition_for_quicksort(int arr[], int low, int high) {
    // Select pivot (median of three)
    int mid = low + (high - low) / 2;
    if (arr[mid] < arr[low])
        swap(&arr[mid], &arr[low]);
    if (arr[high] < arr[low])
        swap(&arr[high], &arr[low]);
    if (arr[mid] < arr[high])
        swap(&arr[mid], &arr[high]);
        
    int pivot = arr[high];  // pivot
    int i = (low - 1);      // Index of smaller element
    
    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// 5. Gnome Sort
void gnome_sort(int *v, int print_steps) {
    int n = TAMANHO;
    clock_t start = clock();
    
    printf("Initial array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n\n");
    
    int index = 0;
    int step = 0;
    
    while (index < n) {
        if (index == 0)
            index++;
        if (v[index] >= v[index - 1])
            index++;
        else {
            // Swap and move back
            swap(&v[index], &v[index - 1]);
            index--;
            
            if (print_steps) {
                step++;
                printf("Step %d: ", step);
                for (int j = 0; j < n; j++) {
                    printf("%d ", v[j]);
                }
                printf("\n");
            }
        }
    }
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n----- FINAL STATS (GNOME SORT) -----\n");
    printf("Sorted array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n");
    printf("Time complexity: O(n²)\n");
    printf("Space complexity: O(1) - in-place sorting\n");
    printf("Time spent: %.6f seconds\n", time_spent);
    printf("----------------------\n\n");
}

// Helper function for swapping
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Bonus: Cocktail Shaker Sort
void cocktail_sort(int *v, int print_steps) {
    int n = TAMANHO;
    clock_t start = clock();
    
    printf("Initial array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n\n");
    
    int swapped = 1;
    int start_idx = 0;
    int end_idx = n - 1;
    int step = 0;
    
    while (swapped) {
        // Reset swapped flag for forward pass
        swapped = 0;
        
        // Forward pass (like a bubble sort)
        for (int i = start_idx; i < end_idx; i++) {
            if (v[i] > v[i + 1]) {
                swap(&v[i], &v[i + 1]);
                swapped = 1;
            }
        }
        
        if (!swapped)
            break;
            
        if (print_steps) {
            step++;
            printf("Step %d (forward): ", step);
            for (int j = 0; j < n; j++) {
                printf("%d ", v[j]);
            }
            printf("\n");
        }
        
        // Decrease end index as largest element is now at the end
        end_idx--;
        
        // Reset swapped flag for backward pass
        swapped = 0;
        
        // Backward pass (bubble largest to beginning)
        for (int i = end_idx; i > start_idx; i--) {
            if (v[i] < v[i - 1]) {
                swap(&v[i], &v[i - 1]);
                swapped = 1;
            }
        }
        
        if (print_steps) {
            step++;
            printf("Step %d (backward): ", step);
            for (int j = 0; j < n; j++) {
                printf("%d ", v[j]);
            }
            printf("\n");
        }
        
        // Increase start index as smallest element is now at the beginning
        start_idx++;
    }
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n----- FINAL STATS (COCKTAIL SORT) -----\n");
    printf("Sorted array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n");
    printf("Time complexity: O(n²)\n");
    printf("Space complexity: O(1) - in-place sorting\n");
    printf("Time spent: %.6f seconds\n", time_spent);
    printf("----------------------\n\n");
}

// Bonus: Pancake Sort
void flip(int *arr, int i) {
    int start = 0;
    while (start < i) {
        swap(&arr[start], &arr[i]);
        start++;
        i--;
    }
}

int find_max(int *arr, int n) {
    int max_idx = 0;
    for (int i = 1; i < n; i++)
        if (arr[i] > arr[max_idx])
            max_idx = i;
    return max_idx;
}

void pancake_sort(int *v, int print_steps) {
    int n = TAMANHO;
    clock_t start = clock();
    
    printf("Initial array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n\n");
    
    int step = 0;
    
    // Reduce the problem size one by one
    for (int curr_size = n; curr_size > 1; curr_size--) {
        // Find index of the maximum element in arr[0..curr_size-1]
        int max_idx = find_max(v, curr_size);
        
        // Move the maximum element to end of current array
        if (max_idx != curr_size - 1) {
            // First flip to bring max element to front
            flip(v, max_idx);
            
            if (print_steps) {
                step++;
                printf("Step %d (bring %d to front): ", step, v[0]);
                for (int j = 0; j < n; j++) {
                    printf("%d ", v[j]);
                }
                printf("\n");
            }
            
            // Second flip to bring max element to its correct position
            flip(v, curr_size - 1);
            
            if (print_steps) {
                step++;
                printf("Step %d (move %d to position %d): ", step, v[curr_size-1], curr_size-1);
                for (int j = 0; j < n; j++) {
                    printf("%d ", v[j]);
                }
                printf("\n");
            }
        }
    }
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n----- FINAL STATS (PANCAKE SORT) -----\n");
    printf("Sorted array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n");
    printf("Time complexity: O(n²)\n");
    printf("Space complexity: O(1) - in-place sorting\n");
    printf("Time spent: %.6f seconds\n", time_spent);
    printf("----------------------\n\n");
}
// A function to do counting sort of v[] according to
// the digit represented by exp.
void countSort(int *v, int n, int exp, int print_steps) {
    int output[n]; // output array
    int i, count[10] = {0};
    
    // Store count of occurrences in count[]
    for (i = 0; i < n; i++) {
        count[(v[i] / exp) % 10]++;
        if (print_steps) printf("Element %d has digit %d at position %d\n", 
                               v[i], (v[i] / exp) % 10, exp);
    }
    
    if (print_steps) {
        printf("Count array: ");
        for (i = 0; i < 10; i++)
            printf("%d ", count[i]);
        printf("\n");
    }
    
    // Change count[i] so that count[i] now contains actual
    // position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
    
    if (print_steps) {
        printf("Cumulative count: ");
        for (i = 0; i < 10; i++)
            printf("%d ", count[i]);
        printf("\n");
    }
    
    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        int digit = (v[i] / exp) % 10;
        int pos = count[digit] - 1;
        
        output[pos] = v[i];
        count[digit]--;
        
        if (print_steps) printf("Placing %d at position %d based on digit %d\n", 
                               v[i], pos, digit);
    }
    
    // Copy the output array to v[], so that v[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        v[i] = output[i];
    
    if (print_steps) {
        printf("Array after sorting by digit at position %d: ", exp);
        for (i = 0; i < n; i++)
            printf("%d ", v[i]);
        printf("\n\n");
    }
}

// The main function to that sorts v[] of size n using
// Shell Sort implementation
void shell_sort(int *v, int print_steps) {
    int n = TAMANHO;
    clock_t start = clock();
    
    printf("Initial array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n\n");
    
    // Sequence of gaps: 9, 5, 3, 2, 1 (common sequence for Shell Sort)
    int gaps[5] = {9, 5, 3, 2, 1};
    
    for (int k = 0; k < 5; k++) {
        int gap = gaps[k];
        
        if (print_steps)
            printf("Using gap = %d\n", gap);
        
        // Do insertion sort for each gap size
        for (int i = gap; i < n; i++) {
            int temp = v[i];
            int j;
            
            // Shift elements that are 'gap' distance apart
            for (j = i; j >= gap && v[j - gap] > temp; j -= gap) {
                v[j] = v[j - gap];
            }
            
            v[j] = temp;
        }
        
        if (print_steps) {
            printf("Array after gap %d: ", gap);
            for (int j = 0; j < n; j++) {
                printf("%d ", v[j]);
            }
            printf("\n\n");
        }
    }
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n----- FINAL STATS (SHELL SORT) -----\n");
    printf("Sorted array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n");
    printf("Time complexity: O(n log² n) to O(n²) depending on gap sequence\n");
    printf("Space complexity: O(1) - in-place sorting\n");
    printf("Time spent: %.6f seconds\n", time_spent);
    printf("----------------------\n\n");
}
// Radix Sort
void radix_sort(int *v, int print_steps) {
    int n = TAMANHO;
	clock_t start = clock(); // Add declaration here
    printf("Initial array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n\n");
    
    // Handle negative numbers check
    int hasNegative = 0;
    for (int i = 0; i < n; i++) {
        if (v[i] < 0) {
            hasNegative = 1;
            break;
        }
    }
    
    if (hasNegative) {
        printf("WARNING: Basic Radix Sort works best with non-negative numbers.\n");
        printf("This implementation will convert negatives to positives for sorting,\n");
        printf("then restore the signs at the end.\n\n");
        
        // Convert negatives to positives for sorting
        int *negFlags = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            negFlags[i] = (v[i] < 0) ? 1 : 0;
            v[i] = abs(v[i]);
        }
        
        // Find the maximum number to know number of digits
        int max = getMax(v, n);
        
        clock_t start = clock();
        
        if (print_steps) printf("Maximum value is %d\n\n", max);
        
        // Do counting sort for every digit
        for (int exp = 1; max / exp > 0; exp *= 10) {
            if (print_steps) printf("Sorting by digit at position %d:\n", exp);
            countSort(v, n, exp, print_steps);
        }
        
        // Restore signs
        for (int i = 0; i < n; i++) {
            if (negFlags[i]) {
                v[i] = -v[i];
            }
        }
        
        // Sort again with negatives in front
        int negCount = 0;
        for (int i = 0; i < n; i++) {
            if (v[i] < 0) negCount++;
        }
        
        int pos = 0, neg = 0;
        int *temp = (int*)malloc(n * sizeof(int));
        
        // Put negatives first (in descending order)
        for (int i = n-1; i >= 0; i--) {
            if (v[i] < 0) {
                temp[neg++] = v[i];
            }
        }
        
        // Then positives (in ascending order)
        for (int i = 0; i < n; i++) {
            if (v[i] >= 0) {
                temp[negCount + pos++] = v[i];
            }
        }
        
        // Copy back to original array
        for (int i = 0; i < n; i++) {
            v[i] = temp[i];
        }
        
        free(temp);
        free(negFlags);
    } else {
        // Find the maximum number to know number of digits
        int max = getMax(v, n);
        
        clock_t start = clock();
        
        if (print_steps) printf("Maximum value is %d\n\n", max);
        
        // Do counting sort for every digit
        for (int exp = 1; max / exp > 0; exp *= 10) {
            if (print_steps) printf("Sorting by digit at position %d:\n", exp);
            countSort(v, n, exp, print_steps);
        }
    }
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n----- FINAL STATS (RADIX SORT) -----\n");
    printf("Sorted array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n");
    printf("Time complexity: O(d * n) where d is number of digits\n");
    printf("Space complexity: O(n + k) where k is range of input\n");
    printf("Time spent: %.6f seconds\n", time_spent);
    printf("----------------------\n\n");
}
// Stooge Sort - A truly ridiculous recursive sorting algorithm
void stooge_sort_recursive(int arr[], int low, int high) {
    // If first element is smaller than last, swap them
    if (arr[low] > arr[high]) {
        swap(&arr[low], &arr[high]);
    }
    
    // If there are more than 2 elements
    if (high - low + 1 > 2) {
        int t = (high - low + 1) / 3;
        
        // Recursively sort first 2/3 elements
        stooge_sort_recursive(arr, low, high - t);
        
        // Recursively sort last 2/3 elements
        stooge_sort_recursive(arr, low + t, high);
        
        // Recursively sort first 2/3 elements again
        stooge_sort_recursive(arr, low, high - t);
    }
}

void stooge_sort(int *v, int print_steps) {
    int n = TAMANHO;
    clock_t start = clock();
    
    printf("Initial array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n\n");
    
    int steps = 0;
    if (print_steps) {
        printf("Warning: Stooge Sort generates A LOT of steps. Showing only major recursion levels.\n\n");
    }
    
    stooge_sort_util(v, 0, n - 1, print_steps, 0, &steps);
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n----- FINAL STATS (STOOGE SORT) -----\n");
    printf("Sorted array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n");
    printf("Time complexity: O(n^(log 3 / log 1.5)) ≈ O(n^2.7095)\n");
    printf("Space complexity: O(log n) - due to recursion\n");
    printf("Time spent: %.6f seconds\n", time_spent);
    printf("----------------------\n\n");
}

void stooge_sort_util(int arr[], int low, int high, int print_steps, int depth, int *steps) {
    // Print only first few recursion levels to avoid flooding output
    if (print_steps && depth < 3) {
        (*steps)++;
        printf("Step %d (recursion depth %d): ", *steps, depth);
        for (int j = low; j <= high; j++) {
            printf("%d ", arr[j]);
        }
        printf("\n");
    }
    
    // If first element is smaller than last, swap them
    if (arr[low] > arr[high]) {
        swap(&arr[low], &arr[high]);
        
        if (print_steps && depth < 3) {
            (*steps)++;
            printf("Step %d (swap %d and %d): ", *steps, arr[high], arr[low]);
            for (int j = low; j <= high; j++) {
                printf("%d ", arr[j]);
            }
            printf("\n");
        }
    }
    
    // If there are more than 2 elements
    if (high - low + 1 > 2) {
        int t = (high - low + 1) / 3;
        
        // Recursively sort first 2/3 elements
        stooge_sort_util(arr, low, high - t, print_steps, depth + 1, steps);
        
        // Recursively sort last 2/3 elements
        stooge_sort_util(arr, low + t, high, print_steps, depth + 1, steps);
        
        // Recursively sort first 2/3 elements again
        stooge_sort_util(arr, low, high - t, print_steps, depth + 1, steps);
    }
}

// Bitonic Sort - A parallel sorting algorithm that needs array size to be power of 2
void bitonic_sort(int *v, int print_steps) {
    int n = TAMANHO;
    clock_t start = clock();
    
    printf("Initial array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n\n");
    
    // Check if array size is power of 2
    int size = n;
    int power_of_two = 1;
    while (size > 1) {
        if (size % 2 != 0) {
            power_of_two = 0;
            break;
        }
        size /= 2;
    }
    
    if (!power_of_two) {
        printf("Warning: Bitonic sort requires array size to be a power of 2.\n");
        printf("Current size is %d. Padding with INT_MAX values.\n\n", n);
        
        // Find next power of 2
        int next_power = 1;
        while (next_power < n) {
            next_power *= 2;
        }
        
        // Create new array with padding
        int *padded = (int*)malloc(next_power * sizeof(int));
        for (int i = 0; i < n; i++) {
            padded[i] = v[i];
        }
        for (int i = n; i < next_power; i++) {
            padded[i] = INT_MAX;
        }
        
        // Sort the padded array
        bitonic_sort_util(padded, 0, next_power, 1, print_steps);
        
        // Copy back only the original elements
        for (int i = 0; i < n; i++) {
            v[i] = padded[i];
        }
        
        free(padded);
    } else {
        bitonic_sort_util(v, 0, n, 1, print_steps);
    }
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n----- FINAL STATS (BITONIC SORT) -----\n");
    printf("Sorted array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n");
    printf("Time complexity: O(n log² n)\n");
    printf("Space complexity: O(1) - in-place sorting\n");
    printf("Time spent: %.6f seconds\n", time_spent);
    printf("----------------------\n\n");
}

// Compares and swaps if direction is specified
void compare_and_swap(int a[], int i, int j, int dir) {
    if (dir == (a[i] > a[j])) {
        swap(&a[i], &a[j]);
    }
}

// Recursively sorts a bitonic sequence in the specified direction
void bitonic_merge(int a[], int low, int count, int dir, int print_steps) {
    if (count > 1) {
        int k = count / 2;
        
        // Compare and swap pairs with a particular gap
        for (int i = low; i < low + k; i++) {
            compare_and_swap(a, i, i + k, dir);
        }
        
        // Recursively sort the two halves
        bitonic_merge(a, low, k, dir, print_steps);
        bitonic_merge(a, low + k, k, dir, print_steps);
    }
}

// Generates a bitonic sequence by recursively sorting
void bitonic_sort_util(int a[], int low, int count, int dir, int print_steps) {
    if (count > 1) {
        int k = count / 2;
        
        // Sort first half in ascending order
        bitonic_sort_util(a, low, k, 1, print_steps);
        
        // Sort second half in descending order
        bitonic_sort_util(a, low + k, k, 0, print_steps);
        
        // Merge the entire sequence in the specified direction
        bitonic_merge(a, low, count, dir, print_steps);
        
        if (print_steps) {
            printf("After bitonic merge (size %d): ", count);
            for (int i = low; i < low + count; i++) {
                printf("%d ", a[i]);
            }
            printf("\n");
        }
    }
}

// Smooth Sort - a variant of heap sort using Leonardo numbers
#define MAX_LP 46 // Max Leonardo position needed for 32-bit int

// Leonardo numbers calculation
int leonardo(int k) {
    if (k < 2)
        return 1;
    return leonardo(k - 1) + leonardo(k - 2) + 1;
}

void smooth_sort(int *v, int print_steps) {
    int n = TAMANHO;
    clock_t start = clock();
    
    printf("Initial array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n\n");
    
    // Precompute Leonardo numbers
    int L[MAX_LP];
    L[0] = L[1] = 1;
    for (int i = 2; i < MAX_LP; i++) {
        L[i] = L[i-1] + L[i-2] + 1;
    }
    
    // Compute the smoothsort
    int p = 1; // First position of the root
    int pshift = 1; // How many bits to shift for next position
    int head = 0; // Head of the current sequence of trees
    
    // Build the Leonardo heaps
    for (int i = 1; i < n; i++) {
        if ((p & 3) == 3) { // p % 4 == 3
            // First see if we need to do any restoring work
            smooth_sift(v, i-p, p, L, print_steps, n);
            
            // Compute next p and pshift
            int trail = __builtin_ctz(p); // Count trailing zeros
            p >>= trail;
            pshift += trail;
            
            // Reset head
            head = 0;
        } else {
            // Perform a normal heap push
            if (head) {
                smooth_sift(v, i-p, p, L, print_steps, n);
            }
            
            // Update p and pshift for next position
            pshift--;
            p = (p << 1) + 1;
            head = 1;
        }
    }
    
    // Sort by repeatedly removing the max element
    for (int i = n-1; i > 0; i--) {
        // Get the root value
        int trail = __builtin_ctz(p);
        p >>= trail;
        pshift += trail;
        int root = i - p;
        
        // Restore heap property after removing max
        smooth_trinkle(v, root, p, pshift, 0, L, print_steps, n);
        
        if (print_steps && i % (n/10) == 0) {
            printf("After removing element at position %d: ", i);
            for (int j = 0; j < n; j++) {
                printf("%d ", v[j]);
            }
            printf("\n");
        }
    }
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n----- FINAL STATS (SMOOTH SORT) -----\n");
    printf("Sorted array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n");
    printf("Time complexity: O(n log n) worst case, O(n) best case\n");
    printf("Space complexity: O(1) - in-place sorting\n");
    printf("Time spent: %.6f seconds\n", time_spent);
    printf("----------------------\n\n");
}

// Sift function for smooth sort
void smooth_sift(int arr[], int root, int lp, int L[], int print_steps, int n) {
    while (lp >= 3) {
        int r1 = root - 1;
        int r2 = root - 1 - L[lp-2];
        
        if (arr[r1] > arr[root] && arr[r2] > arr[root]) {
            break;
        }
        
        if (arr[r1] >= arr[r2]) {
            swap(&arr[root], &arr[r1]);
            root = r1;
            lp--;
        } else {
            swap(&arr[root], &arr[r2]);
            root = r2;
            lp -= 2;
        }
    }
}

// Trinkle function for smooth sort
void smooth_trinkle(int arr[], int root, int p, int pshift, int trusty, int L[], int print_steps, int n) {
    while (p) {
        int stepson = root - L[pshift];
        if (arr[stepson] <= arr[root]) {
            break;
        }
        swap(&arr[root], &arr[stepson]);
        root = stepson;
        p >>= 1;
    }
}
// Library Sort (aka "gapped" insertion sort) - simplified version
void library_sort(int *v, int print_steps) {
    int n = TAMANHO;
    clock_t start = clock();
    
    printf("Initial array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n\n");
    
    // Create an array with gaps
    int size = n * 2; // Size with gaps
    int *lib = (int*)malloc(size * sizeof(int));
    
    // Initialize with markers for empty slots
    for (int i = 0; i < size; i++) {
        lib[i] = INT_MAX;
    }
    
    // Insert first element
    lib[0] = v[0];
    
    if (print_steps) {
        printf("Initial library array with one element:\n");
        printf("[%d", lib[0]);
        for (int i = 1; i < size; i++) {
            if (lib[i] == INT_MAX) {
                printf(", _");
            } else {
                printf(", %d", lib[i]);
            }
        }
        printf("]\n\n");
    }
    
    // Insert remaining elements
    for (int i = 1; i < n; i++) {
        // Find position for insertion using binary search
        int pos = 0;
        while (pos < size && lib[pos] != INT_MAX && lib[pos] < v[i]) {
            pos++;
        }
        
        // If we need to rebalance
        if (lib[pos] != INT_MAX) {
            // Shift elements to make room
            for (int j = size - 1; j > pos; j--) {
                lib[j] = lib[j-1];
            }
        }
        
        // Insert the element
        lib[pos] = v[i];
        
        if (print_steps && i % (n/5) == 0) {
            printf("After inserting element %d:\n", v[i]);
            printf("[");
            for (int j = 0; j < size; j++) {
                if (lib[j] == INT_MAX) {
                    printf("%s_", j == 0 ? "" : ", ");
                } else {
                    printf("%s%d", j == 0 ? "" : ", ", lib[j]);
                }
            }
            printf("]\n\n");
        }
        
        // Periodically rebalance to ensure gaps
        if (i % (n/4) == 0) {
            // Collect non-empty elements
            int count = 0;
            for (int j = 0; j < size; j++) {
                if (lib[j] != INT_MAX) {
                    v[count++] = lib[j];
                }
            }
            
            // Reset library with gaps
            for (int j = 0; j < size; j++) {
                lib[j] = INT_MAX;
            }
            
            // Redistribute with gaps
            for (int j = 0; j < count; j++) {
                lib[j*2] = v[j];
            }
        }
    }
    
    // Compact the result back into the original array
    int j = 0;
    for (int i = 0; i < size && j < n; i++) {
        if (lib[i] != INT_MAX) {
            v[j++] = lib[i];
        }
    }
    
    free(lib);
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n----- FINAL STATS (LIBRARY SORT) -----\n");
    printf("Sorted array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n");
    printf("Time complexity: O(n log n) expected\n");
    printf("Space complexity: O(n)\n");
    printf("Time spent: %.6f seconds\n", time_spent);
    printf("----------------------\n\n");
}
// Bead Sort (aka Gravity Sort) - works only for positive integers
void bead_sort(int *v, int print_steps) {
    int n = TAMANHO;
    clock_t start = clock();
    
    printf("Initial array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n\n");
    
    // Check if all numbers are positive
    for (int i = 0; i < n; i++) {
        if (v[i] < 0) {
            printf("Error: Bead Sort only works with positive integers.\n");
            return;
        }
    }
    
    // Find maximum element
    int max = v[0];
    for (int i = 1; i < n; i++) {
        if (v[i] > max) {
            max = v[i];
        }
    }
    
    // Allocate memory for beads
    unsigned char **beads = (unsigned char**)malloc(n * sizeof(unsigned char*));
    for (int i = 0; i < n; i++) {
        beads[i] = (unsigned char*)calloc(max, sizeof(unsigned char));
        // Set the beads for this row
        for (int j = 0; j < v[i]; j++) {
            beads[i][j] = 1;
        }
    }
    
    if (print_steps) {
        printf("Initial bead configuration:\n");
        for (int i = 0; i < n; i++) {
            printf("Row %d: ", i);
            for (int j = 0; j < max; j++) {
                printf("%d ", beads[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    
    // Let the beads fall (simulate gravity)
    for (int j = 0; j < max; j++) {
        // Count beads in this column
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += beads[i][j];
            beads[i][j] = 0; // Clear the bead
        }
        
        // Place beads at the bottom
        for (int i = n - sum; i < n; i++) {
            beads[i][j] = 1;
        }
    }
    
    if (print_steps) {
        printf("Final bead configuration after gravity:\n");
        for (int i = 0; i < n; i++) {
            printf("Row %d: ", i);
            for (int j = 0; j < max; j++) {
                printf("%d ", beads[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    
    // Count beads in each row to get sorted array
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < max; j++) {
            count += beads[i][j];
        }
        v[i] = count;
    }
    
    // Free memory
    for (int i = 0; i < n; i++) {
        free(beads[i]);
    }
    free(beads);
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n----- FINAL STATS (BEAD SORT) -----\n");
    printf("Sorted array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n");
    printf("Time complexity: O(n + max) where max is the largest number\n");
    printf("Space complexity: O(n*max)\n");
    printf("Time spent: %.6f seconds\n", time_spent);
    printf("----------------------\n\n");
}

// Odd-Even Sort (aka Brick Sort) - a parallel version of bubble sort
void odd_even_sort(int *v, int print_steps) {
    int n = TAMANHO;
    clock_t start = clock();
    
    printf("Initial array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n\n");
    
    int sorted = 0;
    int phase = 0;
    
    while (!sorted) {
        sorted = 1;
        
        // Odd phase (compare odd-indexed elements with next even-indexed)
        for (int i = 1; i < n - 1; i += 2) {
            if (v[i] > v[i + 1]) {
                swap(&v[i], &v[i + 1]);
                sorted = 0;
            }
        }
        
        if (print_steps) {
            phase++;
            printf("After odd phase %d: ", phase);
            for (int j = 0; j < n; j++) {
                printf("%d ", v[j]);
            }
            printf("\n");
        }
        
        // Even phase (compare even-indexed elements with next odd-indexed)
        for (int i = 0; i < n - 1; i += 2) {
            if (v[i] > v[i + 1]) {
                swap(&v[i], &v[i + 1]);
                sorted = 0;
            }
        }
        
        if (print_steps) {
            printf("After even phase %d: ", phase);
            for (int j = 0; j < n; j++) {
                printf("%d ", v[j]);
            }
            printf("\n\n");
        }
    }
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n----- FINAL STATS (ODD-EVEN SORT) -----\n");
    printf("Sorted array: ");
    for (int j = 0; j < n; j++) {
        printf("%d ", v[j]);
    }
    printf("\n");
    printf("Time complexity: O(n²)\n");
    printf("Space complexity: O(1) - in-place sorting\n");
    printf("Time spent: %.6f seconds\n", time_spent);
    printf("----------------------\n\n");
}
int main() {
    int sorted[TAMANHO] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int unsorted[TAMANHO] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int half_sorted[TAMANHO] = {1, 2, 3, 4, 5, 10, 9, 8, 7, 6};
    
    int test_case[TAMANHO];
    int choice;
    
    srand(time(NULL)); // Initialize random seed
    
    printf("\n====== SORTING ALGORITHM COMPARISON ======\n");
    printf("1. Bubble Sort (O(n²))\n");
    printf("2. Insertion Sort (O(n²))\n");
    printf("3. Selection Sort (O(n²))\n");
    printf("4. Bogo Sort (O(n×n!) with high probability)\n");
    printf("5. Stalin Sort (O(n) - not actually sorting!)\n");
    printf("6. Sleep Sort (O(max value in array))\n");
    printf("7. Run ALL tests (grab some coffee!)\n");
    printf("8. Merge Sort (O(n log n))\n");
    printf("9. Counting Sort (O(n k))\n");
    printf("10. Quick Sort (O(n log n) average)\n");
    printf("11. Heap Sort (O(n log n) guaranteed)\n");
	printf("12. Radix Sort (O(d * n) where d is number of digits)\n");
    printf("13. Shell Sort (O(n log² n) to O(n²))\n");
printf("13. Shell Sort (O(n log² n) to O(n²))\n");
printf("14. Bucket Sort (O(n+k) average, O(n²) worst case)\n");
printf("15. Tim Sort (O(n log n))\n");  
printf("16. Comb Sort (O(n² / 2^p))\n");
printf("17. Intro Sort (O(n log n))\n");
printf("18. Gnome Sort (O(n²))\n");
printf("19. Cocktail Shaker Sort (O(n²))\n");
printf("20. Pancake Sort (O(n²))\n");
printf("21. Stooge Sort (O(n^2.7095))\n");
printf("22. Bitonic Sort (O(n log² n))\n");
printf("23. Smooth Sort (O(n log n))\n");
printf("24. Library Sort (O(n log n))\n");
printf("25. Bead Sort (O(n + max))\n");
printf("26. Odd-Even Sort (O(n²))\n");

    printf("Enter your choice (1-7): ");
    scanf("%d", &choice);
    
    // Generate a random array for testing
    printf("Generating random test array...\n");
    for (int i = 0; i < TAMANHO; i++) {
        test_case[i] = rand() % 100;
    }
    
    int print_steps = 1;
    printf("Show detailed steps? (1=yes, 0=no): ");
    scanf("%d", &print_steps);
    
    switch (choice) {
        case 1:
            bolha(test_case, print_steps);
            break;
            
        case 2:
            insertion(test_case, print_steps);
            break;
            
        case 3:
            selecao(test_case, print_steps);
            break;
            
        case 4:
            bogosort(test_case, print_steps);
            break;
            
        case 5:
            stalin_sort(test_case, print_steps);
            break;
            
        case 6:
            sleep_sort(test_case, print_steps);
            break;
            
        case 7:
            printf("\n=== RUNNING ALL SORTING ALGORITHMS ===\n");
            printf("\n----- EFFICIENT ALGORITHMS -----\n");
            
            // Make copies of the array for each algorithm
            int copy1[TAMANHO], copy2[TAMANHO], copy3[TAMANHO], 
                copy4[TAMANHO], copy5[TAMANHO], copy6[TAMANHO];
                
            memcpy(copy1, test_case, sizeof(test_case));
            memcpy(copy2, test_case, sizeof(test_case));
            memcpy(copy3, test_case, sizeof(test_case));
            memcpy(copy4, test_case, sizeof(test_case));
            memcpy(copy5, test_case, sizeof(test_case));
            memcpy(copy6, test_case, sizeof(test_case));
            
            // Run all algorithms
            printf("\n--- BUBBLE SORT ---\n");
            bolha(copy1, print_steps);
            
            printf("\n--- INSERTION SORT ---\n");
            insertion(copy2, print_steps);
            
            printf("\n--- SELECTION SORT ---\n");
            selecao(copy3, print_steps);
            
            printf("\n----- JOKE/INEFFICIENT ALGORITHMS -----\n");
            
            printf("\n--- BOGO SORT ---\n");
            bogosort(copy4, print_steps);
            
            printf("\n--- STALIN SORT ---\n");
            stalin_sort(copy5, print_steps);
            
            printf("\n--- SLEEP SORT ---\n");
            sleep_sort(copy6, print_steps);

            int copy7[TAMANHO];
            memcpy(copy7, test_case, sizeof(test_case));

            printf("\n--- MERGE SORT ---\n");
            mergesort(copy7, print_steps);

			printf("n--- QUICK SORT ---\n");
            mergesort(copy7, print_steps);
            printf("\n=== ALL SORTING ALGORITHMS COMPLETED ===\n");
            break;     
        case 8:
            mergesort(test_case, print_steps);
            break;
        case 9:
            memsortTest();
            break;
	    case 10:
			quick_sort(test_case, print_steps);
			break;
    	case 11:
			heap_sort(test_case, print_steps);
			break;
 
    	case 12:
			radix_sort(test_case, print_steps);
			break;
      	case 13:
			shell_sort(test_case, print_steps);
			break;
case 14:
    bucket_sort(test_case, print_steps);
    break;
case 15:
    tim_sort(test_case, print_steps);
    break;
case 16:
    comb_sort(test_case, print_steps);
    break;
case 17:
    intro_sort(test_case, print_steps);
    break;
case 18:
    gnome_sort(test_case, print_steps);
    break;
case 19:
    cocktail_sort(test_case, print_steps);
    break;
case 20:
    pancake_sort(test_case, print_steps);
    break;
case 21:
    stooge_sort(test_case, print_steps);
    break;
case 22:
    bitonic_sort(test_case, print_steps);
    break;
case 23:
    smooth_sort(test_case, print_steps);
    break;
case 24:
    library_sort(test_case, print_steps);
    break;
case 25:
    bead_sort(test_case, print_steps);
    break;
case 26:
    odd_even_sort(test_case, print_steps);
    break;
       default:
            printf("Invalid choice!\n");
    }
    
    return 0;
}
