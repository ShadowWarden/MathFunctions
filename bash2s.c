/* euler.c
*  Omkar H. Ramachandran
*
*
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define E 2.718281828459045
 
double bash2s(double(*f)(double,double), double dt,double u,double um, double x){
//	printf("%g\t%g\t%g\t%g\n",dt,t,u1,u2
//	printf("%g\t%g\n",sol[0],sol[1]);
	return u+dt/2.0*(3*f(x,u)-f(x-dt,um));
}
 
double f(double x,double y){
	return y+x;
}
 
int main(int argc, char ** argv){
	double *u, x, y1;
	double x0 = 0, x1 = 0.5, dx = 0.1;
	int i, n = 1 + (x1 - x0)/dx;
	u = malloc(sizeof(double) * n);
 
	for (u[0] = 0, i = 1; i < n; i++){
		u[i] = bash2s(f, dx, u[i-1],u[i-2],x0+dx*(i-1));
	}
	printf("t\tu\trel. err.\n-----------------\n");
	for (i = 0; i < n; i ++) {
		x = x0 + dx * i;
		y1 = pow(E, x)-x-1;
		printf("%g\t%g\t%g\n", x, u[i], y1);
	}
 
	free(u);
	return 0;
}
