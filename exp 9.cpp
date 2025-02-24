#include <stdio.h>
#include <stdlib.h>

void sender() {
    FILE *file = fopen("message_queue.txt", "w"); // Open file for writing
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    char message[100];
    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);

    fprintf(file, "%s", message); // Write message to file
    fclose(file);

    printf("Message sent successfully!\n");
}

void receiver() {
    FILE *file = fopen("message_queue.txt", "r"); // Open file for reading
    if (file == NULL) {
        printf("No message found!\n");
        return;
    }

    char message[100];
    fgets(message, sizeof(message), file);
    fclose(file);

    printf("Message received: %s\n", message);

    // Delete the file after reading (optional)
    remove("message_queue.txt");
}

int main() {
    int choice;
    printf("1. Send message\n2. Receive message\nChoose an option: ");
    scanf("%d", &choice);
    getchar(); // Consume newline character

    if (choice == 1)
        sender();
    else if (choice == 2)
        receiver();
    else
        printf("Invalid option\n");

    return 0;
}
