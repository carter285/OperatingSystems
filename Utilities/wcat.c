#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    if (argc == 1)
    {
        return 0;
    }
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {

            if (argv[i] == NULL)
            {
                //fprintf(stderr, "wcat: cannot open file\n");
                //exit(1);
                return 0;
            }
            // printf("argv = %s\n", argv[i]);
            char str[100];
            FILE *f = fopen(argv[i], "r");

            if (f == NULL)
            {
                //fprintf(stderr, "wcat: cannot open file\n");
                printf("wcat: cannot open file\n");
                exit(1);
                //return 0;
            }
            while (fgets(str, 100, f) != NULL)
            {
                printf("%s", str);
            }
            fclose(f);
        }
    }
    return 0;
}
