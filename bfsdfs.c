#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Queue data structure for BFS
struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};

struct Queue* createQueue(unsigned capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

int isQueueEmpty(struct Queue* queue) {
    return (queue->size == 0);
}

void enqueue(struct Queue* queue, int item) {
    if (isQueueEmpty(queue))
        queue->front = 0;
    
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size += 1;
}

int dequeue(struct Queue* queue) {
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size -= 1;
    return item;
}

// Stack data structure for DFS
struct Stack {
    int top;
    unsigned capacity;
    int* array;
};

struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isStackEmpty(struct Stack* stack) {
    return (stack->top == -1);
}

void push(struct Stack* stack, int item) {
    stack->array[++stack->top] = item;
}

int pop(struct Stack* stack) {
    return stack->array[stack->top--];
}

// Function prototypes
void bfsAdjMatrix(int graph[MAX][MAX], int vertices, int start);
void dfsAdjMatrix(int graph[MAX][MAX], int vertices, int start);
void bfsAdjList(int** adjList, int vertices, int start);
void dfsAdjList(int** adjList, int vertices, int start);

int main() {
    int vertices = 6; // Number of vertices
    int edges = 7;    // Number of edges
    int start = 0;     // Starting vertex

    // Sample graph using adjacency matrix
    int graph[MAX][MAX] = {
        {0, 1, 1, 0, 0, 0},
        {1, 0, 0, 1, 1, 0},
        {1, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 1, 0},
        {0, 1, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 0}
    };

    // Sample graph using adjacency list
    int** adjList = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        adjList[i] = (int*)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++) {
            adjList[i][j] = 0;
        }
    }

    // Populate adjacency list
    int edgesList[][2] = {
        {0, 1}, {0, 2},
        {1, 3}, {1, 4},
        {2, 5},
        {3, 4}
    };

    for (int i = 0; i < edges; i++) {
        int u = edgesList[i][0];
        int v = edgesList[i][1];
        adjList[u][v] = 1;
        adjList[v][u] = 1; // For undirected graph
    }

    // Perform BFS and DFS traversals
    printf("BFS Traversal using Adjacency Matrix: ");
    bfsAdjMatrix(graph, vertices, start);
    
    printf("\nDFS Traversal using Adjacency Matrix: ");
    dfsAdjMatrix(graph, vertices, start);

    printf("\nBFS Traversal using Adjacency List: ");
    bfsAdjList(adjList, vertices, start);

    printf("\nDFS Traversal using Adjacency List: ");
    dfsAdjList(adjList, vertices, start);

    // Free allocated memory
    for (int i = 0; i < vertices; i++) {
        free(adjList[i]);
    }
    free(adjList);

    return 0;
}

void bfsAdjMatrix(int graph[MAX][MAX], int vertices, int start) {
    struct Queue* queue = createQueue(vertices);
    int visited[MAX] = {0};

    enqueue(queue, start);
    visited[start] = 1;

    while (!isQueueEmpty(queue)) {
        int current = dequeue(queue);
        printf("%d ", current);

        for (int i = 0; i < vertices; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                enqueue(queue, i);
                visited[i] = 1;
            }
        }
    }

    printf("\n");
}

void dfsAdjMatrix(int graph[MAX][MAX], int vertices, int start) {
    struct Stack* stack = createStack(vertices);
    int visited[MAX] = {0};

    push(stack, start);

    while (!isStackEmpty(stack)) {
        int current = pop(stack);

        if (!visited[current]) {
            printf("%d ", current);
            visited[current] = 1;
        }

        for (int i = vertices - 1; i >= 0; i--) {
            if (graph[current][i] == 1 && !visited[i]) {
                push(stack, i);
            }
        }
    }

    printf("\n");
}

void bfsAdjList(int** adjList, int vertices, int start) {
    struct Queue* queue = createQueue(vertices);
    int visited[MAX] = {0};

    enqueue(queue, start);
    visited[start] = 1;

    while (!isQueueEmpty(queue)) {
        int current = dequeue(queue);
        printf("%d ", current);

        for (int i = 0; i < vertices; i++) {
            if (adjList[current][i] == 1 && !visited[i]) {
                enqueue(queue, i);
                visited[i] = 1;
            }
        }
    }

    printf("\n");
}

void dfsAdjList(int** adjList, int vertices, int start) {
    struct Stack* stack = createStack(vertices);
    int visited[MAX] = {0};

    push(stack, start);

    while (!isStackEmpty(stack)) {
        int current = pop(stack);

        if (!visited[current]) {
            printf("%d ", current);
            visited[current] = 1;
        }

        for (int i = vertices - 1; i >= 0; i--) {
            if (adjList[current][i] == 1 && !visited[i]) {
                push(stack, i);
            }
        }
    }

    printf("\n");
}
