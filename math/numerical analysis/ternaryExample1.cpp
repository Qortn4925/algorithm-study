double t;

vector<double> runSpeed;     // 각 선수의 달리기 속도
vector<double> cycleSpeed;   // 각 선수의 사이클링 속도

// 달리기 구간이 run 일때 i번 선수의 시간을 반환해주는 함수
double time (int i , double run) {
	 double cycle= t-run;
	 return  run/runSpeed[i] + cycle/cycleSpped[i] ;
}


// 두 선수의 차이를 리턴 하는 함수
double diff(double r) {
	int n = runSpped.size();
	double cheater= time(n-1,r);
	double others = time(0,r);
	for(int i = 1; i<n-1; ++i) {
		others =min(other,time(i,r));
 	}
 	return others-cheater;
}


double maxDiff() {
	double lo = 0, hi=t;
	 for(int it= 0; it<100; ++it) {
	 	double aab= (2*lo+ hi) /3.0;
	 	double abb=(lo+2*hi) /3.0;
	 	if(diff(aab)>diff(abb))) 
	 	hi =abb;
	 	else
	 	 lo =aab;
	 }
	 return (lo+hi) / 2;
}