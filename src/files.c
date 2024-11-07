#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include "lib.h"

#define LABEL_SIZE 16
typedef unsigned char byte;

#pragma pack(push, 1)
typedef struct SimpleGameBlockHeader {
    char label[LABEL_SIZE];
    int version[3];
    long long int dataByteSize;
} SimpleGameBlockHeader;
#pragma pack(pop)

#define BV(X, N) (((X) >> (N)) & 0x1)

typedef struct GameBlockHeader {
    char label[16];
    unsigned char version[3];
    unsigned long long dataByteSize;
} GameBlockHeader;

// Serialization and Deserialization Functions
static void SerializeBlock(FILE *f, const GameBlockHeader *blockHeader, const void *data) {
    fwrite(blockHeader, sizeof(GameBlockHeader), 1, f);
    fwrite(data, blockHeader->dataByteSize, 1, f);
}

static void *DeserializeBlock(FILE *f, GameBlockHeader *blockHeader) {
    if (fread(blockHeader, sizeof(GameBlockHeader), 1, f) != 1) {
        return NULL;
    }
    void *data = malloc(blockHeader->dataByteSize);
    if (data == NULL || fread(data, blockHeader->dataByteSize, 1, f) != 1) {
        free(data);
        return NULL;
    }
    return data;
}

// Demonstration of Save and Load
void saves() {
    FILE *f = fopen("data.bin", "wb+");
    if (!f) {
        perror("Failed to open file for writing");
        return;
    }

    GameBlockHeader blockHeader;
    strncpy(blockHeader.label, "Hi", sizeof(blockHeader.label) - 1);
    blockHeader.version[0] = 0;
    blockHeader.version[1] = 2;
    blockHeader.version[2] = 0;
    blockHeader.dataByteSize = sizeof(float);
    const float pi = 3.14f;

    SerializeBlock(f, &blockHeader, &pi);

    strncpy(blockHeader.label, "Car", sizeof(blockHeader.label) - 1);
    blockHeader.dataByteSize = sizeof(unsigned char);
    const unsigned char two = 2;
    SerializeBlock(f, &blockHeader, &two);

    rewind(f);

    GameBlockHeader loadedHeader;
    float *number = (float *)DeserializeBlock(f, &loadedHeader);
    if (number) {
        printf("Label: %s, Version: %hhu.%hhu.%hhu, Byte Size: %llu, Val: %f\n", 
               loadedHeader.label, loadedHeader.version[0], loadedHeader.version[1], 
               loadedHeader.version[2], loadedHeader.dataByteSize, *number);
        free(number);
    }

    unsigned char *integer = (unsigned char *)DeserializeBlock(f, &loadedHeader);
    if (integer) {
        printf("Label: %s, Version: %hhu.%hhu.%hhu, Byte Size: %llu, Val: %hhu\n", 
               loadedHeader.label, loadedHeader.version[0], loadedHeader.version[1], 
               loadedHeader.version[2], loadedHeader.dataByteSize, *integer);
        free(integer);
    }

    fclose(f);
}

// File Loading Function
static void load_file(unsigned char **out, unsigned *outlen, const char *file_name) {
    FILE *file_pointer = fopen(file_name, "rb");
    if (!file_pointer) {
        perror("Error opening file");
        *out = NULL;
        *outlen = 0;
        return;
    }

    if (fseek(file_pointer, 0, SEEK_END) != 0) goto error;
    long file_size = ftell(file_pointer);
    if (file_size == -1L) goto error;
    *outlen = (unsigned)file_size;
    if (fseek(file_pointer, 0, SEEK_SET) != 0) goto error;

    *out = (unsigned char *)malloc(*outlen);
    if (!*out || fread(*out, 1, *outlen, file_pointer) != *outlen) {
        goto error;
    }

    fclose(file_pointer);
    return;

error:
    if (*out) {
        free(*out);
        *out = NULL;
    }
    *outlen = 0;
    fclose(file_pointer);
}

// Bitwise Display Function
void print_byte(byte b) {
    printf("%d%d%d%d_%d%d%d%d",
           BV(b, 7), BV(b, 6), BV(b, 5), BV(b, 4),
           BV(b, 3), BV(b, 2), BV(b, 1), BV(b, 0));
}

// Copy File Function
void filescopy(FILE *file) {
    FILE *new_file = fopen("copy.txt", "w");
    if (!new_file) {
        perror("Failed to open new file for copying");
        return;
    }

    int c;
    while ((c = fgetc(file)) != EOF) {
        fputc(c, new_file);
    }

    fclose(new_file);
}

// File Operation Example
int fileop() {
    unsigned char *data = NULL;
    unsigned data_len = 0;
    const char *file_name = "integers.txt";

    load_file(&data, &data_len, file_name);

    if (data) {
        printf("File loaded. Size: %u bytes\n", data_len);
        free(data);
    } else {
        printf("Failed to load file: %s\n", file_name);
    }

    return 0;
}

// Error Checking and Argument Printing
int errs(int argc, char **argv) {
    printf("args: [");
    for (int i = 0; i < argc; i++) {
        if (i > 0) printf(", ");
        printf("argv[%d]: %s", i, argv[i]);
    }
    printf("]\n");

    if (argc < 2) {
        fprintf(stderr, "Please provide a filename as a command-line argument.\n");
        return 1;
    }

    FILE *fptr = fopen(argv[1], "rb");
    if (!fptr) {
        perror("Failed to open the file");
        return 1;
    }

    byte buf;
    while (fread(&buf, 1, 1, fptr)) {
        print_byte(buf);
        printf(" ");
    }

    if (ferror(fptr)) perror("Error while reading the file");

    fclose(fptr);
    return 0;
}

// Main File Copy Operation with Metadata
int files(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <source file> <destination file>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    char *new_filename = argv[2];
    struct stat metadata;
    if (stat(filename, &metadata) != 0) {
        perror("Stat failed");
        return 1;
    }

    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening source file");
        return 1;
    }

    FILE *new_file = fopen(new_filename, "wb");
    if (!new_file) {
        perror("Error opening destination file");
        fclose(file);
        return 1;
    }

    char *buf = malloc(metadata.st_size);
    if (!buf) {
        perror("Memory allocation failed");
        fclose(file);
        fclose(new_file);
        return 1;
    }

    fread(buf, 1, metadata.st_size, file);
    fwrite(buf, 1, metadata.st_size, new_file);

    free(buf);
    fclose(file);
    fclose(new_file);

    return 0;
}

void filesf(FILE *file, FILE *read){
    saves();
    fileop();
    //files(argc, argv);
    //errs(argc, argv);
}
