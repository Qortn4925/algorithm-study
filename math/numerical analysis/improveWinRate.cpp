#include <iostream>
using namespace std;

// 입력, 게임 한 횟수 , 승리한 횟수
// 출력 승률이 1%올라가기 위해 필요한 게임수 .
//제한 최대 게임수는 20억, 2 x10^9
long long L=2000000000;
int ratio(long long tryGame, long long winGame) {
	return (winGame*100) /tryGame;
}
int neededGame(long long tryGame, long long winGame){
	
	if(ratio(tryGame,winGame)==ratio(tryGame+L,winGame+L)) {
		return -1;
	}
	long long lo =0;
	long long hi = L;
	while(lo+1 <hi ){
		long long mid = (lo+hi) /2;
		if(ratio(tryGame,winGame) == ratio(tryGame+mid,winGame+mid))
 			lo=mid;
 		else
 		    hi = mid;
    }
	   	return  hi;
}

int main() {
    cout << neededGame(10, 8) << endl;       
    cout << neededGame(100, 80) << endl;     
    cout << neededGame(50, 49) << endl;      
    cout << neededGame(10, 1) << endl;       
    cout << neededGame(2000000000, 1000000000) << endl; 
    cout << neededGame(1, 1) << endl;        
}