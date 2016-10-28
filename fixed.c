/* fixed.c
*  Omkar H. Ramachandran
*  University of Colorado - Boulder
*
*  Fixed point iteration method
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define E 2.718281828459045
#define pi 3.141592653589793

double f(double);

int main(int argc, char ** argv){
	double tol=atof(argv[1]);
	double x=atof(argv[2]), xold;
	int flag = 0;
	do{
		xold = x;
		x = f(xold);
		flag ++;
		printf("%d %f\n",flag,x);
//		char junk;
//		scanf("%c",&junk);
	}while(fabs((x-xold)/xold) > pow(10,-tol));
	return 0;
}

double f(double x){
	return (pow(x,2)-3)/2;
}

double fp(double x){
	return x;
}
