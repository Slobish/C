#include <stdio.h>
#include <stdlib.h>

#define N 3 //Cantida de personas
int Calculo_BMI(float *Weight,float *Height,float *BMI, int Size);
float keyboardInput(int x,int y);

void main(void)
{
    int indexer=0;
    float Weight[N]={keyboardInput(1,1),keyboardInput(1,2),keyboardInput(1,3)};
    float Height[N]={keyboardInput(2,1),keyboardInput(2,2),keyboardInput(2,3)};
    float BMI[N];
    for(indexer=Calculo_BMI(Weight,Height,BMI,N);indexer>=0;indexer--) 
    {
        printf("El IBM de la %d° persona es %.2f \n",indexer+1,BMI[indexer]);   
    }
    printf("indexer %d",indexer);
}

int Calculo_BMI(float *Weight,float *Height,float *BMI ,int size){
    int Size=--size;
    while (Size >= 0)
    {
        *(BMI+Size)=*(Weight+Size)/((*(Height+Size))*(*(Height+Size)));
        Size--;
    }
    return size;
}

float keyboardInput(int x,int y)
{
    float a;
    if(x==1){
        printf("Ingrese el peso de la %d° persona  : ",y);
        scanf("%f",&a);
    }else{
        printf("Ingrese la altura de la %d° persona en metros  : ",y);
        scanf("%f",&a);
    }
    return a;
}