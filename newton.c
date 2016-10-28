/* newton.c
*  Omkar H. Ramachandran
*  University of Colorado - Boulder
*
*  Newton Raphson method
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define E 2.718281828459045

double f(double);
double fp(double);

int main(int argc, char ** argv){
	double tol=atof(argv[2]);
	double x=atof(argv[1]), xold;
	int flag = 0;
	do{
		xold = x;
		x = xold-f(xold)/fp(xold);
		flag ++;
		printf("%d : %f : %f\n",flag,x,(sqrt(0.5)-x)/sqrt(0.5));
	}while(flag == 1 || fabs((x-xold)/xold) > tol);
	return 0;
}

double f(double x){
//	int A = 135000;
//	int n = 30*12;
//	int P = 1000;
	return x*x-0.5;
}

double fp(double x){
//	int A = 135000;
//	int n = 30*12;
//	int P = 1000;
	return 2*x;
}
