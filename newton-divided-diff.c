/* newton-divided-diff.c
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*
*  University of Colorado-Boulder
*
*/

#include <stdio.h>
#include <stdlib.h>

int getsize(FILE *, int *);
int populate(double *, double *, double *, FILE *, int);


int main(int argc, char ** argv){
	FILE *fin;
	char *a = argv[1];
	double *x,*y,*p,k, f, f1=1, f2=0;
	int i,j=1,n;

	fin = fopen(a,"r");
	getsize(fin,&n);
	x = (double *) malloc (sizeof(double)*n);
	y = (double *) malloc (sizeof(double)*n);
	p = (double *) malloc (sizeof(double)*n);	
	populate(x,y,&k,fin,n);
	f=y[0];

	do{
        	for (i=0;i<n-1;i++){
			p[i] = ((y[i+1]-y[i])/(x[i+j]-x[i]));
			y[i]=p[i];
		}
		f1=1;
		for(i=0;i<j;i++){
			f1*=(k-x[i]);
		}
		printf("%f ",f1);
		f2+=(y[0]*f1);
		n--;
		j++;
	}while(n!=1);
	f+=f2;
	printf("\nf(%f) = %f\n", k , f);

	free(x);
	free(y);
	fclose(fin);
	
	return 0;
}

int getsize(FILE *fin, int *n){
	fseek(fin,SEEK_SET,0);
	fscanf(fin,"%d",n);
}

int populate(double *x, double *y, double *k, FILE *fin, int n){
	int i;
	fseek(fin,SEEK_SET,sizeof(int));
	fscanf(fin,"%lf",k);
	for(i=0;i<n;i++){
		fscanf(fin,"%lf %lf",x+i,y+i);
	}
}
	
