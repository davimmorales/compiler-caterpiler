#include "stdio.h"

void sort(int num[], int tam){
    int i;
    int j;
    int min;
    int aux;
    i = 0;
    while (i < tam-1){
        min = i;
        j = i + 1;
        while (j < tam){
            if(num[j] < num[min])
                min = j;
            j = j + 1;
        }
        if (i != min){
            aux = num[i];
            num[i] = num[min];
            num[min] = aux;
        }
        i = i + 1;
    }
}
int main(){
    int vetor[4];
    int i;
    vetor[0] = 9;
    vetor[1] = 6;
    vetor[2] = 8;
    vetor[3] = 7;
    sort(vetor, 4);
    scanf("%d", &i);
    printf("%d\n", vetor[i]);
    return 0;
}

