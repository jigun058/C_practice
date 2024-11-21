#include<stdio.h>

int x, y;

void g(void){
	x = x + 1;
	y = x + 1;
}

void f(void){
	int x;
	y = y + 1;
	x = y + 1;
	g();
}

int main(){
	x = 1;
	y = 2;
	f();
	g();
	
	printf("x = %d, y = %d \n", x, y);

    return 0;
}