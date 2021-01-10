#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//gcc rosenbrock_lma.c -o rb -lm -Ofast -fsanitize=address -static-libasan -g -Wall && time ./rb 


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

void compute_d ( double *x, double *d, double m){
	double denom = (400+202*m+m*m+80000*x[0]*x[0]+1200*m*x[0]*x[0]-80000*x[1]-400*m*x[1]);
	d[0] = -((80000*x[0]*(-x[0]*x[0]+x[1]))/denom) + ((200+m)*(2*(1-x[0])+400*x[0]*(-x[0]*x[0]+x[1])))/denom;
	d[1] = -((200*(-x[0]*x[0]+x[1])*(2+m+800*x[0]*x[0]-400*(-x[0]*x[0]+x[1])))/denom) + (400*x[0]*(2*(1-x[0])+400*x[0]*(-x[0]*x[0]+x[1])))/denom;
}

double modulus ( double *dx ) {
	return(sqrt( dx[0]*dx[0] + dx[1]*dx[1] ));
}


int main(int argc, char const *argv[])
{

	double *x, *d, *gradient, old, new, m;
	x  = (double*) malloc(2*sizeof(double));
	d  = (double*) malloc(2*sizeof(double));
	gradient = (double*) malloc(2*sizeof(double));
/*
	x[0] = atof(argv[1]);
	x[1] = atof(argv[2]);
*/
	x[0] = -1.5;
	x[1] = -1.0;
	printf("%.4f\t%.4f\t\n", x[0],x[1]);
	
	unsigned short i=0, iters=100;
	double thres = 0.001;						////////////////

	old=0;
	new = rosenbrock ( x );
	m = 2;

	rbGradient( x, gradient);
	while (modulus(gradient) > thres && i < iters) {
		i++;
		compute_d( x, d, m);
		old = rosenbrock ( x );	
		x[0] = x[0] + d[0];
		x[1] = x[1] + d[1];
		new = rosenbrock ( x );
		rbGradient( x, gradient);
				if 	(new < old){ m = m/2;
		} else 	if 	(new > old){ m = m*2;
		}


		//if (i%1==0) printf("[%06d]: x=%.4f, y=%.4f, z=%.6f\n", i, x[0],x[1],z);
		//printf("%.4f\t%.4f\t%.10f\n", x[0],x[1],new);
		printf("%.4f\t%.4f\t\n", x[0],x[1]);
		//printf("%.2f\t%.2f %f\n", x[0],x[1], modulus( gradient ));
	}
	free(x);
	free(d);
	free(gradient);

}