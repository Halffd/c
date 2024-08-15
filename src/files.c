#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include "lib.h"

#define LABEL_SIZE 16

#pragma pack(push, 1)
typedef struct SimpleGameBlockHeader
{
    char label[LABEL_SIZE];
    int version[3];
    long long int dataByteSize;
} SimpleGameBlockHeader;
#pragma pack(pop)
typedef unsigned char byte;

#define BV(X, N) (((X) >> (N)) & 0x1)

typedef struct GameBlockHeader
{
    char label[16];
    unsigned char version[3];
    unsigned long long dataByteSize;
} GameBlockHeader;

static void SerializeBlock(FILE *f, const GameBlockHeader *blockHeader, const void *data)
{
    unsigned int byteSize = sizeof(GameBlockHeader) + blockHeader->dataByteSize;
    fwrite(blockHeader, sizeof(GameBlockHeader), 1, f);
    fwrite(data, blockHeader->dataByteSize, 1, f);
}

static void *DeserializeBlock(FILE *f, GameBlockHeader *blockHeader)
{
    fread(blockHeader, sizeof(GameBlockHeader), 1, f);
    void *data = malloc(blockHeader->dataByteSize);
    fread(data, blockHeader->dataByteSize, 1, f);
    return data;
}

void saves()
{
    FILE *f = fopen("data.bin", "wb+");
    if (f == NULL)
    {
        printf("Failed to open file for writing.\n");
        return;
    }

    {
        GameBlockHeader blockHeader;
        strncpy(blockHeader.label, "Hi", sizeof(blockHeader.label));
        blockHeader.version[0] = 0;
        blockHeader.version[1] = 2;
        blockHeader.version[2] = 0;
        blockHeader.dataByteSize = sizeof(float);
        const float pi = 3.14;

        SerializeBlock(f, &blockHeader, &pi);

        strncpy(blockHeader.label, "Car", sizeof(blockHeader.label));
        blockHeader.dataByteSize = sizeof(unsigned char);
        const unsigned char two = 2;

        SerializeBlock(f, &blockHeader, &two);
    }

    rewind(f);

    {
        GameBlockHeader blockHeader;
        float *number = (float *)DeserializeBlock(f, &blockHeader);
        printf("Label: %s, Version: %hhu, %hhu, %hhu, Byte Size: %llu, Val: %f\n", blockHeader.label,
               blockHeader.version[0], blockHeader.version[1], blockHeader.version[2],
               blockHeader.dataByteSize, *number);
        free(number);

        unsigned char *integer = (unsigned char *)DeserializeBlock(f, &blockHeader);
        printf("Label: %s, Version: %hhu, %hhu, %hhu, Byte Size: %llu, Val: %hhu\n", blockHeader.label,
               blockHeader.version[0], blockHeader.version[1], blockHeader.version[2],
               blockHeader.dataByteSize, *integer);
        free(integer);
    }

    fclose(f);
}
static void SerializeBlock0(FILE *f, const SimpleGameBlockHeader *blockHeader, const void *data)
{
    fwrite(blockHeader, sizeof(SimpleGameBlockHeader), 1, f);
    fwrite(data, (size_t)blockHeader->dataByteSize, 1, f);
}

static void *DeserializeBlock0(FILE *f, SimpleGameBlockHeader *blockHeader)
{
    fread(blockHeader, sizeof(SimpleGameBlockHeader), 1, f);
    void *data = malloc((size_t)blockHeader->dataByteSize);
    fread(data, (size_t)blockHeader->dataByteSize, 1, f);
    return data;
}
int savestst(void)
{

    // Example usage
    FILE *file = fopen("data.bin", "wb");
    if (file == NULL)
    {
        printf("Failed to open file for writing.\n");
        return 1;
    }

    // Create a block header
    SimpleGameBlockHeader header;
    snprintf(header.label, LABEL_SIZE, "Example");
    header.version[0] = 1;
    header.version[1] = 2;
    header.version[2] = 3;
    header.dataByteSize = sizeof(int) * 10;

    // Create some data to serialize
    int *data = (int *)malloc(header.dataByteSize);
    for (int i = 0; i < 10; i++)
    {
        data[i] = i;
    }

    // Serialize the block
    SerializeBlock0(file, &header, data);

    fclose(file);

    // Deserialize the block
    file = fopen("data.bin", "rb");
    if (file == NULL)
    {
        printf("Failed to open file for reading.\n");
        return 1;
    }

    SimpleGameBlockHeader deserializedHeader;
    void *deserializedData = DeserializeBlock0(file, &deserializedHeader);

    fclose(file);

    // Print the deserialized data
    printf("Deserialized Header:\n");
    printf("Label: %s\n", deserializedHeader.label);
    printf("Version: %u.%u.%u\n", deserializedHeader.version[0], deserializedHeader.version[1], deserializedHeader.version[2]);
    printf("Data Byte Size: %llu\n", deserializedHeader.dataByteSize);

    printf("Deserialized Data:\n");
    for (int i = 0; i < deserializedHeader.dataByteSize; i++)
    {
        printf("%u ", ((int *)deserializedData)[i]);
    }
    printf("\n");

    free(deserializedData);

    return 0;
}
static void load_file(unsigned char** out, unsigned* outlen, const unsigned char* file_name) {
    FILE* file_pointer;
    if ((file_pointer = fopen(file_name, "rb")) == NULL) goto error;
    if (fseek(file_pointer, 0, SEEK_END) != 0) goto error;
    long file_size = ftell(file_pointer);
    if (file_size == -1L) goto error;
    *outlen = (unsigned)file_size;
    if (fseek(file_pointer, 0, SEEK_SET) != 0) goto error;
    *out = (unsigned char*)malloc(*outlen);
    if (*out == NULL) goto error;
    if (fread(*out, 1, *outlen, file_pointer) != *outlen) goto error;
    if (fclose(file_pointer) != 0) goto error;
    return;

error:
    if (*out) {
        free(*out);
        *out = NULL;
    }
    *outlen = 0;
}
int dates()
{

    FILE *date_p = fopen("/.../.../dateandtime", "w");
    int out_iter = fseek(stdout, 0, SEEK_END);

    int i = 0;
    system("date");
    for (int end_out = fseek(stdout, 0, SEEK_END); out_iter < end_out; ++out_iter)
    {
        date_p[i] = stdout[out_iter];
        ++i;
    }
    fclose(date_p);
    return 0;
}

