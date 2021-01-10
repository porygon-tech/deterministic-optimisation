#include <stdio.h>
#include <stdlib.h>
#include <math.h>	

//DEBUGGING:  gcc rosenbrock2.c -o rb -lm -Ofast -fsanitize=address -static-libasan -g -Wall && time ./rb -1.5f 1.0f 100
//gcc rosenbrock2.c -o rb -lm -Ofast -fsanitize=address -static-libasan -g -Wall && time ./rb 2 5 100 > /mnt/c/Users/Miki/Documents/Modelling/OPT/2.\ Deterministic\ opt/coords.txt


double rosenbrock ( double *vars ){
	double x = vars[0];
	double y = vars[1];
	return(100.0f*(y - x*x)*(y - x*x) + (1 - x)*(1 - x));	//rosenbrock function
}

void rbGradient ( double *vars, double *dx ){
	double x = vars[0];
	double y = vars[1];
	double k = -200.0f*(x*x-y);
	dx[0] = 2.0f*(x-1)-2.0f*x*k;	// partial derivative of rosenbrock in x
	dx[1] = k;				// partial derivative of rosenbrock in y
}

void dcpy ( double *copy, double *paste ){
	paste[0] = copy[0];
	paste[1] = copy[1];
}

void lineSearch ( double *x, double *dxo, float sigma, float rho, double *conj){
	//double(f)(float *),	//function
	//void(df)(double *, double *),//gradient function corresponding to f
	double fo = rosenbrock ( x );
	double ak = 1.0f;
	double *xo, fk;

	xo = (double*) malloc( 2*sizeof(double));
	dcpy( x, xo ); //recording initial position at xo

	x[0] = xo[0] + ak * conj[0];
	x[1] = xo[1] + ak * conj[1];

	fk = rosenbrock ( x ) - sigma * ak * (dxo[0]*conj[0] + dxo[1]*conj[1]);

	while (fk > fo && ak > 0.0001f){
		ak = ak*rho;
		x[0] = xo[0] + ak * conj[0];
		x[1] = xo[1] + ak * conj[1];
		fk = rosenbrock ( x ) - sigma * ak * (dxo[0]*conj[0] + dxo[1]*conj[1]);
		//printf("\t%f: (%f,%f)\n", ak, x[0], x[1]);
	}
	free(xo);
}

void conjugate ( double *dx, double *conj, double beta){
	conj[0] = -dx[0] + beta * conj[0];
	conj[1] = -dx[1] + beta * conj[1];
}

double pr ( double *dir, double *dir_prev ){ //polak-ribiere
	return((dir[0] * (dir[0]-dir_prev[0]) + dir[1] * (dir[1]-dir_prev[1])) / (pow(dir_prev[0],2) + pow(dir_prev[1],2)));
}

double modulus ( double *dx ) {
	return(sqrt( dx[0]*dx[0] + dx[1]*dx[1] ));
}


//==========================================================================================================





int main(int argc, char const *argv[])
{

	double *x, *gradient, *gradprev, *conj, z;

	x		 = (double*) malloc(2*sizeof(double));
	gradient = (double*) malloc(2*sizeof(double));
	gradprev = (double*) malloc(2*sizeof(double));
	conj	 = (double*) malloc(2*sizeof(double));

/*
	x[0] = atof(argv[1]);
	x[1] = atof(argv[2]);
*/
	x[0] = -1.5;
	x[1] = -1.0;
	printf("%.2f\t%.2f\n", x[0],x[1]);

	unsigned short i=0, iters=atoi(argv[3]);
	double thres = 0.001f;						////////////////


	z = rosenbrock ( x );
	rbGradient( x, gradient );


	conj[0] = -gradient[0];
	conj[1] = -gradient[1];
	


	while (modulus( gradient ) > thres && i < iters) {
		i++;
		//printf("(%f,%f)\n", conj[0],conj[1]);
		//printf("ls on %f %f %f %f %f %f \n", x[0],x[1], gradient[0], gradient[1], conj[0], conj[1] );
		lineSearch( x, gradient, 0.001f, 0.25f, conj );
		dcpy( gradient, gradprev );
		rbGradient( x, gradient );
		conjugate( gradient, conj, pr(gradient,gradprev));
		z = rosenbrock ( x );
		//if (i%1==0) printf("[%06d]: x=%.4f, y=%.4f, z=%.6f\n", i, x[0],x[1],z);
		printf("%.2f\t%.2f\n", x[0],x[1]);
		//printf("%.2f\t%.2f %f\n", x[0],x[1], modulus( gradient ));
	}
	free(x);
	free(gradient);
	free(gradprev);
	free(conj);
}