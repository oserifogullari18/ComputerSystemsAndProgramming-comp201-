#include <stdlib.h>
#include "f.h"

int calculate_f(int x){
	int i ;
	int f =1;
	for(i = x;i>0;i--){
		f = f*i;
	}
	f--;
	return f;
}
