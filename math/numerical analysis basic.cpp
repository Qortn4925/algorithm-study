#include <bits/stdc++.h>
using namespace std;

// poly(다항식)의 미분 결과를 반환하는 함수
// 예: 3x^2 + 2x + 1 → 6x + 2
vector<double> differentiate(const vector<double>& poly);

// 다항식 차수가 2 이하일 때(1차, 2차 방정식)의 해를 직접 구하는 함수
vector<double> solveNative(const vector<double>& poly);

// poly(다항식)를 x0에 대입했을 때의 함수값을 계산하는 함수
double evaluate(const vector<double> &poly, double x0);

const double L = 25; // 해(근)가 존재할 것으로 예상하는 범위 절댓값 (±L 바깥은 무시)

vector<double> solve(const vector<double>& poly) {
    int n = poly.size() - 1; // 다항식 차수

    // 차수가 2 이하라면 (1차 or 2차) 직접 해를 구하는 solveNative 호출
    if (n <= 2) return solveNative(poly);

    // 다항식의 미분을 구함 → 극값 위치를 알아내기 위해
    vector<double> derivative = differentiate(poly);

    // 미분 다항식의 근(=원래 다항식의 극값 x좌표)을 구함
    vector<double> sols = solve(derivative);

    // 양쪽 무한대 쪽 구간을 처리하기 위해 구간 경계 추가
    sols.insert(sols.begin(), -L - 1); // 제일 왼쪽에 (-L-1) 삽입
    sols.push_back(L + 1);              // 제일 오른쪽에 (L+1) 삽입

    vector<double> ret; // 최종 해를 저장할 벡터

    // 극값과 경계 사이의 구간을 하나씩 검사
    for (int i = 0; i + 1 < (int)sols.size(); ++i) {
        double x1 = sols[i],     x2 = sols[i + 1];     // 현재 구간 양 끝 x값
        double y1 = evaluate(poly, x1), y2 = evaluate(poly, x2); // 해당 점에서의 함수값

        // 구간 한쪽 끝이 해(근)일 경우 바로 추가
        if (y1 == 0) {
            ret.push_back(x1);
            continue;
        }
        if (y2 == 0) {
            ret.push_back(x2);
            continue;
        }

        // 양 끝의 함수값 부호가 같으면 근 없음 (Intermediate Value Theorem)
        if (y1 * y2 > 0) continue;

        // [x1, x2] 사이에 부호 변화 → 근이 존재 → 이분법으로 근 찾기
        for (int iter = 0; iter < 100; ++iter) { // 100번 반복 → 오차 충분히 줄어듦
            double mx = (x1 + x2) / 2;       // 중간점
            double my = evaluate(poly, mx);  // 중간점에서의 함수값

            // 중간점과 왼쪽 끝의 부호가 같으면 왼쪽을 중간점으로 옮김
            if (y1 * my > 0) {
                y1 = my;
                x1 = mx;
            }
            // 아니면 오른쪽 끝을 중간점으로 옮김
            else {
                y2 = my;
                x2 = mx;
            }
        }
        // 반복 끝 → x1, x2 거의 같아짐 → 근은 그 중간값
        ret.push_back((x1 + x2) / 2);
    }

    // 모든 근을 오름차순 정렬
    sort(ret.begin(), ret.end());

    return ret; // 찾은 모든 실근 반환
}
