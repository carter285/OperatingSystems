//This Project invloved reversing a linked list from various inputs
// reverse.c has 3 cases --
// 1.(./reverse) No file input, get input from terminal
// 2. (./reverse InputFile) reverse the contents of an input file and display to terminal
// 3. (./reverse InputFile OutputFile) Reverse contents of Input file and place into Output file.

//Topics:
// Linked list - Pointers - Malloc -
// Struct Stats for File comparision
// Getline, strcspn, strdup,  function calls
// File I/O - fopen, fclose, file error handeling

#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct DataNode
{
    char *word;
    struct DataNode *next;
};

void addToLinkedList(struct DataNode **head, const char *word);
void printList(struct DataNode *head);
void freeList(struct DataNode *head);
void argcIsOne();
void argcIsTwo(const char *filename);
void argcIsThree(const char *input, const char *output);

int main(int argc, char *argv[]){

    if (argc == 1){
        argcIsOne();
    }
    else if (argc == 2){
        argcIsTwo(argv[1]);
    }
    else if (argc == 3){
        argcIsThree(argv[1], argv[2]);
        //printf("\nComplete\n");
    }
    else if (argc > 3){
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }
    return 0;
}
///------------------///
void addToLinkedList(struct DataNode **head, const char *word)
{
    struct DataNode *newDataNode = (struct DataNode *)malloc(sizeof(struct DataNode)); // allocates mem
    if (newDataNode == NULL)
    {
        perror("malloc");
        exit(1);
    }
    //duplicates a string. Allocates memory for a new string, copies the content of the provided string,  into the new memory, and returns a pointer to the new string.
    newDataNode->word = strdup(word); // The returned pointer must be passed to free to avoid a memory leak.
    newDataNode->next = *head;
    *head = newDataNode;
}

void printList(struct DataNode *head)
{
    while (head != NULL)
    {
        printf("%s\n", head->word);
        head = head->next;
    }
}

void freeList(struct DataNode *head)
{
    while (head != NULL)
    {
        struct DataNode *temp = head;
        head = head->next;
        free(temp->word);
        free(temp);
    }
}

void argcIsOne()
{
    struct DataNode *head = NULL; // Initialize an empty linked list

    char *buffer = NULL;
    size_t size = 0;

    //printf("Enter a word (type 'q' to end):\n");

    while (1)
    {
        // Read a line from standard input
        // printf("Enter a word (type 'q' to end): ");
        ssize_t bytesRead = getline(&buffer, &size, stdin);

        // Check for errors/end-of-file
        if (bytesRead == -1)
        {

            //perror("getline");
            break;
        }
        buffer[strcspn(buffer, "\n")] = '\0'; // returns the location of the new line and switches it to end of line
        // Check if the user wants to exit
        // if (strcmp(buffer, "q") == 0)
        // {
        //     break;
        // }
        // Add the word to the linked list
        addToLinkedList(&head, buffer);
    }
    // Print the words in the linked list
    //printf("\nWords entered:\n");
    printList(head);

    // Free the dynamically allocated buffer and the linked list
    free(buffer);
    freeList(head);
}

void argcIsTwo(const char *filename)
{
    //const char *filepath = filename;
    FILE *f = fopen(filename, "r");
    //struct DataNode *head = NULL; // Initialize an empty linked list

    if (f == NULL)
    {
        fprintf(stderr, "reverse: cannot open file '%s'\n", filename);
        exit(1);
    }
    struct DataNode *head = NULL;
    // int linenum = 1;
    size_t num;
    char *line = NULL;
    // In a loop, call getline to read the next line from f,
    while (getline(&line, &num, f) != -1)
    {
        // Remove newline character at the end
        line[strcspn(line, "\n")] = '\0';
        // Add the word to the linked list
        addToLinkedList(&head, line);
        // printf("%3d: %s", linenum, line);
        // linenum++;
    }
    // Print the words in the linked list

    //printf("\nLines in file\n");
    printList(head);
    // Free the allocated lines and the linked list
    free(line);
    freeList(head);
    fclose(f);
}

void argcIsThree(const char *input, const char *output)
{

    struct stat inP;
    stat(input, &inP);

    struct stat outP;
    stat(output, &outP);

    // --- Print the iDataNode number and file size ---

    // printf("Input iDataNode number: %lld\n", inP.st_ino);
    // printf("Input size in bytes: %lld\n", inP.st_size);

    // printf("Output iDataNode number: %lld\n", outP.st_ino);
    // printf("Output size in bytes: %lld\n", outP.st_size);

    if (inP.st_ino == outP.st_ino)
    {
        //fprintf(stderr, "reverse: cannot open file '%s'\n", input);
        fprintf(stderr, "reverse: input and output file must differ\n");
        exit(1);
    }
    FILE *in = fopen(input, "r");
    FILE *out = fopen(output, "w");

    if (in == NULL)
    {
        fprintf(stderr, "reverse: cannot open file '%s'\n", input);
        exit(1);
    }
    if (out ==NULL){
        fprintf(stderr, "reverse: cannot open file '%s'\n", input);
        exit(1);
    }
    struct DataNode *head = NULL;

    size_t num;
    char *line = NULL;
    // In a loop read the next line from f,
    while (getline(&line, &num, in) != -1)
    {

        line[strcspn(line, "\n")] = '\0';
        // Add the word to the linked list
        addToLinkedList(&head, line);
        // printf("%3d: %s", linenum, line);
        // linenum++;
    }
    while (head != NULL)
    {
        fprintf(out,"%s\n",head->word);
        head = head->next;
    }

    //addListToFile(head,output); // pass through head pointer and output file
    free(line);
    freeList(head);
    fclose(in);
    fclose(out);
}