void print_byte(byte b) {
    printf("%d%d%d%d_%d%d%d%d",
        BV(b, 7), BV(b, 6), BV(b, 5), BV(b, 4),
        BV(b, 3), BV(b, 2), BV(b, 1), BV(b, 0)
    );
}

int errs() {
    int argc = ac;
    char** argv = av;
    printf("args:[");
    for (int i = 0; i < argc; i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("argv[%i]:%s", i, argv[i]);
    }
    printf("]\n");

    if (argc < 2) {
        printf("Please provide a filename as a command-line argument.\n");
        return 1;
    }

    FILE *fptr = fopen(argv[1], "rb");
    if (fptr == NULL) {
        perror("Failed to open the file");
        return 1;
    }

    byte buf = 0;

    while (!feof(fptr) && !ferror(fptr)) {
        if (fread(&buf, 1, 1, fptr)) {
            print_byte(buf);
            printf(" ");
        }
    }

    if (ferror(fptr)) {
        perror("Error while reading the file");
    }

    fclose(fptr);
    return 0;
}
int fileop() {
    unsigned char* data = NULL;
    unsigned data_len = 0;
    const unsigned char* file_name = "integers.txt";

    load_file(&data, &data_len, file_name);

    if (data != NULL) {
        // File loaded successfully
        printf("File loaded. Size: %u bytes\n", data_len);

        // Use the loaded data as needed

        // Free the allocated memory
        free(data);
        data = NULL;
    } else {
        // Error loading file
        printf("Failed to load file: %s\n", file_name);
    }

    return 0;
}
void filesf(FILE *file, FILE *read)
{
    errs();
    //fileop();
    //dates();
    // numb();
    // saves();
    /*while (1) {
    printf("0\n");
    fflush(stdout);
    printf("1\n");
    fflush(stdout);
    }*/
}
void filescopy(FILE *file)
{
    FILE *new_file;
    char new_filename[] = "copy.txt";
    int c;

    new_file = fopen(new_filename, "w");
    if (new_file == NULL)
    {
        printf("Failed to open the new file.\n");
        return;
    }

    while ((c = fgetc(file)) != EOF)
    {
        fputc(c, new_file);
    }

    fclose(file);
    fclose(new_file);
}
int files(int argc, char **argv)
{
    if (argc < 3)
        return 1;

    char *filename = argv[1];
    char *new_filename = argv[2];
    FILE *file;
    FILE *new_file;
    struct stat metadata;
    size_t filesize;
    char *buf;

    stat(filename, &metadata);
    filesize = metadata.st_size;

    buf = malloc(filesize);

    if (!(file = fopen(filename, "r")))
    {
        fprintf(stderr, "%s\n", strerror(errno));
        return 1;
    }

    if (!(new_file = fopen(new_filename, "w")))
    {
        fprintf(stderr, "%s\n", strerror(errno));
        return 1;
    }

    fread(buf, 1, filesize, file);
    fwrite(buf, 1, filesize, new_file);

    free(buf);
    fclose(file);
    fclose(new_file);

    return 0;
}
int numb(void)
{
    FILE *file = fopen("integers.txt", "rb");
    if (!file)
        return 1;

    int *numbers = NULL;
    size_t numbers_size = 0;
    size_t numbers_allocated = 0;

    int result = 0;
    while (!feof(file))
    {
        if (numbers_size == numbers_allocated)
        {
            if (numbers_allocated == 0)
                numbers_allocated = sizeof(int) * 4;
            else
                numbers_allocated *= 2;

            int *newNumbers = realloc(numbers, numbers_allocated);
            if (!newNumbers)
            {
                result = 2;
                goto done;
            }
            numbers = newNumbers;
        }

        int number = 0;
        if (fscanf(file, "%d", &number) == 1)
        {
            numbers[numbers_size] = number;
            numbers_size++;
        }
    }

    for (size_t i = 0; i < numbers_size; i++)
    {
        fprintf(stdout, "number %zu: %d\n", i, numbers[i]);
    }

done:
    free(numbers);
    fclose(file);
    return result;
}