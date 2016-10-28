/* fixed.c
*  Omkar H. Ramachandran
*  University of Colorado - Boulder
*
*  Bisection method
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define E 2.718281828459045

double f(double);

int main(int argc, char ** argv){
	double tol=atof(argv[1]);
	double a = atof(argv[2]);
	double b = atof(argv[3]);
	double xold, x=0;
	int flag = 0;
	do{
		xold = x;
		x = a - (b-a)*f(a)/(f(b)-f(a));
		if(f(x)<0){
			a = x; 
		}else if(f(x)>0){
			b = x;
		}
		flag ++;
		printf("%d : %f : %f\n",flag,x,(x-xold)/xold);
	}while(flag == 1 || fabs((x-xold)/xold) > tol);
	return 0;
}

double f(double x){
	return x+pow(E,x);
}
