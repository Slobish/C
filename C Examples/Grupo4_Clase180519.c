#include <stdio.h>
#include <stdlib.h>

unsigned int potencias(unsigned int x,unsigned int y);
unsigned int factorial(int y);
unsigned int decimal(float y);
void fibonacci(float y);

int main()
{
    unsigned int resultado=0;
    unsigned int n0 =0;
    unsigned int n1 =0;
    int n2 =0;
    int aux =0;
    float n3 =0;
    float n4 =0;

    while(1){
    printf("Menu. Elija funcion:\n");
    printf("1. Potencia.\n");
    printf("2. Factorial.\n");
    printf("3. Binario.\n");
    printf("4. Fibonacci.\n\n\n\n\n\n");
    printf("0. Salir.\n");
    scanf("%d",&aux);
        switch(aux){
            case 0:
                return 0;
            case 1:
                printf("X a la Y. Ingrese numero 1.\n");
                scanf("%d",&n1);
                printf("X a la Y. Ingrese numero 2.\n");
                scanf("%d",&n2);
                resultado = potencias(n1,n2);
                printf("%d\n",resultado);
                n1=0;
                n2=0;
                resultado=0;                
            break;
            case 2:
                resultado=3;
                while(resultado==3){
                    printf("Factorial. Ingrese numero.\n");
                    scanf("%d",&n2);
                    resultado = factorial(n2);
                }
                printf("%d\n",resultado);
                n2=0;
                resultado=0;                
                break;
            case 3:
                printf("Decimal. Ingrese numero.\n");
                scanf("%f",&n3);
                resultado=decimal(n3);               
                n3=0;
                resultado=0;                
            break;
            case 4:
                printf("Fibonacci. Ingrese numero.\n");
                scanf("%f",&n4);
                fibonacci(n4);
                resultado=0;
                n4=0;            
            break;
        }
    }

}

unsigned int potencias(unsigned int x,unsigned int y){
    unsigned xi = x;
    for(y;y>1;y--){
        x=x*xi;
    }
    return x;
}

unsigned int factorial(int y){
    if(y<0){
        printf("Error, ingrese de nuevo.\n");
        return 3;
    }
    unsigned int i=0;
    for(i=y-1;i>1;i--){
        y=(y*i);
    }
    return y;
}

unsigned int decimal(float y){
    unsigned int i=(int)y;
    while(i!=0){
        if((i%2)==0){
            printf("0");
        }else{
            printf("1");
        }
        i=i/2;
    }
    return i;
}

void fibonacci(float y){
    unsigned int i=(int)y;
    unsigned int aux1=0;
    unsigned int aux2=1;
    printf("%d\n",aux1);
    printf("%d\n",aux2);
    while(i>aux2){
        aux1=aux1+aux2;
        aux2=aux1+aux2;
        if(i>aux1){
            printf("%d\n",aux1);
        }
        if(i>aux2){
            printf("%d\n",aux2);    
       }
    }
}