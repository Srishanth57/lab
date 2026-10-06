#include <stdio.h>
#include <ctype.h>
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

/* mode 0 = Three Address Code, 1 = Quadruple, 2 = Triple */
void generate(char *postfix, int mode) {
    char s[MAX], a[4], b[4];
    int t = -1, n = (mode == 2) ? 0 : 1;
    const char *tmp = (mode == 2) ? "(%c)" : "t%c";
    if (mode == 1) printf("\nOp\tArg1\tArg2\tResult");
    if (mode == 2) printf("\n\tOp\tArg1\tArg2");
    for (char *p = postfix; *p; p++) {
        if (isalpha(*p)) { s[++t] = *p; continue; }
        char r = s[t--], l = s[t--];
        sprintf(b, isdigit(r) ? tmp : "%c", r);
        sprintf(a, isdigit(l) ? tmp : "%c", l);
        if (mode == 0) printf("\nt%d=%s%c%s", n, a, *p, b);
        else if (mode == 1) printf("\n%c\t%s\t%s\tt%d", *p, a, b, n);
        else printf("\n(%d)\t%c\t%s\t%s", n, *p, a, b);
        s[++t] = n++ + '0';
    }
}

int main() {
    char infix[MAX], postfix[MAX];
    printf("Enter infix expression: ");
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);
    printf("Three Address Code : "); generate(postfix, 0);
    printf("\nQuadraple : ");        generate(postfix, 1);
    printf("\nTriple : ");           generate(postfix, 2);
    printf("\n");
    return 0;
}
