#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }

    FILE *o = stdout;
    int count = 0;
    char c = '\0';

    for (int i = 1; i < argc; i++)
    {
        FILE *f = fopen(argv[i], "r");
        if (f == NULL)
        {
            perror("Error opening file");
            exit(1);
        }

        while (fread(&count, sizeof(int), 1, f) == 1 && fread(&c, sizeof(char), 1, f) == 1)
        {
            for (int j = 0; j < count; j++)
            {
                fwrite(&c, 1, 1, o);
            }
        }
        fclose(f);
    }

    return 0;
}

