/*  power-method.c
*   Omkar H. Ramachandran
*
*
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int getsize(FILE * fin, int *N){
	fseek(fin,SEEK_SET,0);
	fscanf(fin,"%d",N);
}

int populate(double *a, double *x, FILE *fin, int N){
	fseek(fin,SEEK_SET,sizeof(int));
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			fscanf(fin,"%lf",a+N*i+j);
		}
	}
	for(i=0;i<N;i++){
		fscanf(fin,"%lf",x+i);
	}
}

int equate(double *a, double *b, int N){
	int i;
	for(i=0;i<N;i++){
		a[i] = b[i];
	}
}

int mult(double *a, double *x, double *c,int N){
	int i,j;
	for(i=0;i<N;i++){
		c[i] = 0;
		for(j=0;j<N;j++){
			c[i]+=a[N*i+j]*x[j];
		}
//		printf("%f ",c[i]);
	}
//	printf("\n");
}

double dot(double *a, double *b, int N){
	int i;
	double sum = 0;
	for(i=0;i<N;i++){
		sum += a[i]*b[i];
	}
//	printf("%f\n",sum);
	return sum;
}

int print(double *x, int N, double r){
	int i;
	for(i=0;i<N;i++){
		printf("%f ",x[i]/r);
	}
	printf("\n");
}

double max(double *x, int N){
	int i;
	double max = x[0];
	for(i=0;i<N;i++){
		if(fabs(x[i])>fabs(max)){
			max = x[i];
		}
	}
//	printf("%f\n",max);
	return max;
}

int main(int argc, char **argv){
	int N;
	double *a,*x, *xold, *xtemp, l=1, lold, res=0, resold=0;
	FILE *fin = fopen(argv[1],"r");
	getsize(fin,&N);
	a = (double *) malloc (sizeof(double)*N*N);
	x = (double *) malloc (sizeof(double)*N);
	xold = (double *) malloc (sizeof(double)*N);
	xtemp = (double *) malloc (sizeof(double)*N);
	populate(a,x,fin,N);
	equate(xold,x,N);
	double tol = atof(argv[2]);
	int flag = 0;

	do{
		resold = res;
		lold = l;
		equate(xtemp,x,N);
		mult(a,xtemp,x,N);
		l = dot(x,xold,N);
		res = l/lold;			
//		equate(xold,x,N);

		printf("%d %f ",flag,res);
		print(x,N,max(x,N));
		flag++;
	}while(fabs(res-resold)>=pow(10,-tol));
//	double norm = max(x,N);
//	print(x,N,max(x,N));
	
//	printf("%f %d\n",res,flag);
	free(a);
	free(x);
	free(xold);
	free(xtemp);
	fclose(fin);

	return 0;
}
