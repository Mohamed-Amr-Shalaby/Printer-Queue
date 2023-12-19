#include <stdio.h>
#include <stdlib.h>

#define MAX_DOCUMENT_LENGTH 100
#define MAX_QUEUE_SIZE 10

typedef struct PrintJob {
    char document[MAX_DOCUMENT_LENGTH];
    struct PrintJob *next;
} PrintJob;

typedef struct {
    PrintJob *front, *rear;
    int count;
} PrinterQueue;

void initializePrinterQueue(PrinterQueue *queue) {
    queue->front = queue->rear = NULL;
    queue->count = 0;
}

int isEmpty(PrinterQueue *queue) {
    return queue->count == 0;
}

int isFull(PrinterQueue *queue) {
    return queue->count == MAX_QUEUE_SIZE;
}

void submitPrintJob(PrinterQueue *queue, char *document) {
    if (!isFull(queue)) {
        PrintJob *newJob = (PrintJob *)malloc(sizeof(PrintJob));
        if (newJob == NULL) {
            printf("Memory allocation failed. Cannot submit print job.\n");
            return;
        }

        snprintf(newJob->document, MAX_DOCUMENT_LENGTH, "%s", document);
        newJob->next = NULL;

        if (isEmpty(queue)) {
            queue->front = queue->rear = newJob;
        } else {
            queue->rear->next = newJob;
            queue->rear = newJob;
        }

        queue->count++;

        printf("Print job submitted to the printer queue: %s\n", document);
    } else {
        printf("The printer queue is full. Cannot submit more print jobs!\n");
    }
}

void processPrintJob(PrinterQueue *queue) {
    if (!isEmpty(queue)) {
        PrintJob *jobToRemove = queue->front;

        printf("Printing: %s\n", jobToRemove->document);

        queue->front = jobToRemove->next;
        free(jobToRemove);

        if (queue->front == NULL) {
            queue->rear = NULL;
        }

        queue->count--;
    } else {
        printf("The printer queue is empty. No print jobs to process!\n");
    }
}

int main() {
    PrinterQueue printerQueue;
    initializePrinterQueue(&printerQueue);

    int choice;
    char *document = (char *)malloc(MAX_DOCUMENT_LENGTH * sizeof(char));

    if (document == NULL) {
        printf("Memory allocation failed. Exiting.\n");
        return 1;  // Return a non-zero value to indicate an error
    }

    while (1) {
        printf("\n Printer Queue \n");
        printf("1. Submit a print job\n");
        printf("2. Process print job\n");
        printf("3. Exit\n");

        printf("Enter your choice (1/2/3): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the document name: ");
                scanf("%s", document);
                submitPrintJob(&printerQueue, document);
                break;
            case 2:
                processPrintJob(&printerQueue);
                break;
            case 3:
                printf("Exiting the Printer Queue. Goodbye!\n");
                free(document);  // Free the allocated memory before exiting
                return 0;
            default:
                printf("Invalid choice. Please enter 1, 2, or 3.\n");
        }
    }

    // This point is reached only if the user enters an invalid choice
    free(document);
    return 0;
}
