#include<iostream>

using namespace std;

int fibonacci(int n);

int main(int argc,char* argv[]){
	int n;//计算第n项斐波拉契数列
	cin>>n;
	for(int i=0;i<n;i++)
		cout<<fibonacci(i)<<endl;
	return 0;
}

int fibonacci(int n){
	int a=0,b=1;
	while(n-->0){
		b=a+b;
		a=b-a;
	}
	return b;
}