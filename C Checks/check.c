#include "stdio.h"

int vetor[2];

int foo(int x, int y, int z, int w){
    int result;
    result = 0;
    while(result >= 0){
        if(x < 2)
            result = x + y;
        if(y > 2)
            result = result + y + z;
        else
            result = result * 3;
        if(w <= 4){
            if(z == 0)
                return 0;
            if(result != 0)
                return result/(w - 1);
        }
    }
}
int main(){
    vetor[0] = 7;
    vetor[1] = foo(1, vetor[0], 3, 4);
    printf("%d\n", vetor[1]);
    return 0;
}



