/* lagrange.c
*  Omkar H. Ramachandran
*
*  DISCUSSION
*  
*  The lagrange polynomial given n points x1,x2,...xn is defined as follows :
*  li(x) = (x-x1)*(x-x2)*...*(x-x[i-1])*(x-x[i+1])*...*(x-xn)
*  Notice that (x-xi) is missing. Given N points, is is clear that a weighted
*  average of each normalized li has to give you the interpolated polynomial. 
*  In other words :
*  Pn(x) = Sum {li(x)/li(xi)*y[i]}
*  
*/

#include <stdio.h>
#include <stdlib.h>

int getsize(FILE *);
int populate(FILE *, int, double *, double *);

int main(int argc, char ** argv){
	// Declarations and init
	FILE *in = fopen(argv[1],"r");
	double a = atof(argv[2]);
	int N = getsize(in);
	double *x = (double *) malloc (sizeof(double)*N);
	double *y = (double *) malloc (sizeof(double)*N);
	populate(in,N,x,y);
	int i,j;
	double res = 0;

	// Main loop
	for(i=0;i<N;i++){
		float num = 1;
		float din = 1;
		for(j=0;j<N;j++){
			if(i!=j){
				num*=a-x[j];
				din*=x[i]-x[j];
			}	
		}
		res+=num/din*y[i];
		printf("%d : %f\n",i,res);
	}
//	printf("%f\n",res);
	fclose(in);
	free(x);
	free(y);
	return 1;
}

int getsize(FILE *in){
	int N;
	fseek(in,SEEK_SET,0);
	fscanf(in,"%d",&N);
	return N;
}

int populate(FILE *in,int N,double *x, double *y){
	int i;
	fseek(in,SEEK_SET,sizeof(int));
	for(i=0;i<N;i++){
		fscanf(in,"%lf %lf",x+i,y+i);
	}
	return 1;
}
