#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void highlight_word(const char *input, const char *word)
{
    const char *pos = input;
    while ((pos = strstr(pos, word)) != NULL)
    {
        // Print the text before the word in white
        printf("\033[37m%.*s", (int) (pos - input), input);

        // Print the word in red
        printf("\033[31m%s", word);

        // Reset color to white
        printf("\033[37m");

        // Move pos forward by the length of the word
        pos += strlen(word);
        input = pos;
    }
    // Print the rest of the string in white
    printf("\033[37m%s", input);
}

int main(int argc, char *argv[])
{

    if (argc == 1)
    {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }
    if (argc == 2)
    {
        char str[100];
        char *targetWord = argv[1];
        while (fgets(str, sizeof(str), stdin) != NULL)
        {
            // Remove the newline character
            str[strcspn(str, "\n")] = '\0';

            // Check if the target word is in the input
            if (strstr(str, targetWord) != NULL)
            {
                printf("%s\n", str);


                // highlight_word(str, targetWord);
                // printf("\n");
            }
        }
    }
    if (argc > 2)
    {
        char *targetWord = argv[1];
        //printf("Target word: %s \n", targetWord);
        for (int i = 2; i <= argc; i++)
        {
            if (argv[i] != NULL)
            {
                FILE *f = fopen(argv[i], "r");
                //printf("\nFile Trying To Open: %s \n", argv[i]);
                if (f == NULL)
                {
                    // fprintf(stderr, "wgrep: cannot open file%s\n", argv[i]);
                    printf("wgrep: cannot open file\n");
                    exit(1);
                }

                char *line = NULL;
                size_t len = 0;

                while (1)
                {

                    ssize_t read = getline(&line, &len, f);
                    if (read == -1){
                        break;
                    }
                    // Remove the newline character
                    line[strcspn(line, "\n")] = '\0';

                    // Check if the target word is in the line
                    if (strstr(line, targetWord) != NULL)
                    {
                        printf("%s\n", line);


                        // highlight_word(line, targetWord);
                        // printf("\n");
                    }
                }
                free(line);
                fclose(f);
            }
        }
    }
}
