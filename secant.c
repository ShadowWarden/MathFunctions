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
	double tol=atof(argv[1]);
	double xnew, x=0, xold=1;
	int flag = 0;
	do{
		xnew = x-(f(x)*(x-xold))/(f(x)-f(xold));
		xold = x;
		x = xnew;
		flag ++;
		printf("%d : %f : %f\n",flag,x,(x-xold)/xold);
	}while(fabs((x-xold)/xold) > tol);
	return 0;
}

double f(double x){
	return x+pow(E,x);
}

double fp(double x){
	return 1+pow(E,x);
}
