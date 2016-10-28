/* neville.c
*  Omkar H. Ramachandran
*
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct{
	double f;
	int first;
	int last;	
}P;

int getsize(FILE *);
int populate(FILE *, int, double *, P *);
void dump(P*,int);

int main(int argc, char ** argv){
	// Declarations and init
	FILE *in = fopen(argv[1],"r");
	double a = atof(argv[2]);
	int N = getsize(in);
	double *x = (double *) malloc (sizeof(double)*N);
	P *p = (P *) malloc (sizeof(P)*N);
	int n = N;
	populate(in,N,x,p);
	int i,j;
	double res = 0;

	// Main loop
	dump(p,N);
	do{
		printf("N = %d\n",N-1);
		for(i=0;i<N-1;i++){
			p[i].f = ((a-x[p[i+1].last])*p[i].f+(x[p[i].first]-a)*p[i+1].f)/(x[p[i].first]-x[p[i+1].last]);
			p[i].last = p[i+1].last;
//			printf("%d : %f, %d, %d\n",i,p[i].f,p[i].first,p[i].last);
		}
		N -= 1;
		dump(p,N);
	}while(N>1);
//	printf("%f\n",p[0].f);
	fclose(in);
	free(x);
	return 1;
}

int getsize(FILE *in){
	int N;
	fseek(in,SEEK_SET,0);
	fscanf(in,"%d",&N);
	return N;
}

int populate(FILE *in,int N,double *x, P *p){
	int i;
	fseek(in,SEEK_SET,sizeof(int));
	for(i=0;i<N;i++){
		fscanf(in,"%lf %lf",x+i,&(p+i)->f);
		p[i].first = i;
		p[i].last = i;
	}
	return 1;
}

void dump(P *p, int N){
	int i;
	for(i=0;i<N;i++){
		printf("%d : %f %d %d\n",i,p[i].f,p[i].first,p[i].last);
	}
}
