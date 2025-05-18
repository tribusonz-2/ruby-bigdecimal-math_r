#include <stdio.h>
#include <math.h>
#include <float.h>
#define KMAX 20

double a,b,h;
int n;

double
f(double x)
{
	return( exp(x)*cos(x) );
}

double
trapezoid2(double tk1)
{
	double sum;
	int i;
	h /=2 ;
	sum=0;
	for(i=0;i<n;i++)
		sum += f(a+h*(2*i+1));
	n *=2;
	return(tk1/2+h*sum);
}


int
main(void)
{
	double eps = DBL_EPSILON,r,t[KMAX],t1[KMAX];
	int k,j;
	printf("torelence of Romberg's quadrature: eps ? ");
//	scanf("%lg", &eps);
	printf("interval of quadrature: a, b ? ");
	scanf("%lg%lg", &a, &b);
	printf("\n  n  trapezoid \t\t*** extrapolation ***\n");
	n=1;
	h=b-a;
	t[0]=h*(f(a)+f(b))/2;
	printf("%3d %13.6e\n", n, t[0]);
	for(k=1;k<KMAX;k++)
	{
		for(j=0;j<k;j++)
		t1[j]=t[j];
		t[0] = trapezoid2(t1[0]);
		r =1;
		for(j=0;j<k;j++)
		{
			r *= 4;
			t[j+1] = (r*t[j]-t1[j])/(r-1);
		}
		printf("%3d", n);
		for (j = 0; j <= k; j++)
		printf(" %13.16e", t[j]);
		printf("\n");
		if( fabs((t[k]-t1[k-1])/t[k])<eps)
			break;
	}
	if(k>=KMAX)
	printf("divergent ?\n");
	printf("\nintegral=%13.16g\n", t[k]);
}
