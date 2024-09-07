#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// prompt> ./wzip file1.txt file2.txt > output.z

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    FILE *output = stdout;

    int count = 0;
    char last_char = '\0';

    for (int i = 1; i < argc; i++)
    {
        FILE *f = fopen(argv[i], "r");
        if (f == NULL)
        {
            exit(1);
        }

        char c;

        while ((c = fgetc(f)) != EOF)
        {

            if (c == last_char)
            {
                count++;
            }
            else
            {
                if (count > 0)
                {
                    fwrite(&count, sizeof(int), 1, output);
                    fwrite(&last_char, sizeof(char), 1, output);
                }
                last_char = c;
                count = 1;
            }
        }
        fclose(f);
    }
    if (count > 0)
    {
        fwrite(&count, sizeof(int), 1, output);
        // printf("%c", last_char);
        fwrite(&last_char, sizeof(char), 1, output);
    }

    return 0;
}

