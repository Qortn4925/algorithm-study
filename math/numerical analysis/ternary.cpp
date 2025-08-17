
// 우리가 최대치를 찾고 싶어하는 함수
double f(double x);

// [lo ,hi] ㅇ구간에서 f(x)가 최대치를 가지는 x 를 반환
double ternary_max(double lo, double hi) {
    for(int iter = 0; iter < 100; iter++) {  
        double a = (2*lo + hi) / 3.0;
        double b = (lo + 2*hi) / 3.0;        수정
        
        if(f(a) > f(b)) {
            hi = b;
        } else {
            lo = a;
        }
    }
    return (lo + hi) / 2.0;
}