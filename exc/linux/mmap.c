#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FILENAME "file.dat"
#define LENGTH 4096 // Size of the mapping

int main() {
    // Open the file for reading and writing
    int fd = open(FILENAME, O_RDWR);
    if (fd == -1) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Ensure the file is large enough
    if (lseek(fd, LENGTH - 1, SEEK_SET) == -1) {
        perror("Error seeking in file");
        close(fd);
        return EXIT_FAILURE;
    }

    // Write a byte to the end of the file to ensure its size
    if (write(fd, "", 1) != 1) {
        perror("Error writing to file");
        close(fd);
        return EXIT_FAILURE;
    }

    // Map the file at the specified address
    void* addr = (void*)0x10000; // Example address
    void* result = mmap(addr, LENGTH, PROT_READ | PROT_WRITE, MAP_FIXED | MAP_SHARED, fd, 0);
    if (result == MAP_FAILED) {
        perror("Error mapping file");
        close(fd);
        return EXIT_FAILURE;
    }

    // Example: Write to the mapped memory
    strcpy(result, "Hello, mmap!");
}
