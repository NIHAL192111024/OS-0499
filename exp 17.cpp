#include <stdio.h>
#include <stdbool.h>

#define MAX 10
#define RESOURCES 3

int allocation[MAX][RESOURCES], max[MAX][RESOURCES], need[MAX][RESOURCES];
int available[RESOURCES], safeSequence[MAX], processCount, resourceCount;

bool isSafe() {
    int work[RESOURCES];
    bool finish[MAX] = {0};
    int count = 0;

    for (int i = 0; i < RESOURCES; i++)
        work[i] = available[i];

    while (count < processCount) {
        bool found = false;
        for (int p = 0; p < processCount; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < resourceCount; j++)
                    if (need[p][j] > work[j])
                        break;

                if (j == resourceCount) {
                    for (int k = 0; k < resourceCount; k++)
                        work[k] += allocation[p][k];
                    safeSequence[count++] = p;
                    finish[p] = 1;
                    found = true;
                }
            }
        }
        if (!found)
            return false;
    }
    return true;
}

void requestResources(int processID, int request[]) {
    for (int i = 0; i < resourceCount; i++) {
        if (request[i] > need[processID][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return;
        }
    }

    for (int i = 0; i < resourceCount; i++) {
        if (request[i] > available[i]) {
            printf("Process is waiting, resources not available.\n");
            return;
        }
    }

    for (int i = 0; i < resourceCount; i++) {
        available[i] -= request[i];
        allocation[processID][i] += request[i];
        need[processID][i] -= request[i];
    }

    if (isSafe()) {
        printf("Resources allocated successfully.\n");
    } else {
        for (int i = 0; i < resourceCount; i++) {
            available[i] += request[i];
            allocation[processID][i] -= request[i];
            need[processID][i] += request[i];
        }
        printf("Resources allocation leads to unsafe state. Reverting.\n");
    }
}

int main() {
    processCount = 5; // Number of processes
    resourceCount = RESOURCES; // Number of resources

    // Example initialization
    int initialAvailable[RESOURCES] = {3, 2, 2};
    for (int i = 0; i < resourceCount; i++)
        available[i] = initialAvailable[i];

    // Example allocation and max matrices
    int exampleAllocation[MAX][RESOURCES] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int exampleMax[MAX][RESOURCES] = {
        {0, 1, 0},
        {2, 2, 2},
        {3, 0, 2},
        {2, 2, 2},
        {0, 6, 5}
    };

    for (int i = 0; i < processCount; i++) {
        for (int j = 0; j < resourceCount; j++) {
            allocation[i][j] = exampleAllocation[i][j];
            max[i][j] = exampleMax[i][j];
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Request resources for process 1
    int request[RESOURCES] = {1, 0, 2};
    requestResources(1, request);

    return 0;
}
