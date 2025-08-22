// 22:20 시작 
//테스트 케이스 c <=50; 개를 만족
// 입력  짝수인 정수 n  2<=n <10;  , 친구 쌍의 수  0<=m <=nC2;
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

bool areFriends[10][10];
int n; // 전역 변수로 선언

// 결국 출력해야하는것은, 가능한 순서쌍이다 . 
// 1.순서쌍의 순서는 중요하지 않기에     n 을 2로 나눈 만큼 팩토리얼로 죽여줘야한다.
// 2. 
//3. 결국, n명을 /2 해서, 잘 조합 하자 , 근데 순서는 중요하지 않기에 , nCn-2 << 의 값을 리턴하게 되는데 nC2 와 같으니까  nC2 를 nC2/N 뭐시기
// 순서쌍을 기억하는 무언가를 가진다면 , for문을 이용해 1부터 시도해보면된다 .  0번과 매칭 될수 있는 경우가 있을때 마다  +1 씩 가운트 해서 출력하면되는거같은데??
int countPairings(bool taken[10]) {
    // taken[i] = i번째 학생이 짝을 이미 찾았다면  true, false; 
    int firstFree = -1;
    for(int i = 0; i < n; i++) {
        if(!taken[i]) {
            firstFree = i;
            break;
        }
    }
    
    // 기저 사례 모든 학생이 짝을 찾았으면 한 가지 방법을 찾았으니 종료한다.
    if (firstFree == -1) return 1;
    
    int ret = 0;
    
    for(int pairWith = firstFree + 1; pairWith < n; pairWith++) {
        if(!taken[pairWith] && areFriends[firstFree][pairWith]) {
            taken[firstFree] = taken[pairWith] = true;
            ret += countPairings(taken);
            taken[firstFree] = taken[pairWith] = false;
        }
    }
    
    return ret;    
}

int main() {
    int studentCount;
    int friendsPair;
    
    // 입력 받기
    cin >> studentCount >> friendsPair;
    n = studentCount;
    
    // areFriends 배열 초기화
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            areFriends[i][j] = false;
        }
    }
    
    // 친구 관계 입력 받기
    for(int i = 0; i < friendsPair; i++) {
        int a, b;
        cin >> a >> b;
        areFriends[a][b] = areFriends[b][a] = true;
    }
    
    // taken 배열 초기화
    bool taken[10] = {false};
    
    // 결과 출력
    cout << countPairings(taken) << endl;
    
    return 0;
}