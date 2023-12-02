#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100


typedef struct {
    char data[MAX_SIZE];
    int top;
} Stack;

void initialize(Stack* stack) {
    stack->top = -1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, char value) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    stack->data[++stack->top] = value;
}

char pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top--];
}

char peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top];
}


int isOperand(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}


int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}


int getPrecedence(char ch) {
    if (ch == '+' || ch == '-')
        return 1;
    else if (ch == '*' || ch == '/')
        return 2;
    else
        return 0;  
}


void infixToPostfix(char infix[], char postfix[]) {
    Stack stack;
    initialize(&stack);
    int i = 0, j = 0;

    while (infix[i] != '\0') {
        if (isOperand(infix[i])) {
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {
            push(&stack, infix[i]);
        } else if (infix[i] == ')') {
            while (!isEmpty(&stack) && peek(&stack) != '(') {
                postfix[j++] = pop(&stack);
            }
            if (!isEmpty(&stack) && peek(&stack) != '(') {
                printf("Invalid expression\n");
                exit(EXIT_FAILURE);
            } else {
                pop(&stack);  
            }
        } else if (isOperator(infix[i])) {
            while (!isEmpty(&stack) && getPrecedence(peek(&stack)) >= getPrecedence(infix[i])) {
                postfix[j++] = pop(&stack);
            }
            push(&stack, infix[i]);
        }
        i++;
    }

    while (!isEmpty(&stack)) {
        postfix[j++] = pop(&stack);
    }

    postfix[j] = '\0';
}


void infixToPrefix(char infix[], char prefix[]) {
 
    int len = strlen(infix);
    char reversedInfix[MAX_SIZE];
    for (int i = 0; i < len; i++) {
        reversedInfix[i] = infix[len - i - 1];
    }
    reversedInfix[len] = '\0';


    char reversedPostfix[MAX_SIZE];
    infixToPostfix(reversedInfix, reversedPostfix);

    
    int j = 0;
    for (int i = strlen(reversedPostfix) - 1; i >= 0; i--) {
        prefix[j++] = reversedPostfix[i];
    }
    prefix[j] = '\0';
}


int evaluatePostfix(char postfix[]) {
    Stack stack;
    initialize(&stack);
    int i = 0;

    while (postfix[i] != '\0') {
        if (isOperand(postfix[i])) {
            push(&stack, postfix[i] - '0');
        } else if (isOperator(postfix[i])) {
            int operand2 = pop(&stack);
            int operand1 = pop(&stack);
            switch (postfix[i]) {
                case '+':
                    push(&stack, operand1 + operand2);
                    break;
                case '-':
                    push(&stack, operand1 - operand2);
                    break;
                case '*':
                    push(&stack, operand1 * operand2);
                    break;
                case '/':
                    push(&stack, operand1 / operand2);
                    break;
            }
        }
        i++;
    }

    return pop(&stack);
}

int main() {
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];
    char prefix[MAX_SIZE];

    printf("Enter infix expression: ");
    scanf("%s", infix);

   
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    
    infixToPrefix(infix, prefix);
    printf("Prefix expression: %s\n", prefix);

    
    int result = evaluatePostfix(postfix);
    printf("Result of postfix expression: %d\n", result);

    return 0;
}
