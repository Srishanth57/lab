#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX 100
char stack[MAX];
int top = -1;

void push(char ch) { stack[++top] = ch; }
char pop() { return stack[top--]; }

int priority(char ch) {
    return ch == '^' ? 3 : (ch == '*' || ch == '/') ? 2 : (ch == '+' || ch == '-') ? 1 : 0;
}

void infixToPostfix(char *infix, char *postfix) {
    int j = 0;
    for (char *p = infix; *p; p++) {
        if (isalnum(*p)) postfix[j++] = *p;
        else if (*p == '(') push(*p);
        else if (*p == ')') {
            while (top != -1 && stack[top] != '(') postfix[j++] = pop();
            pop();
        } else {
            while (top != -1 && stack[top] != '(' && priority(stack[top]) >= priority(*p))
                postfix[j++] = pop();
            push(*p);
        }
    }
    while (top != -1) postfix[j++] = pop();
    postfix[j] = '\0';
}

void CG(char *postfix, int addr) {
    const char *ops = "+-*/", *names[] = {"ADD", "SUB", "MUL", "DIV"};
    printf("\nAddr\tInstruction\n");
    for (char *p = postfix; *p; p++) {
        if (isalpha(*p)) {
            printf("%d\tMOV A,%c\n%d\tPUSH A\n", addr, *p, addr + 1);
            addr += 2;
        } else if (strchr(ops, *p)) {
            printf("%d\tPOP B\n%d\tPOP A\n%d\t%s B\n%d\tPUSH A\n",
                   addr, addr + 1, addr + 2, names[strchr(ops, *p) - ops], addr + 3);
            addr += 4;
        }
    }
    printf("%d\tPOP A\n%d\tHLT\n", addr, addr + 1);
}

int main() {
    char infix[MAX], postfix[MAX];
    int addr;
    printf("Enter infix expression: ");
    scanf("%s", infix);
    printf("Enter the starting address : ");
    scanf("%d", &addr);
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);
    CG(postfix, addr);
    return 0;
}
