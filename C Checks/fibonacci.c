#include "stdio.h"

int fibonacci(int n){
    int c;
    int next;
    int first;
    int second;
    first = 0;
    second = 1;
    c = 0;
    while(c <= n){
        if(c <= 1){
            next = c;
	}
        else{
            next = first + second;
            first = second;
            second = next; /* Estava second = first */
        }
        c = c + 1;
	printf("%d\n", c);
    }
    return next;
}

int main(){
  int n;
  n = 9;
  printf("%d\n", fibonacci(n));
  return 0;
}
