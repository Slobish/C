#include <stdio.h>
#include <stdlib.h>

#define N 3 //Cantida de personas
int maximoBMI(int *ID,float *BMI,int Size);
int minimoBMI(int *ID,float *BMI,int Size);
float keyboardInput(int x,int y);

void main(void)
{
    float BMI[N]={keyboardInput(1,1),keyboardInput(1,2),keyboardInput(1,3)};
    int ID[N]={keyboardInput(2,1),keyboardInput(2,2),keyboardInput(2,3)};
    maximoBMI(ID,BMI,N);
    minimoBMI(ID,BMI,N);
    
}
int minimoBMI(int *ID,float *BMI,int size)
{
    int Size=--size;
    float minBMI=BMI[0];
    int atID=ID[0];
    while (Size >= 0)
    {
        if(BMI[Size]<minBMI)
        {
            minBMI=BMI[Size];
            atID=ID[Size];
        }
       Size--;
    }
    printf("El paciente de id %d posee un BMI de %.2f, siendo este el minimo ingresado\n",atID,minBMI);
    return size;
}
int maximoBMI(int *ID,float *BMI,int size)
{
    int Size=--size;
    float maxBMI=0.0;
    int atID=0;
    while (Size >= 0)
    {
        if(BMI[Size]>maxBMI)
        {
            maxBMI=BMI[Size];
            atID=ID[Size];
        }
       Size--;
    }
    printf("El paciente de id %d posee un BMI de %.2f, siendo este el maximo ingresado\n",atID,maxBMI);
    return size;
}

float keyboardInput(int x,int y)
{
    float a;
    if(x==1)printf("Ingrese el BMI de la %d° persona: ",y);
    else printf("Ingrese el ID de la %d° persona: ",y);
    scanf("%f",&a);    
    return a;
}