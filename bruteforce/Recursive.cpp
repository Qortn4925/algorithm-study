#include <iostream>
using namespace std;
int Recrusive (int n) {
	 int sum;
	if(n==1) {
		return 1;
	}
	sum= n+Recrusive(n-1) ;
	
	return sum;
}

int ReverseRecrusive (int cur,int n ) {
	if(cur==n) {
		return n;
	}
	return cur+ReverseRecrusive(cur+1,n) ;
	
}

int main (){
	int n= 10;
	int hap = Recrusive(n);
	int j = ReverseRecrusive(1,n);
	cout<<hap<<endl;
	cout<<j<<endl;
}