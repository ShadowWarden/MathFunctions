/* horner.c
*  Omkar H. Ramachandran
*  University of Colorado - Boulder
*
*  Roots of an order 'N' polynomial
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define E 2.718281828459045

double fp(double *, int, double);
double horner(double *, int, double);
double divide(double *,int, double);
int print(double *, int); 

int main(int argc, char ** argv){
	int N = argc-2,i;
	double tol = atof(argv[argc-1]);
//	printf("%d %d\n",argc,N);
	double *coeffs = (double *) malloc (sizeof(double)*N);	
	double *roots = (double *) malloc (sizeof(double)*(N-1));
	double x = 1.24,xold;

	for(i=0;i<N;i++){
		*(coeffs+i) = atof(argv[i+1]);
	}
	int root = 0;
	while(N!=3 && N!=0){
		int flag = 0;
//		printf("Root %d\n",root + 1);
		do{
			xold = x;
			x = xold-horner(coeffs,N,xold)/fp(coeffs,N,xold);
			flag ++;
//			printf("%d : %f : %f\n",flag,x,(x-xold)/xold);
		}while(flag == 1 || fabs((x-xold)/xold) > pow(10,-tol));
		roots[root] = x;
		divide(coeffs,N,x);
		N-=1;
		root++;
	}
//	print(coeffs,3);
//	printf("\n");
	if(N==3){
		double B = pow(coeffs[N-2],2)-4*coeffs[N-1]*coeffs[N-3];
		if(B>=0){
			roots[root] = (-coeffs[N-2]-sqrt(B))/(2*coeffs[N-1]);
			roots[root+1] = (-coeffs[N-2]+sqrt(B))/(2*coeffs[N-1]);
			root+=2;
		}
	}
	printf("\n");
	print(roots,root);
	printf("\n");
	free(coeffs);
	free(roots);
	return 0;

}

int print(double * roots, int n){
	int i;
	for(i=0;i<n;i++){
		printf("%f ", roots[i]);
	}
	return 1;
}

double horner(double *coeffs, int s, double x){
	int i;
	double res = 0.0;
 	for(i=s-1; i >= 0; i--){
		res = res * x + coeffs[i];
	}
  	return res;
}

double fp(double * coeffs,int s,double x){
// Compute the derivative of the polynomial
	int i;
	double res = 0;
	double * new = (double *) malloc (sizeof(double)*(s-1));
	for(i=s-1;i>0;i--){
		new[i-1] = coeffs[i]*i;	
	}
	res = horner(new,s-1,x);
	free(new);
	return res;
}

double divide(double * coeffs, int N, double r){
	int i;
//	double old=coeffs[N-1];
//	printf("%d\n",N);
	for(i=N-2;i>=0;i--){
		double new=coeffs[i+1]*(r)+coeffs[i];
//		printf("%d : %f %f\n",i,coeffs[i+1],new);
//		old = coeffs[i];
		coeffs[i] = new;
	}
	for(i=0;i<N-1;i++){
		coeffs[i]=coeffs[i+1];
//		printf("%f ", coeffs[i]);
	}
//	printf("\n");
	return r;
}
