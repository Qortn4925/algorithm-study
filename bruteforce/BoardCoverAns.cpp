#include <iostream>
#include <vector>
using namespace std;

const int coverType[4][3][2] = {
 { {0,0} ,{1,0},{0,1}} ,
 {{ 0,0} ,{0,1} ,{1,1}  }  ,
 {  {0,0} ,{1,0} ,{1,1}} ,
 { {0,0} ,{1,0} ,{1,-1}}  
  };
  bool set (vector<vector<int>> & board ,int y ,int x, int type , int delta) {
	bool ok =true;
	for(int i = 0; i<3; ++i) {
		const int ny =y +coverType[type] [i][0] ;
		const int nx = x+ coverType[type] [i] [1] ;
		if(ny <0 || ny>= board.size() || nx <0 || nx>= board[0].size()) {
			ok= false;
		}else if( (board[ny][nx] += delta)>1 ) {
			ok = false;
		} 
	}	
	return ok ;
  	
  }
  
  int cover ( vector<vector <int>> & board) {
  	int y =- 1, x= -1;
  	for(int i =0; i<board.size(); ++i) {
  		for(int j =0; j<board[i].size(); ++j ) {
  			if (board[i][j] == 0) {
  				y= i;
  				x =j;
  				break;
			  }
			
		  }
  		if( y!= -1) break;
	  }
	  
	  // 기저 사례
	  if( y==-1) return 1;
	  int ret= 0;
	  for(int type=0; type <4; ++type) {
	  	if(set(board,y,x,type,1)) 
	  	ret += cover(board) ;
	  	set(board,y,x,type ,-1) ;
	  }
	  return ret;
  }
  
  
  // 게임판 출력 함수
void printBoard(const vector<vector<int>>& board) {
    for(int i = 0; i < board.size(); ++i) {
        for(int j = 0; j < board[i].size(); ++j) {
            if(board[i][j] == 1) cout << "■ ";
            else cout << "□ ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    // 테스트 케이스 1: 3x3 게임판 (가운데 1칸이 막힌 상태)
    cout << "=== 테스트 케이스 1: 3x3 게임판 ===\n";
    vector<vector<int>> board1 = {
        {0, 0, 0},
        {0, 1, 0},  // 가운데 칸은 이미 채워져 있음
        {0, 0, 0}
    };
    
    cout << "초기 게임판:\n";
    printBoard(board1);
    
    int result1 = cover(board1);
    cout << "가능한 덮기 방법의 수: " << result1 << "\n\n";
    
    // 테스트 케이스 2: 4x3 게임판 (모든 칸이 빈 상태)
    cout << "=== 테스트 케이스 2: 4x3 게임판 ===\n";
    vector<vector<int>> board2 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    
    cout << "초기 게임판:\n";
    printBoard(board2);
    
    int result2 = cover(board2);
    cout << "가능한 덮기 방법의 수: " << result2 << "\n\n";
    
    // 테스트 케이스 3: 2x3 게임판
    cout << "=== 테스트 케이스 3: 2x3 게임판 ===\n";
    vector<vector<int>> board3 = {
        {0, 0, 0},
        {0, 0, 0}
    };
    
    cout << "초기 게임판:\n";
    printBoard(board3);
    
    int result3 = cover(board3);
    cout << "가능한 덮기 방법의 수: " << result3 << "\n\n";
    
    // 사용자 입력으로 커스텀 게임판 만들기
    cout << "=== 커스텀 게임판 테스트 ===\n";
    int rows, cols;
    cout << "게임판 크기를 입력하세요 (행 열): ";
    cin >> rows >> cols;
    
    vector<vector<int>> customBoard(rows, vector<int>(cols, 0));
    
    cout << "막힌 칸의 개수를 입력하세요: ";
    int blocked;
    cin >> blocked;
    
    cout << "막힌 칸의 위치를 입력하세요 (행 열, 0부터 시작):\n";
    for(int i = 0; i < blocked; ++i) {
        int r, c;
        cin >> r >> c;
        if(r >= 0 && r < rows && c >= 0 && c < cols) {
            customBoard[r][c] = 1;
        }
    }
    
    cout << "\n커스텀 게임판:\n";
    printBoard(customBoard);
    
    int customResult = cover(customBoard);
    cout << "가능한 덮기 방법의 수: " << customResult << "\n";
    
    return 0;
}