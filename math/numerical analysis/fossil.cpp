// 입력의 첫 줄은  테스트 케이스의 수 C <=50 
// 두 볼록 껍질의 포함된 점의 개수 N ,M    1<= n,m <=100
// 2n개의 실수로 첫 번째 볼록껍질에 포함된 점의 좌표 (x,y)가 시계 반대 방향 순서대로 주어집니다.
// 2m개의 실수로 두 번째 볼록 겁질에 포함된 점의 좌표(x,y)가 시계반대 방향
// 내가 생각하는 풀이, 결국 엔 직선 4개의  높이차의 최대를 구하는 문제 . 직선 ax+b - cx+d  의 특정 점 x   범위는 lo hi  에서의 최대
//1 번, 직선 구하기 이 직선의 특징은 겹치는 영역에 있다 인데. 이걸 기준잡기가 어렵네 어느 지점에서  방정식을 전부 구하고 
//2 번  좌표값의 다 주어지니까 , 특정한 일차 함수 4개를 도출한다
//3 범위도 구해야하네 , 범위 구하고
//4  마지막 최대값 구하는 함수 
#include <bits/stdc++.h>
using namespace std;

struct point {
    double x, y;
};

//입력에 주어진 볼록 다각형
vector<point> hull1, hull2;
vector<pair<point,point>> upper, lower;

void decompose(const vector<point>& hull) {
    int n = hull.size();
    for (int i = 0; i < n; i++) {
        if(hull[i].x < hull[(i+1)%n].x){
            lower.push_back(make_pair(hull[i], hull[(i+1)%n]));
        } else if (hull[i].x > hull[(i+1)%n].x) {
            upper.push_back(make_pair(hull[i], hull[(i+1)%n]));
        }
    }
}

//[a.x,b.x]구간 안에 x가 포함되나 확인
bool between(const point& a, const point& b, double x) {
    return (a.x <= x && x <= b.x) || (b.x <= x && x <= a.x);
}

// 선분 (a,b)와 주어진 위치의 수직선이 교차하는 y좌표를 반환한다.
double at(const point& a, const point& b, double x) {
    if (abs(a.x - b.x) < 1e-9) return a.y;
    return a.y + (b.y - a.y) * (x - a.x) / (b.x - a.x);
}

double vertical(double x) {
    double minUp = 1e20, maxLow = -1e20;
    //위 껍질의 선분을 순회하며 최소 y좌표를 찾는다.
    for(int i = 0; i < upper.size(); ++i) {
        if(between(upper[i].first, upper[i].second, x)) 
            minUp = min(minUp, at(upper[i].first, upper[i].second, x));
    }
    for (int i = 0; i < lower.size(); ++i) {
        if(between(lower[i].first, lower[i].second, x)) 
            maxLow = max(maxLow, at(lower[i].first, lower[i].second, x));
    }
    return minUp - maxLow;
}

double minX(const vector<point>& hull) {
    double result = hull[0].x;
    for(const auto& p : hull) result = min(result, p.x);
    return result;
}

double maxX(const vector<point>& hull) {
    double result = hull[0].x;
    for(const auto& p : hull) result = max(result, p.x);
    return result;
}

double solve() {
    upper.clear();
    lower.clear();
    decompose(hull1);
    decompose(hull2);
    
    // 수직선이 두 다각형을 모두 만나는 x좌표의 범위를 구한다
    double lo = max(minX(hull1), minX(hull2));
    double hi = min(maxX(hull1), maxX(hull2));
    // 예외 처리 
    if(hi < lo) return 0;
    
    for(int iter = 0; iter < 100; ++iter) {
        double aab = (lo*2 + hi) / 3.0;
        double abb = (lo + 2*hi) / 3.0;
        if(vertical(aab) < vertical(abb)) 
            lo = aab;
        else
            hi = abb;
    }
    return max(0.0, vertical(hi));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int C;
    cin >> C;
    cout << fixed << setprecision(6);
    while (C--) {
        int N, M;
        cin >> N >> M;
        hull1.resize(N);
        hull2.resize(M);
        for (int i = 0; i < N; i++) cin >> hull1[i].x >> hull1[i].y;
        for (int i = 0; i < M; i++) cin >> hull2[i].x >> hull2[i].y;
        cout << solve() << "\n";
    }
    return 0;
}
