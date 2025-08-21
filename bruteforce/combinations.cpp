#include <iostream>
using namespace std;

#include <iostream>
#include <vector>
using namespace std;

// picked 벡터 출력
void printPicked(const vector<int>& picked) {
    for (int x : picked) {
        cout << x << " ";
    }
    cout << endl;
}

// n개 중 toPick개 뽑기 (조합)
void pick(int n, vector<int>& picked, int toPick) {
    if (toPick == 0) { // 기저 사례
        printPicked(picked);
        return;
    }
    int smallest = picked.empty() ? 0 : picked.back() + 1;
    for (int next = smallest; next < n; ++next) {
        picked.push_back(next);
        pick(n, picked, toPick - 1);
        picked.pop_back();
    }
}

int main() {
    int n = 7;     
    int toPick = 4;  // 뽑을 갯수
    vector<int> picked;
    pick(n, picked, toPick);
    return 0;
}