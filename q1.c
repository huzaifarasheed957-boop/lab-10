#include <stdio.h>
#include <string.h>

#define MAX_FLIGHTS 50

struct Flight {
    int  flightNumber;
    char departureCity[30];
    char destinationCity[30];
    char date[15];
    int  availableSeats;
};

struct Flight flights[MAX_FLIGHTS];
int flightCount = 0;

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

void addFlight() {
    int n;
    if (flightCount >= MAX_FLIGHTS) {
        printf("Flight list is full.\n");
        return;
    }
    n = flightCount;

    flights[n].flightNumber = readInt("Flight number: ");

    printf("Departure city: ");
    fgets(flights[n].departureCity, sizeof(flights[n].departureCity), stdin);
    flights[n].departureCity[strcspn(flights[n].departureCity, "\n")] = '\0';

    printf("Destination city: ");
    fgets(flights[n].destinationCity, sizeof(flights[n].destinationCity), stdin);
    flights[n].destinationCity[strcspn(flights[n].destinationCity, "\n")] = '\0';

    printf("Date (DD-MM-YYYY): ");
    fgets(flights[n].date, sizeof(flights[n].date), stdin);
    flights[n].date[strcspn(flights[n].date, "\n")] = '\0';

    flights[n].availableSeats = readInt("Available seats: ");

    flightCount++;
    printf("Flight added successfully.\n");
}

void displayFlights() {
    int i;
    if (flightCount == 0) {
        printf("No flights available.\n");
        return;
    }
    printf("\n%-10s %-15s %-15s %-12s %-6s\n",
           "Flight No", "From", "To", "Date", "Seats");
    printf("------------------------------------------------------------\n");
    for (i = 0; i < flightCount; i++) {
        printf("%-10d %-15s %-15s %-12s %-6d\n",
               flights[i].flightNumber,
               flights[i].departureCity,
               flights[i].destinationCity,
               flights[i].date,
               flights[i].availableSeats);
    }
}

void bookSeat() {
    int i, num, seats;
    num = readInt("Enter flight number to book: ");

    for (i = 0; i < flightCount; i++) {
        if (flights[i].flightNumber == num) {
            seats = readInt("Seats to book: ");

            if (seats <= 0) {
                printf("Invalid number of seats.\n");
            } else if (seats > flights[i].availableSeats) {
                printf("Only %d seat(s) available.\n", flights[i].availableSeats);
            } else {
                flights[i].availableSeats -= seats;
                printf("Booked %d seat(s). Remaining: %d\n",
                       seats, flights[i].availableSeats);
            }
            return;
        }
    }
    printf("Flight not found.\n");
}

int main() {
    int choice;
    do {
        printf("\n===== FLIGHT MANAGEMENT =====\n");
        printf("1. Add Flight\n");
        printf("2. Display Flight Details\n");
        printf("3. Book a Seat\n");
        printf("4. Exit\n");
        choice = readInt("Choice: ");

        switch (choice) {
            case 1: addFlight();      break;
            case 2: displayFlights(); break;
            case 3: bookSeat();       break;
            case 4: printf("Goodbye!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);

    return 0;
}