
#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<vector<char>> board = {
    {'U','R','L','P','M'},
    {'X','P','R','E','T'},
    {'G','I','A','E','T'},
    {'X','T','N','Z','Y'},
    {'X','O','Q','R','S'}
};

// 보드의 범위가 나갔는지 확인 하는 함수 
bool inRange(int y,int x) {
	// 보드의 사이즈는 5x5 임   c++ 에서 해당 
	if ( !((0<=y&&y<5) && (0<=x&& x<5)) ) {
		return false;
	}
	return true;
}

const int dx[8] ={-1,-1,-1,1,1,1,0,0};
const int dy[8]= {-1,0,1,-1,0,1,-1,1};

//1.  탐색 ,  그후 인접한 방향  -1,0, 1,0, -1,-1,  ~~~ 등 확인, 없으면 ? false  시행 마다 그 다음 인덱스 값이 맞는지 확인해봐야함
 bool hasWord(int y,int x, const string &  word) {
 	
 	if( !inRange(y,x)) return false;
 	
 	if(board[y][x] !=word[0]) return false;
  	
  	if(word.size()==1) return true;

	  // 8가지 방향 체크 
 	for (int direction=0; direction<8; ++direction) {
 		int nextY=y+dy[direction] ; 
		 int nextX=x+dx[direction];
 		if(	hasWord(nextY,nextX,word.substr(1)) )
		 return true;
	 }
 	
 	return true;
 }
 int main() {
    vector<string> words = {"PRETTY", "GIRL", "REPEAT", "KIM", "URPM"};
    
    for (string word : words) {
        bool found = false;
        // 보드의 모든 칸에서 시작해봄
        for (int y = 0; y < 5; ++y) {
            for (int x = 0; x < 5; ++x) {
                if (hasWord(y, x, word)) {
                    found = true;
                }
            }
        }
        cout << word << ": " << (found ? "YES" : "NO") << endl;
    }

    return 0;
}
 