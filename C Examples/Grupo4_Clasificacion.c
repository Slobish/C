#include <stdio.h>
#include <stdlib.h>

#define N 3 //Cantida de personas
int clasificarBMI(float *BMI,int Size);
float keyboardInput(int x);

void main(void)
{
    float BMI[N]={keyboardInput(1),keyboardInput(2),keyboardInput(3)};
    
    clasificarBMI(BMI,N);

    
}

int clasificarBMI(float *BMI , int size)
{
    int indexer=0;
    int Size=--size;
    for(indexer=Size;indexer>=0;indexer--)
    {
        if(BMI[indexer]>=30) printf("Detectado un BMI de %f clasificado como obesidad\n",BMI[indexer]);
        else if(BMI[indexer]>=25 && BMI[indexer]<30) printf("Detectado un BMI de %f clasificado como sobrepeso\n",BMI[indexer]);
            else if(BMI[indexer]>=18.5 && BMI[indexer]<25) printf("Detectado un BMI de %f clasificado como normal\n",BMI[indexer]);
                else if(BMI[indexer]<18.5) printf("Detectado un BMI de %f clasificado como desnutricion\n",BMI[indexer]);
    }
    return size;
}

float keyboardInput(int x)
{
    float a;
    printf("Ingrese el %d°BMI : ",x);    
    scanf("%f",&a);    
    return a;
}