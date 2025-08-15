#include <iostream>
using namespace std;

// m개월 후의 대출 잔액 계산
double balance(double amount, int duration, double rates, double monthlyPayment) {
    double remaining = amount;
    for (int i = 0; i < duration; i++) {
        if (remaining > 0) {
            // 한 달 이자 적용
            remaining = remaining + remaining * rates;
            // 매달 상환
            remaining -= monthlyPayment;
        } else {
            return 0.0;
        }
    }
    return remaining;
}

// 기간 안에 갚을 수 있는 최소 월 상환액 계산
double payment(double amount, int duration, double rates) {
    double lo = 0.0;       // 갚을 수 없는 최소 금액
    double hi = amount * (1 + rates) * 2; // 충분히 큰 값으로 초기화

    for (int iter = 0; iter < 100; ++iter) { // 이분 탐색 반복
        double mid = (lo + hi) / 2.0;
        if (balance(amount, duration, rates, mid) <= 0) {
            hi = mid; // mid로도 갚을 수 있음 → 더 적게 갚을 수 있는지 탐색
        } else {
            lo = mid; // mid로는 부족 → 더 많이 갚아야 함
        }
    }
    return hi;
}


int main() {
    double loan = 1000000; // 100만 원 대출
    int months = 12;       // 12개월
    double rate = 0.01;    // 월 이자율 1%

    double monthlyPay = payment(loan, months, rate);
    cout << " monthly payment: " << monthlyPay << " won" << endl;

    return 0;
}