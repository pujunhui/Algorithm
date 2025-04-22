#include<iostream>
#include<cmath>
using namespace std;
#define PI 3.14159265

double sinx(double x){
	return sin(x);
}

double e_sqrx(double x){
	return exp(-x*x);
}

double x_sqrx(double x){
	return 2*x/(1+x*x);
}

//梯形法求定积分
double integral(double a, double b,double (*fun)(double), int n){
	double h = (b-a)/2;
	double sum = ((*fun)(a)+(*fun)(b))/2;
	for(int i=1; i<n; i++)
		sum += (*fun)(a+i*h);
	sum *= h;
	return sum;
}

int main(int argc,char* argv[]){
	cout<<integral(0, PI, sinx,1000)<<endl;
	cout<<integral(0, PI, e_sqrx,1000)<<endl;
	cout<<integral(0, PI, x_sqrx,1000)<<endl;
}