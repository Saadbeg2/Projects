#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

// Function to check if the character is an opening bracket
int isOpeningBracket(char c) {
    return c == '(' || c == '[' || c == '{';
}

// Function to check if the character is a closing bracket
int isClosingBracket(char c) {
    return c == ')' || c == ']' || c == '}';
}

// Function to check if the brackets match
int isMatchingPair(char opening, char closing) {
    return (opening == '(' && closing == ')') ||
           (opening == '[' && closing == ']') ||
           (opening == '{' && closing == '}');
}

// Function to check the order of brackets
int followsBracketOrder(const char *line) {
    int len = strlen(line);
    char *stack = (char *)malloc(len);
    int top = -1;

    for (int i = 0; i < len; i++) {
        char c = line[i];
        if (isOpeningBracket(c)) {
            stack[++top] = c;
        } else if (isClosingBracket(c)) {
            if (top == -1 || !isMatchingPair(stack[top--], c)) {
                free(stack);
                return 0;
            }
        }
    }

    int isValid = (top == -1);
    free(stack);
    return isValid;
}

// Function to check if brackets are valid
int areBracketsValid(const char *line) {
    if (followsBracketOrder(line)) {
        int len = strlen(line);
        char *stack = (char *)malloc(len);
        int top = -1;

        for (int i = 0; i < len; i++) {
            char c = line[i];
            if (isOpeningBracket(c)) {
                stack[++top] = c;
            } else if (isClosingBracket(c)) {
                if (top == -1 || !isMatchingPair(stack[top--], c)) {
                    free(stack);
                    return 0;
                }
            }
        }

        int isValid = (top == -1);
        free(stack);
        return isValid;
    } else {
        return 0;
    }
}

int main() {
    char line[MAX_LENGTH];
    char *validLines[MAX_LENGTH];
    char *invalidLines[MAX_LENGTH];
    int validCount = 0;
    int invalidCount = 0;

    printf("Enter your input strings (type 'END' to finish):\n");
    while (1) {
        fgets(line, MAX_LENGTH, stdin);
        line[strcspn(line, "\n")] = 0; // Remove newline character

        if (strcmp(line, "END") == 0) {
            break;
        }

        if (areBracketsValid(line)) {
            validLines[validCount] = strdup(line);
            validCount++;
        } else {
            invalidLines[invalidCount] = strdup(line);
            invalidCount++;
        }
    }

    if (invalidCount > 0) {
        printf("Invalid\n");
        for (int i = 0; i < invalidCount; i++) {
            printf("%s\n", invalidLines[i]);
            free(invalidLines[i]);
        }
    }

    if (validCount > 0) {
        printf("Valid\n");
        for (int i = 0; i < validCount; i++) {
            printf("%s\n", validLines[i]);
            free(validLines[i]);
        }
    }

    return 0;
}
