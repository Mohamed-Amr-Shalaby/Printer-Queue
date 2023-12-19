#include <stdio.h>
#include <stdlib.h>

#define MAX_DOCUMENT_LENGTH 100
#define MAX_QUEUE_SIZE 10

// define the PrintJob structure here
typedef struct PrintJob 
{
    char document[MAX_DOCUMENT_LENGTH];
    struct PrintJob *next;
} PrintJob;

// define the PrinterQueue structure here
typedef struct 
{
    PrintJob *front, *rear;
    int count;
} PrinterQueue;

// Initialize the printer queue to an empty state
void initializePrinterQueue(PrinterQueue *queue) 
{
    queue->front = queue->rear = NULL;
    queue->count = 0;
}

// Check if the printer queue is empty
int isEmpty(PrinterQueue *queue) 
{
    return queue->count == 0;
}

// Check if the printer queue is full
int isFull(PrinterQueue *queue) 
{
    return queue->count == MAX_QUEUE_SIZE;
}

// Add a new print job to the printer queue
void submitPrintJob(PrinterQueue *queue, char *document) 
{
    // Check if the queue is full
    if (!isFull(queue)) 
    {
        PrintJob *newJob = (PrintJob *)malloc(sizeof(PrintJob));
        // Check if memory allocation failed
        if (newJob == NULL) 
        {
            printf("Memory allocation failed. Cannot submit print job.\n");
            return;
        }

        // Copy the document name into the new print job
        strcpy(newJob->document, document);
        newJob->next = NULL;

        // Add the new print job to the queue
        // If the queue is empty, the new job is both the front and rear
        if (isEmpty(queue)) 
        {
            queue->front = queue->rear = newJob;
        }
        // Otherwise, add the new job to the rear of the queue 
        else 
        {
            queue->rear->next = newJob;
            queue->rear = newJob;
        }
        // Increment the number of print jobs in the queue
        queue->count++;

        printf("Print job submitted to the printer queue: %s\n", document);
    } 
    else 
    {
        printf("The printer queue is full. Cannot submit more print jobs!\n");
    }
}

void processPrintJob(PrinterQueue *queue) 
{
    if (!isEmpty(queue)) 
    {
        PrintJob *jobToRemove = queue->front;

        printf("Printing: %s\n", jobToRemove->document);

        queue->front = jobToRemove->next;
        free(jobToRemove);

        if (queue->front == NULL) 
        {
            queue->rear = NULL;
        }

        queue->count--;
    } 
    else 
    {
        printf("The printer queue is empty. No print jobs to process!\n");
    }
}

int main() 
{
    //initialize the printer queue
    PrinterQueue printerQueue;
    initializePrinterQueue(&printerQueue);
    
    int choice;
    char *document = (char *)malloc(MAX_DOCUMENT_LENGTH * sizeof(char));

    // Check if memory allocation failed
    if (document == NULL) 
    {
        printf("Memory allocation failed. Exiting.\n");
        return 1;  // Return a non-zero value to indicate an error
    }
    
    // Loop until the user chooses to exit
    while (1) 
    {
        printf("\n Printer Queue \n");
        printf("1. Submit a print job\n");
        printf("2. Process print job\n");
        printf("3. Exit\n");

        printf("Enter your choice (1/2/3): ");
        scanf("%d", &choice);

        switch (choice) 
        {
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
