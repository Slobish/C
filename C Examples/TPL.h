#include <stdio.h>
#include <stdlib.h>


#define VECTOR_LENGTH 100 

int compare(char input[],char check[]);
int getLength(char * text);
int filterWord(char * text);
int keyboardInput(int * p);
int getValuesIn(int *p);
void cleanVector(int * vector);


int getValuesIn(int * p)
{
    int k=0;
    int amount=0;
    int * number;
    
    while(keyboardInput(number)!=999)
    {
        p[k++]=*number;
        amount++;
    }
    return amount;
}

int getLength(char * text)
{
    int i=0,length=0;
    
    while(text[i++]!='\n') length++;
    return length;
}
int filterWord(char * text)
{
    char KEYWORD[]="FIN\n";    
    fgets(text,VECTOR_LENGTH,stdin);
    if (compare(text,KEYWORD)) return 1;
    else return 0;
}

void cleanVector(int * vector)
{
    int i;
    for (i=0;i<VECTOR_LENGTH;i++)
    {
        vector[i]=0;
    }
}

int keyboardInput(int * p)
{
    int a;
    scanf("%d",&a);
    while ((getchar()) != '\n'); //para flushear el buffer de entrada
    *p = a;
    return *p;
}

int compare(char input[],char check[])
{
    int i,result=1;
    for(i=0; input[i]!='\0' || check[i]!='\0'; i++)
    {
        if(input[i] != check[i]) {
            result=0;
            break;
        }
    }
    return result;
}