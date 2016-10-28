/* free_spline.c
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*  University of Colorado-Boulder
*
*
*/

#include <stdio.h>
#include <stdlib.h>

int getsize(FILE *,int *);
int populate(double *, double *, FILE *, int);
int print(double *, double *, double *, double *, int);

int main(int argc, char ** argv){
	// Declarations
	FILE *fin;
	int N;
	double *a,*b,*c,*d,*x,*h,*alpha,*z,*mu, *l;
//	double FPO,FPN;
	char *f = argv[1];
	fin = fopen(f,"r");

	// Populate	
	getsize(fin,&N);
	x = (double *) malloc (sizeof(double)*N);
	a = (double *) malloc (sizeof(double)*N); 
	b = (double *) malloc (sizeof(double)*N);
	c = (double *) malloc (sizeof(double)*N);
	d = (double *) malloc (sizeof(double)*N);
	h = (double *) malloc (sizeof(double)*N);
	mu = (double *) malloc (sizeof(double)*N);
	z = (double *) malloc (sizeof(double)*N);
	alpha = (double *) malloc (sizeof(double)*N);
	l = (double *) malloc (sizeof(double)*N);
	populate(a,x,fin,N);
	
	//Step 1
	int i;
	for(i=0;i<N-1;i++){
		h[i] = x[i+1]-x[i];
	}
	
	// Step 2
//	alpha[0] = 3*(a[1]-a[0])/h[0]-3*FPO;
//	alpha[N-1] = 3*FPN - 3*(a[N-1]-a[N-2])/h[N-2];
	
	// Step 3
	for(i=1;i<N-1;i++){
		alpha[i] = 3/h[i]*(a[i+1]-a[i])-3/h[i-1]*(a[i]-a[i-1]);	
	}

	// Step 4
	l[0] = 1;
	mu[0] = 0;
	z[0]= 0;

	// Step 5
	for(i=1;i<N-1;i++){
		l[i] = 2*(x[i+1]-x[i-1])-h[i-1]*mu[i-1];
		mu[i] = h[i]/l[i];
		z[i] = (alpha[i]-h[i-1]*z[i-1])/l[i];
	}	

	// Step 6
	l[N-1] = 1;
	z[N-1] = 0;
	c[N-1] = 0;

	// Step 7
	for(i=N-2;i>=0;i--){
		c[i] = z[i] - mu[i]*c[i+1];
		b[i] = (a[i+1]-a[i])/h[i] - h[i]*(c[i+1]+2*c[i])/3;
		d[i] = (c[i+1]-c[i])/(3*h[i]);
	}

	// Step 8
	print(a,b,c,d,N);
	
	// Free
	fclose(fin);
	free(x);
	free(a);
	free(b);
	free(c);
	free(d);
	free(h);
	free(z);
	free(mu);
	free(alpha);
	free(l);

	return 0;
}

int getsize(FILE *fin, int *N){
	int err;
	fseek(fin,SEEK_SET,0);
	err = fscanf(fin,"%d",N);
	return err;
}

int populate(double *a, double *x, FILE *fin, int N){
	fseek(fin,SEEK_SET,sizeof(int));
//	fscanf(fin,"%lf %lf",FPO,FPN);
	int i;
	for(i=0;i<N;i++){
		fscanf(fin,"%lf %lf",x+i,a+i);
	}
	return 0;
}

int print(double *a, double *b, double *c, double *d, int N){
	int i;
	for(i = 0;i < N-1; i++){
		printf("%f %f %f %f\n",a[i],b[i],c[i],d[i]);
	}
	return 0;
}
