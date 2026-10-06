
#include <stdio.h>
#include <string.h>

char str[100];
int i =0,error =0;

void T()
{
    if(str[i] =='a')
    {
        i++;
        
    }
    else
    {
        error=1;
    }
}

void X()
{
    if(str[i] == '+')
    {
        i++;
        T();X();
    }
}

void E()
{
    T();
    X();
}

int main()
{
    printf("Enter the string:\n");
    scanf("%s",str);
    E();
    if(str[i] == '\0' && error ==0)
    {
        printf("Accepted\n");
    }
    else
    {
        printf("Rejected\n");
    }
    return 0;
}

/*
E -> TX
T -> a
X -> +TX | epsilon
*/

