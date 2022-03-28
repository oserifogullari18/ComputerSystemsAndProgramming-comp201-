#include <stdio.h>
#include "io.h"

int ask_number(){
	int num;
	printf("Please enter an integer between 0-10: ");
	scanf("%d",&num);
	return num;
}

void print_result(int result){
	printf("f(x) = %d", result);
}
