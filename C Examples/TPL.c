#include "TPL.h"

void deployMenu(void);
void sort(void);
void myStrlen(void);
void calculate(void);

int main(void)
{
    
    int selection[1];
    
    unsigned char outcome=0;
    deployMenu();
    while(keyboardInput(selection)!=0)
    {
        
        switch(*selection)
        {
            case 0:
                exit(0);
                break;
            case 1:
                sort();
                break;
            case 2:
                calculate();
                break;
            case 3:
                myStrlen();
                break;
            default:
                printf("La seleccion '%d' no es una opcion valida \n",*selection);
                break;
        }
        deployMenu();        
    }
   return 0; 
}

void calculate(void)
{   
    char a;
    char b;
    
    char *p;
    char *q;
    
    char **r;
    char **k;
    char **s;
    
    a=9;
    b=4;
    
    printf("a=%d , b=%d , p=%p , q=%p , *p=%d *q=%d , r=%p ,s=%p ,*r=%p ,*s=%p , **r=%p , **s=%p",a,b,p,q,*p,*q,r,s,*r,*s,**r,**s);
    p=&a;
    q=&b;
    printf("a=%d , b=%d , p=%p , q=%p , *p=%d *q=%d , r=%p ,s=%p ,*r=%p ,*s=%p , **r=%p , **s=%p",a,b,p,q,*p,*q,r,s,*r,*s,**r,**s);
    r=&p;
    s=&q;
    printf("a=%d , b=%d , p=%p , q=%p , *p=%d *q=%d , r=%p ,s=%p ,*r=%p ,*s=%p , **r=%p , **s=%p",a,b,p,q,*p,*q,r,s,*r,*s,**r,**s);
    **r=*q;
    printf("a=%d , b=%d , p=%p , q=%p , *p=%d *q=%d , r=%p ,s=%p ,*r=%p ,*s=%p , **r=%p , **s=%p",a,b,p,q,*p,*q,r,s,*r,*s,**r,**s);
    
}

void myStrlen(void)
{
    printf("MyStrlen--- Insert some text ---\n");
    
    
    char text[VECTOR_LENGTH];
    int length=0,i=0,strings=0; // para no contar el FIN y el loop del FIN
    
    while(!filterWord(text))
    {       
        length+=getLength(text);
        strings++;
    }
    printf("Ingresó %d caracteres, en %d oportunidades \n",length,strings);
}


void sort(void)
{
    int i=0,aux1=0,aux2=0;
    int vector[VECTOR_LENGTH];
    int vectorOrdenado[VECTOR_LENGTH];
    int lastFactor=0;
    cleanVector(vectorOrdenado);

    printf("Sort function ---Insert up to %d values---\n",VECTOR_LENGTH);    
    i=getValuesIn(vector);

    for(aux2=0;aux2<i;aux2++)
    {
        for(aux1=0;aux1<i;aux1++)
        {
            if(vector[aux1]>vectorOrdenado[aux2]) 
            {
                vectorOrdenado[aux2]=vector[aux1];
                lastFactor=aux1;
            }
        }        
        vector[lastFactor]=0;
    }

    for(aux1=0;aux1<i;aux1++)printf("%d ",vectorOrdenado[aux1]);
    
}
void deployMenu(void)
{
    printf("Seleccione la funcion que desee ejecutar:\n -----------------------------\n");
    printf("0. Exit           1. Sort  \n");
    printf("2. Calculate      3. myStrlen\n");
}
