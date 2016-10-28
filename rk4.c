/* rk4.c
*  Omkar H. Ramachandran
*
*  4th Order Runge Kutta implementation for solving an ODE
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define E 2.718281828459045
 
double rk4(double(*f1)(double, double), double dt, double t, double u1){
//	printf("%g\t%g\t%g\t%g\n",dt,t,u1,u2);
	double	k11 = dt * f1(t, u1),
//		k12 = dt * f2(t, u1, u2),
		k21 = dt * f1(t + dt / 2, u1 + k11/2),
//		k22 = dt * f2(t + dt / 2, u1 + k11/2, u2 + k12/2),	
		k31 = dt * f1(t + dt / 2, u1 + k21/2),
//		k32 = dt * f2(t + dt / 2, u1 + k21/2, u2 + k22/2),	
		k41 = dt * f1(t + dt, u1 + k31);
//		k42 = dt * f2(t + dt, u1 + k31, u2 + k32);
//	double * sol = (double *) malloc (sizeof(double)*2); 
	double sol = u1 + (k11+2*k21+2*k31+k41)/6;
//	sol[1] = u2 + (k12+2*k22+2*k32+k42)/6;	
//	printf("%g\t%g\n",sol[0],sol[1]);
	return sol;
}
 
double u1p(double t, double u1){
	return t+u1;
}

double u2p(double t, double u1, double u2){
	return 4*u1 + u2 + (t*t+2*t-4)*pow(E,2*t);
}
 
int main(int argc, char ** argv){
	double *u1, *u2, x, y1, y2;
	double x0 = 0, x1 = 0.5, dx = 0.1;
	int i, n = 1 + (x1 - x0)/dx;
	u1 = malloc(sizeof(double) * n);
//	u2 = malloc(sizeof(double) * n);
 
	for (u1[0] = 0, i = 1; i < n; i++){
		double sol;
		sol = rk4(u1p, dx, x0 + dx * (i - 1), u1[i-1]);
 		u1[i] = sol;
//		u2[i] = sol[1];	
//		free(sol);
	}
	printf("t\tu1\n");
	for (i = 0; i < n; i ++) {
		x = x0 + dx * i;
		y1 = pow(E,x)-x-1;
//		y2 = 1/3.0*pow(E,5*x)+2/3.0*pow(E,-x)+x*x*pow(E, 2*x);
		printf("%g\t%g\t%g\n", x, u1[i],(y1-u1[i])/y1);
	}
 
	free(u1);
//	free(u2);
	return 0;
}
