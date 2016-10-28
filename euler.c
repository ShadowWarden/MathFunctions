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
 
double euler(double(*f)(double,double), double dt,double u, double x){
//	printf("%g\t%g\t%g\t%g\n",dt,t,u1,u2
//	printf("%g\t%g\n",sol[0],sol[1]);
	return u+dt*f(x,u);
}
 
double f(double x,double y){
	return y+x;
}
 
int main(int argc, char ** argv){
	double *u, x, y1;
	double x0 = 0, x1 = 1, dx = atof(argv[1]);
	int i, n = 1 + (x1 - x0)/dx;
	u = malloc(sizeof(double) * n);
 
	for (u[0] = 0, i = 1; i < n; i++){
		u[i] = euler(f, dx, u[i-1],x0+dx*(i-1));
	}
	printf("t\tu\trel. err.\n-----------------\n");
	for (i = 0; i < n; i ++) {
		x = x0 + dx * i;
		y1 = pow(E, x)-x-1;
		printf("%g\t%g\t%g\n", x, u[i], (y1-u[i])/y1);
	}
 
	free(u);
	return 0;
}
