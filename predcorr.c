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
 
double moul3s(double(*f)(double,double), double dt,double unew,double *u,int i, double x){
//	printf("%g\t%g\t%g\t%g\n",dt,t,u1,u2
//	printf("%g\t%g\n",sol[0],sol[1]);
	return u[i-1]+dt/24.0*(9*f(x+dt,unew)+19*f(x,u[i-1])-5*f(x-dt,u[i-2])+f(x-2*dt,u[i-3]));
}

double bash4s(double(*f)(double,double), double dt,double *u,int i, double x){
//      printf("%g\t%g\t%g\t%g\n",dt,t,u1,u2
//      printf("%g\t%g\n",sol[0],sol[1]);
        return u[i-1]+dt/24.0*(55*f(x,u[i-1])-59*f(x-dt,u[i-2])+37*f(x-2*dt,u[i-3])-9*f(x-3*dt,u[i-4]));
}

 
double f(double x,double y){
	return y+x;
}
 
int main(int argc, char ** argv){
	double *u, x, y1;
	double x0 = 0, x1 = 1, dx = atof(argv[1]);
	int i, n = 1 + (x1 - x0)/dx;
	u = malloc(sizeof(double) * n);
	u[0]=x0*x0/2; u[1] = pow(x0+dx,2)/2; u[2] = pow(x0+2*dx,2)/2; u[3] = pow(x0+3*dx,2)/2; 
	for (i = 4; i < n; i++){
		double unew = bash4s(f, dx, u,i,x0+dx*(i-1));
		u[i] = moul3s(f,dx,unew,u,i,x0+dx*(i-1));
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
