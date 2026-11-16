#include <stdio.h>
#include <string.h>

#define MAX_MOVIES 100

struct Movie {
    char  title[50];
    char  genre[30];
    char  director[40];
    int   releaseYear;
    float rating;
};

struct Movie movies[MAX_MOVIES];
int movieCount = 0;

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int readInt(const char prompt[]) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1) {
            clearBuffer();
            return value;
        }
        printf("Invalid input. Enter a number.\n");
        clearBuffer();
    }
}

float readFloat(const char prompt[]) {
    float value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%f", &value) == 1) {
            clearBuffer();
            return value;
        }
        printf("Invalid input. Enter a number.\n");
        clearBuffer();
    }
}

void readString(const char prompt[], char dest[], int size) {
    printf("%s", prompt);
    fgets(dest, size, stdin);
    dest[strcspn(dest, "\n")] = '\0';
}

int toLower(int ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return ch + 32;
    }
    return ch;
}

int equalsIgnoreCase(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (toLower(a[i]) != toLower(b[i])) {
            return 0;
        }
        i++;
    }
    return a[i] == b[i];
}

void printHeader() {
    printf("\n%-25s %-12s %-18s %-6s %-6s\n",
           "Title", "Genre", "Director", "Year", "Rating");
    printf("--------------------------------------------------------------------\n");
}

void printMovie(int i) {
    printf("%-25s %-12s %-18s %-6d %-6.1f\n",
           movies[i].title,
           movies[i].genre,
           movies[i].director,
           movies[i].releaseYear,
           movies[i].rating);
}

void addMovie() {
    int n;
    if (movieCount >= MAX_MOVIES) {
        printf("Movie list is full.\n");
        return;
    }
    n = movieCount;

    readString("Title: ", movies[n].title, sizeof(movies[n].title));
    readString("Genre: ", movies[n].genre, sizeof(movies[n].genre));
    readString("Director: ", movies[n].director, sizeof(movies[n].director));
    movies[n].releaseYear = readInt("Release year: ");
    movies[n].rating = readFloat("Rating (0-10): ");

    movieCount++;
    printf("Movie added successfully.\n");
}

void displayAll() {
    int i;
    if (movieCount == 0) {
        printf("No movies available.\n");
        return;
    }
    printHeader();
    for (i = 0; i < movieCount; i++) {
        printMovie(i);
    }
}

void searchByGenre() {
    char genre[30];
    int i, found = 0;

    readString("Enter genre to search: ", genre, sizeof(genre));

    for (i = 0; i < movieCount; i++) {
        if (equalsIgnoreCase(movies[i].genre, genre)) {
            if (!found) {
                printHeader();
            }
            printMovie(i);
            found = 1;
        }
    }
    if (!found) {
        printf("No movies found in genre '%s'.\n", genre);
    }
}

int main() {
    int choice;
    do {
        printf("\n===== MOVIE MANAGEMENT =====\n");
        printf("1. Add New Movie\n");
        printf("2. Search by Genre\n");
        printf("3. Display All Movies\n");
        printf("4. Exit\n");
        choice = readInt("Choice: ");

        switch (choice) {
            case 1: addMovie();      break;
            case 2: searchByGenre(); break;
            case 3: displayAll();    break;
            case 4: printf("Goodbye!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);

    return 0;
}
