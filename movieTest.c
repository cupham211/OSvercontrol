//
//  movieTest.c
//  first C project
//
//  Created by Christine Pham on 9/28/20.
//  Sashay into project folder from Hyper and input:
//  gcc --std=gnu99 -o movie movieTest.c
//  ./movie movie_sample_1.csv

#include "movieTest.h"
/* struct for movie information */
struct movies
{
    char *title;
    int year;
    char *languages;
    float rating;
    struct movies *next;
};

/* Parse the current line which is space delimited and create a
*  movie struct with the data in this line
*/
struct movies *createMovie(char *currLine)
{
    struct movies *currMovie = malloc(sizeof(struct movies));

    // For use with strtok_r
    char *saveptr;

    // The first token is the title
    char *token = strtok_r(currLine, ",", &saveptr);
    currMovie->title = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->title, token);

    // The next token is the year
    token = strtok_r(NULL, ",", &saveptr);
    currMovie->year = atoi(token);

    // The next token is the language
    token = strtok_r(NULL, ",", &saveptr);
    currMovie->languages = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->languages, token);

    // The last token is the rating
    token = strtok_r(NULL, "\n", &saveptr);
    currMovie->rating = atof(token);

    // Set the next node to NULL in the newly created student entry
    currMovie->next = NULL;

    return currMovie;
}

struct movies *processFile(char *filePath)
{
    // Open the specified file for reading only
    FILE *movieFile = fopen(filePath, "r");

    char *currLine = NULL;
    size_t len = 0;
    ssize_t nread;

    // The head of the linked list
    struct movies *head = NULL;
    // The tail of the linked list
    struct movies *tail = NULL;

    // Read the file line by line
    while ((nread = getline(&currLine, &len, movieFile)) != -1)
    {
        // Get a new student node corresponding to the current line
        struct movies *newNode = createMovie(currLine);

        // Is this the first node in the linked list?
        if (head == NULL)
        {
            // This is the first node in the linked link
            // Set the head and the tail to this node
            head = newNode;
            tail = newNode;
        }
        else
        {
            // This is not the first node.
            // Add this node to the list and advance the tail
            tail->next = newNode;
            tail = newNode;
        }
    }
    free(currLine);
    fclose(movieFile);
    return head;
}

/*
* Print data for the given student
*/
void printMovies(struct movies* aMovie){
  printf("%s--%d--%s--%.1f\n", aMovie->title,
               aMovie->year,
               aMovie->languages,
               aMovie->rating);
}
/*
* Print the linked list of students
*/
void printMovieList(struct movies *list)
{
    while (list != NULL)
    {
        printMovies(list);
        list = list->next;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./movies movie_sample_1.csv\n");
        return EXIT_FAILURE;
    }
    struct movies *list = processFile(argv[1]);
    printMovieList(list);
    return EXIT_SUCCESS;
}
