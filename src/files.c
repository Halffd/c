
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

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