#include <stdio.h>
#include <string.h>

#define MAX_FILES 100  // Maximum number of files in the directory
#define NAME_LEN 50    // Maximum file name length

typedef struct {
    char name[NAME_LEN];
    int in_use;  // 1 if file exists, 0 otherwise
} File;

File directory[MAX_FILES]; // Single-level directory

// Function to create a file
void createFile() {
    char filename[NAME_LEN];
    printf("Enter file name to create: ");
    scanf("%s", filename);

    // Check if file already exists
    for (int i = 0; i < MAX_FILES; i++) {
        if (directory[i].in_use && strcmp(directory[i].name, filename) == 0) {
            printf("Error: File '%s' already exists!\n", filename);
            return;
        }
    }

    // Find an empty slot
    for (int i = 0; i < MAX_FILES; i++) {
        if (!directory[i].in_use) {
            strcpy(directory[i].name, filename);
            directory[i].in_use = 1;
            printf("File '%s' created successfully!\n", filename);
            return;
        }
    }
    printf("Error: Directory is full!\n");
}

// Function to delete a file
void deleteFile() {
    char filename[NAME_LEN];
    printf("Enter file name to delete: ");
    scanf("%s", filename);

    for (int i = 0; i < MAX_FILES; i++) {
        if (directory[i].in_use && strcmp(directory[i].name, filename) == 0) {
            directory[i].in_use = 0;
            printf("File '%s' deleted successfully!\n", filename);
            return;
        }
    }
    printf("Error: File '%s' not found!\n", filename);
}

// Function to search for a file
void searchFile() {
    char filename[NAME_LEN];
    printf("Enter file name to search: ");
    scanf("%s", filename);

    for (int i = 0; i < MAX_FILES; i++) {
        if (directory[i].in_use && strcmp(directory[i].name, filename) == 0) {
            printf("File '%s' found!\n", filename);
            return;
        }
    }
    printf("File '%s' not found!\n", filename);
}

// Function to display all files
void displayFiles() {
    printf("\nFiles in the directory:\n");
    int found = 0;
    for (int i = 0; i < MAX_FILES; i++) {
        if (directory[i].in_use) {
            printf(" - %s\n", directory[i].name);
            found = 1;
        }
    }
    if (!found) {
        printf("No files found!\n");
    }
}

// Main function
int main() {
    int choice;

    while (1) {
        printf("\n--- Single-Level Directory System ---\n");
        printf("1. Create File\n");
        printf("2. Delete File\n");
        printf("3. Search File\n");
        printf("4. Display Files\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createFile(); break;
            case 2: deleteFile(); break;
            case 3: searchFile(); break;
            case 4: displayFiles(); break;
            case 5: printf("Exiting program.\n"); return 0;
            default: printf("Invalid choice! Please try again.\n");
        }
    }
}
