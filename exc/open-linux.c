#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int main(void)
{
    // Step 1: Create directory "exercicio"
    printf("Creating directory '/home/teste/_exercicio'...\n");
    if (mkdir("/home/teste/_exercicio", S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH) != 0)
    {
        perror("Failed to create directory");
        return EXIT_FAILURE;
    }
    printf("Directory created successfully.\n");

    // Step 2: Change directory to "exercicio"
    printf("Changing directory to '/home/teste/_exercicio'...\n");
    if (chdir("/home/teste/_exercicio") != 0)
    {
        perror("Failed to change directory");
        return EXIT_FAILURE;
    }
    printf("Changed directory successfully.\n");

    // Step 3: Change permissions of the directory
    printf("Changing permissions of '/home/teste/_exercicio' to 0755...\n");
    if (chmod("/home/teste/_exercicio", S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) != 0)
    {
        perror("Failed to change permissions");
        return EXIT_FAILURE;
    }
    printf("Permissions changed successfully.\n");

    // Step 4: Open file "example.txt"
    printf("Opening file 'example.txt' for writing...\n");
    int fd = open("example.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1)
    {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }
    printf("File opened successfully.\n");

    // Step 5: Write data to the file
    const char* data = "Hello, world!\n";
    printf("Writing data to file: '%s'\n", data);
    if (write(fd, data, strlen(data)) != strlen(data))
    {
        perror("Failed to write to file");
        close(fd);
        return EXIT_FAILURE;
    }
    printf("Data written successfully.\n");

    // Step 6: Read data back from the file
    printf("Reading data back from file...\n");
    char buffer[100] = {0};
    lseek(fd, 0, SEEK_SET); // Reset file pointer to the beginning
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead == -1)
    {
        perror("Failed to read from file");
        close(fd);
        return EXIT_FAILURE;
    }
    buffer[bytesRead] = '\0'; // Null-terminate the buffer
    printf("Data read from file: '%s'\n", buffer);

    // Step 7: Close the file
    printf("Closing the file...\n");
    if (close(fd) != 0)
    {
        perror("Failed to close file");
        return EXIT_FAILURE;
    }
    printf("File closed successfully.\n");

    return EXIT_SUCCESS;
}