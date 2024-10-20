#include <stdio.h>
#include <stdlib.h>

void hanoi(int n, char from, char tmp, char to){
    if(n==1){
        printf("%d : %c -> %c\n", n, from, to);
    }
    else{
        hanoi(n-1, from, to, tmp);
        printf("%d : %c -> %c\n", n, from, to);
        hanoi(n-1, tmp, from, to);
    }
}



int main() {

    hanoi(6, 'A', 'B', 'C');

    return 0;
}